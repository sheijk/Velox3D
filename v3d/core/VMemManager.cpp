#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <new>

#ifndef	WIN32
#include <unistd.h>
#endif

#include <Core/VMemManager.h>


static const vuint			hashBits							= 12;
static vbool				randomWipe							= false;
static vbool				alwaysValidateAll					= false;
static vbool				alwaysLogAll						= false;
static vbool				alwaysWipeAll						= true;
static vbool				cleanupLogOnFirstRun				= true;
static const vuint			paddingSize							= 4;

#undef	new
#undef	delete
#undef	malloc
#undef	calloc
#undef	realloc
#undef	free

const vuint					VMemManager::ALLOC_UNKNOWN			= 0;
const vuint					VMemManager::ALLOC_NEW				= 1;
const vuint					VMemManager::ALLOC_NEW_ARRAY		= 2;
const vuint					VMemManager::ALLOC_MALLOC			= 3;
const vuint					VMemManager::ALLOC_CALLOC			= 4;
const vuint					VMemManager::ALLOC_REALLOC			= 5;
const vuint					VMemManager::ALLOC_DELETE			= 6;
const vuint					VMemManager::ALLOC_DELETE_ARRAY		= 7;
const vuint					VMemManager::ALLOC_FREE				= 8;

static vuint				prefixPattern						= 0xbaadf00d;
static vuint				postfixPattern						= 0xdeadc0de;
static vuint				unusedPattern						= 0xfeedface;
static vuint				releasedPattern						= 0xdeadbeef;

static const vuint			hashSize							= 1 << hashBits;
static const vchar*			allocationTypes[]					= { "Unknown",
																	"new",     
																	"new[]", 
																	"malloc",   
																	"calloc",
																	"realloc",
																	"delete", 
																	"delete[]", 
																	"free" };
static VMemManager::VAllocationUnit* hashTable[hashSize];
static VMemManager::VAllocationUnit* reservoir;
static vuint				currentAllocationCount				= 0;
static vuint				breakOnAllocationCount				= 0;
static VMemManager::VStats	stats;
static const vchar*			sourceFile							= "??";
static const vchar*			sourceFunc							= "??";
static vuint				sourceLine							= 0;
static vbool				staticDeinitTime					= false;
static VMemManager::VAllocationUnit** reservoirBuffer			= NULL;
static vuint				reservoirBufferSize					= 0;

static void	doCleanupLogOnFirstRun(void)
{
	if (cleanupLogOnFirstRun)
	{
		unlink("memory.log");
		cleanupLogOnFirstRun = false;
	}
}

static const vchar* sourceFileStripper(const vchar* sourceFile)
{
	vchar* ptr = strrchr(sourceFile, '\\');
	if (ptr) 
	{
		return ptr + 1;
	}

	ptr = strrchr(sourceFile, '/');
	if (ptr) 
	{
		return ptr + 1;
	}

	return sourceFile;
}

static const vchar* ownerString(const vchar *sourceFile, const vuint sourceLine, const vchar *sourceFunc)
{
	static	vchar	str[90];
	memset(str, 0, sizeof(str));
	sprintf(str, "%s(%05d)::%s", sourceFileStripper(sourceFile), sourceLine, sourceFunc);
	return str;
}

static	const vchar	*insertCommas(vuint value)
{
	static	vchar	str[30];
	memset(str, 0, sizeof(str));

	sprintf(str, "%u", value);
	if (strlen(str) > 3)
	{
		memmove(&str[strlen(str)-3], &str[strlen(str)-4], 4);
		str[strlen(str) - 4] = ',';
	}
	if (strlen(str) > 7)
	{
		memmove(&str[strlen(str)-7], &str[strlen(str)-8], 8);
		str[strlen(str) - 8] = ',';
	}
	if (strlen(str) > 11)
	{
		memmove(&str[strlen(str)-11], &str[strlen(str)-12], 12);
		str[strlen(str) - 12] = ',';
	}

	return str;
}

static	const vchar	*memorySizeString(unsigned long size)
{
	static	vchar	str[90];
	
	if (size > (1024 * 1024))	
	{
		sprintf(str, "%10s (%7.2fM)", insertCommas(size), (float) size / (1024.0f * 1024.0f));
	}
	else if (size > 1024)	
	{
		sprintf(str, "%10s (%7.2fK)", insertCommas(size), (float) size / 1024.0f);
	}
	else
	{
		sprintf(str, "%10s bytes     ", insertCommas(size));
	}

	return str;
}

static VMemManager::VAllocationUnit* findAllocUnit(const void *reportedAddress)
{
	assert(reportedAddress != NULL);

	vuint hashIndex = ((vuint) reportedAddress >> 4) & (hashSize - 1);
	VMemManager::VAllocationUnit* ptr = hashTable[hashIndex];
	while(ptr)
	{
		if (ptr->m_pReportedAddress == reportedAddress) 
		{
			return ptr;
		}
		ptr = ptr->m_pNext;
	}

	return NULL;
}

static size_t calculateActualSize(const size_t reportedSize)
{
	return reportedSize + paddingSize * sizeof(long) * 2;
}

static size_t calculateReportedSize(const size_t actualSize)
{
	return actualSize - paddingSize * sizeof(long) * 2;
}

static void* calculateReportedAddress(const void *actualAddress)
{
	if (!actualAddress) 
	{
		return NULL;
	}

	return (void*)((vchar*)actualAddress + sizeof(long) * paddingSize);
}

static void wipeWithPattern(VMemManager::VAllocationUnit *allocUnit, unsigned long pattern, 
							const vuint originalReportedSize = 0)
{
	if (randomWipe)
	{
		pattern = ((rand() & 0xff) << 24) | ((rand() & 0xff) << 16) | ((rand() & 0xff) << 8) | (rand() & 0xff);
	}

	if (alwaysWipeAll && allocUnit->m_iReportedSize > originalReportedSize)
	{
		long	*lptr = (long *) ((vchar *)allocUnit->m_pReportedAddress + originalReportedSize);
		vint	length = allocUnit->m_iReportedSize - originalReportedSize;
		vint	i;
		for (i = 0; i < (length >> 2); i++, lptr++)
		{
			*lptr = pattern;
		}

		vuint	shiftCount = 0;
		vchar		*cptr = (vchar *) lptr;
		for (i = 0; i < (length & 0x3); i++, cptr++, shiftCount += 8)
		{
			*cptr = (pattern & (0xff << shiftCount)) >> shiftCount;
		}
	}

	long		*pre = (long *) allocUnit->m_pActualAddress;
	long		*post = (long *) ((vchar *)allocUnit->m_pActualAddress + allocUnit->m_iActualSize - paddingSize * sizeof(long));
	for (vuint i = 0; i < paddingSize; i++, pre++, post++)
	{
		*pre = prefixPattern;
		*post = postfixPattern;
	}
}

static void	resetGlobals(void)
{
	sourceFile = "??";
	sourceLine = 0;
	sourceFunc = "??";
}

static void log(const vchar *format, ...)
{
	static vchar buffer[2048];
	va_list	ap;
	va_start(ap, format);
	vsprintf(buffer, format, ap);
	va_end(ap);

	if (cleanupLogOnFirstRun) 
	{
		doCleanupLogOnFirstRun();
	}

	FILE	*fp = fopen("memory.log", "ab");

	assert(fp);

	if (!fp) 
	{
		return;
	}

	fprintf(fp, "%s\r\n", buffer);
	fclose(fp);
}

static void dumpAllocations(FILE *fp)
{
	fprintf(fp, "Alloc.   Addr       Size       Addr       Size                        BreakOn BreakOn              \r\n");
	fprintf(fp, "Number Reported   Reported    Actual     Actual     Unused    Method  Dealloc Realloc Allocated by \r\n");
	fprintf(fp, "------ ---------- ---------- ---------- ---------- ---------- -------- ------- ------- --------------------------------------------------- \r\n");

	for (vuint i = 0; i < hashSize; i++)
	{
		VMemManager::VAllocationUnit *ptr = hashTable[i];
		while(ptr)
		{
			fprintf(fp, "%06d 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X %-8s    %c       %c    %s\r\n",
				ptr->m_uiAllocationNumber,
				(vuint) ptr->m_pReportedAddress, ptr->m_iReportedSize,
				(vuint) ptr->m_pActualAddress, ptr->m_iActualSize,
				VMemManager::CalcUnused(ptr),
				allocationTypes[ptr->m_uiAllocationType],
				ptr->m_bBreakOnDealloc ? 'Y':'N',
				ptr->m_bBreakOnRealloc ? 'Y':'N',
				ownerString(ptr->m_szSourceFile, ptr->m_uiSourceLine, ptr->m_szSourceFunc));
			ptr = ptr->m_pNext;
		}
	}
}

static	void	dumpLeakReport()
{
	FILE	*fp = fopen("memleaks.log", "w+b");

	assert(fp);
	if (!fp) return;

	static  vchar    timeString[25];
	memset(timeString, 0, sizeof(timeString));
	time_t  t = time(NULL);
	struct  tm *tme = localtime(&t);
	fprintf(fp, " ---------------------------------------------------------------------------------------------------------------------------------- \r\n");
	fprintf(fp, "|                                          Memory leak report for:  %02d/%02d/%04d %02d:%02d:%02d                                            |\r\n", tme->tm_mon + 1, tme->tm_mday, tme->tm_year + 1900, tme->tm_hour, tme->tm_min, tme->tm_sec);
	fprintf(fp, " ---------------------------------------------------------------------------------------------------------------------------------- \r\n");
	fprintf(fp, "\r\n");
	fprintf(fp, "\r\n");
	if (stats.m_uiTotalAllocUnitCount)
	{
		fprintf(fp, "%d memory leak%s found:\r\n", stats.m_uiTotalAllocUnitCount, stats.m_uiTotalAllocUnitCount == 1 ? "":"s");
	}
	else
	{
		fprintf(fp, "Congratulations! No memory leaks found!\r\n");

		if (reservoirBuffer)
		{
			for (vuint i = 0; i < reservoirBufferSize; i++)
			{
				free(reservoirBuffer[i]);
			}
			free(reservoirBuffer);
			reservoirBuffer = 0;
			reservoirBufferSize = 0;
			reservoir = NULL;
		}
	}
	fprintf(fp, "\r\n");

	if (stats.m_uiTotalAllocUnitCount)
	{
		dumpAllocations(fp);
	}

	fclose(fp);
}

class VMemStaticTimeTracker
{
public :

	VMemStaticTimeTracker()
	{
		doCleanupLogOnFirstRun();
	}

	~VMemStaticTimeTracker() 
	{
		staticDeinitTime = true; 
		dumpLeakReport();
	}
};

static	VMemStaticTimeTracker	mstt;

vbool& m_alwaysValidateAll(void)
{
	return alwaysValidateAll;
}

vbool& m_alwaysLogAll(void)
{
	return alwaysLogAll;
}

vbool& m_alwaysWipeAll(void)
{
	return alwaysWipeAll;
}

vbool& m_randomeWipe()
{
	return randomWipe;
}

vbool& VMemManager::BreakOnRealloc(void *reportedAddress)
{
	VMemManager::VAllocationUnit	*au = findAllocUnit(reportedAddress);

	assert(au != NULL);
	assert(au->m_uiAllocationType == VMemManager::ALLOC_MALLOC ||
		au->m_uiAllocationType == VMemManager::ALLOC_CALLOC ||
		au->m_uiAllocationType == VMemManager::ALLOC_REALLOC);

	return au->m_bBreakOnRealloc;
}

vbool& VMemManager::BreakOnDealloc(void *reportedAddress)
{
	VMemManager::VAllocationUnit	*au = findAllocUnit(reportedAddress);

	assert(au != NULL);

	return au->m_bBreakOnDealloc;
}

void m_breakOnAllocation(vuint count)
{
	breakOnAllocationCount = count;
}

void VMemManager::SetOwner(const vchar *file, const vuint line, const vchar *func)
{
	sourceFile = file;
	sourceLine = line;
	sourceFunc = func;
}

void	*operator new(size_t reportedSize)
{
	#ifdef TEST_MEMORY_MANAGER
	log("ENTER: new");
	#endif

	if (reportedSize == 0) reportedSize = 1;

	for(;;)
	{
		void	*ptr = VMemManager::Allocator(sourceFile, sourceLine, sourceFunc, VMemManager::ALLOC_NEW, reportedSize);
		if (ptr)
		{
			#ifdef TEST_MEMORY_MANAGER
			log("EXIT : new");
			#endif
			return ptr;
		}

		new_handler	nh = set_new_handler(0);
		set_new_handler(nh);

		if (nh)
		{
			(*nh)();
		}

		else
		{
			#ifdef TEST_MEMORY_MANAGER
			log("EXIT : new");
			#endif
			throw std::bad_alloc();
		}
	}
}

void* operator new[](size_t reportedSize)
{
	#ifdef TEST_MEMORY_MANAGER
	log("ENTER: new[]");
	#endif

	if (reportedSize == 0) reportedSize = 1;

	for(;;)
	{
		void	*ptr = VMemManager::Allocator(sourceFile, sourceLine, sourceFunc, VMemManager::ALLOC_NEW_ARRAY, reportedSize);
		if (ptr)
		{
			#ifdef TEST_MEMORY_MANAGER
			log("EXIT : new[]");
			#endif
			return ptr;
		}

		new_handler	nh = set_new_handler(0);
		set_new_handler(nh);

		if (nh)
		{
			(*nh)();
		}

		else
		{
			#ifdef TEST_MEMORY_MANAGER
			log("EXIT : new[]");
			#endif
			throw std::bad_alloc();
		}
	}
}

void* operator new(size_t reportedSize, const vchar *sourceFile, vint sourceLine)
{
	#ifdef TEST_MEMORY_MANAGER
	log("ENTER: new");
	#endif

	if (reportedSize == 0) reportedSize = 1;

	for(;;)
	{
		void	*ptr = VMemManager::Allocator(sourceFile, sourceLine, "??", VMemManager::ALLOC_NEW, reportedSize);
		if (ptr)
		{
			#ifdef TEST_MEMORY_MANAGER
			log("EXIT : new");
			#endif
			return ptr;
		}

		new_handler	nh = set_new_handler(0);
		set_new_handler(nh);

		if (nh)
		{
			(*nh)();
		}

		else
		{
			#ifdef TEST_MEMORY_MANAGER
			log("EXIT : new");
			#endif
			throw std::bad_alloc();
		}
	}
}

void* operator new [] (size_t reportedSize, const vchar *sourceFile, vint sourceLine)
{
	if (reportedSize == 0) reportedSize = 1;

	for(;;)
	{
		void	*ptr = VMemManager::Allocator(sourceFile, sourceLine, "??", VMemManager::ALLOC_NEW_ARRAY, reportedSize);
		if (ptr)
		{
			return ptr;
		}

		new_handler	nh = set_new_handler(0);
		set_new_handler(nh);

		if (nh)
		{
			(*nh)();
		}

		else
		{
			throw std::bad_alloc();
		}
	}
}

void operator delete(void *reportedAddress)
{
	#ifdef TEST_MEMORY_MANAGER
	log("ENTER: delete");
	#endif

	if (!reportedAddress) return;

	VMemManager::Deallocator(sourceFile, sourceLine, sourceFunc, VMemManager::ALLOC_DELETE, reportedAddress);

	#ifdef TEST_MEMORY_MANAGER
	log("EXIT : delete");
	#endif
}

void operator delete [] (void *reportedAddress)
{
	#ifdef TEST_MEMORY_MANAGER
	log("ENTER: delete[]");
	#endif


	if (!reportedAddress) return;

	VMemManager::Deallocator(sourceFile, sourceLine, sourceFunc, VMemManager::ALLOC_DELETE_ARRAY, reportedAddress);

	#ifdef TEST_MEMORY_MANAGER
	log("EXIT : delete[]");
	#endif
}

void* VMemManager::Allocator(const vchar *sourceFile, const vuint sourceLine, const vchar *sourceFunc, const vuint allocationType, const size_t reportedSize)
{
	try
	{
		#ifdef TEST_MEMORY_MANAGER
		log("ENTER: m_allocator()");
		#endif

		currentAllocationCount++;

		if (alwaysLogAll) log("%05d %-40s %8s            : %s", currentAllocationCount, ownerString(sourceFile, sourceLine, sourceFunc), allocationTypes[allocationType], memorySizeString(reportedSize));

		assert(currentAllocationCount != breakOnAllocationCount);

		if (!reservoir)
		{
			reservoir = (VMemManager::VAllocationUnit *) malloc(sizeof(VMemManager::VAllocationUnit) * 256);

			assert(reservoir != NULL);

			if (reservoir == NULL) throw "Unable to allocate RAM for internal memory tracking data";


			memset(reservoir, 0, sizeof(VMemManager::VAllocationUnit) * 256);
			for (vuint i = 0; i < 256 - 1; i++)
			{
				reservoir[i].m_pNext = &reservoir[i+1];
			}

			VMemManager::VAllocationUnit	**temp = (VMemManager::VAllocationUnit **) realloc(reservoirBuffer, (reservoirBufferSize + 1) * sizeof(VMemManager::VAllocationUnit *));
			assert(temp);
			if (temp)
			{
				reservoirBuffer = temp;
				reservoirBuffer[reservoirBufferSize++] = reservoir;
			}
		}

		assert(reservoir != NULL);

		VMemManager::VAllocationUnit	*au = reservoir;
		reservoir = au->m_pNext;

		memset(au, 0, sizeof(VMemManager::VAllocationUnit));
		au->m_iActualSize        = calculateActualSize(reportedSize);
		#ifdef RANDOM_FAILURE
		double	a = rand();
		double	b = RAND_MAX / 100.0 * RANDOM_FAILURE;
		if (a > b)
		{
			au->actualAddress = malloc(au->actualSize);
		}
		else
		{
			log("!Random faiure!");
			au->actualAddress = NULL;
		}
		#else
		au->m_pActualAddress     = malloc(au->m_iActualSize);
		#endif
		au->m_iReportedSize      = reportedSize;
		au->m_pReportedAddress   = calculateReportedAddress(au->m_pActualAddress);
		au->m_uiAllocationType    = allocationType;
		au->m_uiSourceLine        = sourceLine;
		au->m_uiAllocationNumber  = currentAllocationCount;
		if (sourceFile) strncpy(au->m_szSourceFile, sourceFileStripper(sourceFile), sizeof(au->m_szSourceFile) - 1);
		else		strcpy (au->m_szSourceFile, "??");
		if (sourceFunc) strncpy(au->m_szSourceFunc, sourceFunc, sizeof(au->m_szSourceFunc) - 1);
		else		strcpy (au->m_szSourceFunc, "??");

		#ifndef RANDOM_FAILURE
		assert(au->m_pActualAddress != NULL);
		#endif

		if (au->m_pActualAddress == NULL)
		{
			throw "Request for allocation failed. Out of memory.";
		}

		assert(allocationType != VMemManager::ALLOC_UNKNOWN);


		vuint hashIndex = ((vuint)au->m_pReportedAddress >> 4) & (hashSize - 1);
		if (hashTable[hashIndex]) hashTable[hashIndex]->m_pPrev = au;
		au->m_pNext = hashTable[hashIndex];
		au->m_pPrev = NULL;
		hashTable[hashIndex] = au;

		stats.m_uiTotalReportedMemory += au->m_iReportedSize;
		stats.m_uiTotalActualMemory   += au->m_iActualSize;
		stats.m_uiTotalAllocUnitCount++;
		if (stats.m_uiTotalReportedMemory > stats.m_uiPeakReportedMemory) stats.m_uiPeakReportedMemory = stats.m_uiTotalReportedMemory;
		if (stats.m_uiTotalActualMemory   > stats.m_uiPeakActualMemory)   stats.m_uiPeakActualMemory   = stats.m_uiTotalActualMemory;
		if (stats.m_uiTotalAllocUnitCount > stats.m_uiPeakAllocUnitCount) stats.m_uiPeakAllocUnitCount = stats.m_uiTotalAllocUnitCount;
		stats.m_uiAccumulatedReportedMemory += au->m_iReportedSize;
		stats.m_uiAccumulatedActualMemory += au->m_iActualSize;
		stats.m_uiAccumulatedAllocUnitCount++;

		wipeWithPattern(au, unusedPattern);

		if (allocationType == VMemManager::ALLOC_CALLOC)
		{
			memset(au->m_pReportedAddress, 0, au->m_iReportedSize);
		}

		if (alwaysValidateAll) VMemManager::ValidateAllAllocUnits();

		if (alwaysLogAll) log("                                                                 OK: %010p (hash: %d)", au->m_pReportedAddress, hashIndex);

		resetGlobals();

		#ifdef TEST_MEMORY_MANAGER
		log("EXIT : m_allocator()");
		#endif

		return au->m_pReportedAddress;
	}
	catch(const vchar *err)
	{
		// Deal with the errors

		log(err);
		resetGlobals();

		#ifdef TEST_MEMORY_MANAGER
		log("EXIT : m_allocator()");
		#endif

		return NULL;
	}
}

void* VMemManager::Reallocator(const vchar *sourceFile, const vuint sourceLine, const vchar *sourceFunc, const vuint reallocationType, const size_t reportedSize, void *reportedAddress)
{
	try
	{
		#ifdef TEST_MEMORY_MANAGER
		log("ENTER: m_reallocator()");
		#endif

		if (!reportedAddress)
		{
			return VMemManager::Allocator(sourceFile, sourceLine, sourceFunc, reallocationType, reportedSize);
		}

		currentAllocationCount++;

		assert(currentAllocationCount != breakOnAllocationCount);

		if (alwaysLogAll) log("%05d %-40s %8s(%010p): %s", currentAllocationCount, ownerString(sourceFile, sourceLine, sourceFunc), allocationTypes[reallocationType], reportedAddress, memorySizeString(reportedSize));

		VMemManager::VAllocationUnit	*au = findAllocUnit(reportedAddress);

		assert(au != NULL);
		if (au == NULL) throw "Request to reallocate RAM that was never allocated";
		assert(VMemManager::ValidateAllocUnit(au));
		assert(reallocationType != VMemManager::ALLOC_UNKNOWN);
		assert(au->m_uiAllocationType == VMemManager::ALLOC_MALLOC ||
			 au->m_uiAllocationType == VMemManager::ALLOC_CALLOC ||
			 au->m_uiAllocationType == VMemManager::ALLOC_REALLOC);
		assert(au->m_bBreakOnRealloc == false);

		vuint	originalReportedSize = au->m_iReportedSize;

		void	*oldReportedAddress = reportedAddress;
		size_t	newActualSize = calculateActualSize(reportedSize);
		void	*newActualAddress = NULL;
		#ifdef RANDOM_FAILURE
		double	a = rand();
		double	b = RAND_MAX / 100.0 * RANDOM_FAILURE;
		if (a > b)
		{
			newActualAddress = realloc(au->actualAddress, newActualSize);
		}
		else
		{
			log("!Random faiure!");
		}
		#else
		newActualAddress = realloc(au->m_pActualAddress, newActualSize);
		#endif

		#ifndef RANDOM_FAILURE
		assert(newActualAddress);
		#endif

		if (!newActualAddress) throw "Request for reallocation failed. Out of memory.";

		stats.m_uiTotalReportedMemory -= au->m_iReportedSize;
		stats.m_uiTotalActualMemory   -= au->m_iActualSize;

		au->m_iActualSize        = newActualSize;
		au->m_pActualAddress     = newActualAddress;
		au->m_iReportedSize      = calculateReportedSize(newActualSize);
		au->m_pReportedAddress   = calculateReportedAddress(newActualAddress);
		au->m_uiAllocationType    = reallocationType;
		au->m_uiSourceLine        = sourceLine;
		au->m_uiAllocationNumber  = currentAllocationCount;
		if (sourceFile) strncpy(au->m_szSourceFile, sourceFileStripper(sourceFile), sizeof(au->m_szSourceFile) - 1);
		else		strcpy (au->m_szSourceFile, "??");
		if (sourceFunc) strncpy(au->m_szSourceFunc, sourceFunc, sizeof(au->m_szSourceFunc) - 1);
		else		strcpy (au->m_szSourceFunc, "??");

		vuint	hashIndex = (vuint) -1;
		if (oldReportedAddress != au->m_pReportedAddress)
		{
			{
				vuint	hashIndex = ((vuint) oldReportedAddress >> 4) & (hashSize - 1);
				if (hashTable[hashIndex] == au)
				{
					hashTable[hashIndex] = hashTable[hashIndex]->m_pNext;
				}
				else
				{
					if (au->m_pPrev)	au->m_pPrev->m_pNext = au->m_pNext;
					if (au->m_pNext)	au->m_pNext->m_pPrev = au->m_pPrev;
				}
			}

			hashIndex = ((vuint) au->m_pReportedAddress >> 4) & (hashSize - 1);
			if (hashTable[hashIndex]) hashTable[hashIndex]->m_pPrev = au;
			au->m_pNext = hashTable[hashIndex];
			au->m_pPrev = NULL;
			hashTable[hashIndex] = au;
		}


		stats.m_uiTotalReportedMemory += au->m_iReportedSize;
		stats.m_uiTotalActualMemory   += au->m_iActualSize;
		if (stats.m_uiTotalReportedMemory > stats.m_uiPeakReportedMemory) stats.m_uiPeakReportedMemory = stats.m_uiTotalReportedMemory;
		if (stats.m_uiTotalActualMemory   > stats.m_uiPeakActualMemory)   stats.m_uiPeakActualMemory   = stats.m_uiTotalActualMemory;
		vint	deltaReportedSize = reportedSize - originalReportedSize;
		if (deltaReportedSize > 0)
		{
			stats.m_uiAccumulatedReportedMemory += deltaReportedSize;
			stats.m_uiAccumulatedActualMemory += deltaReportedSize;
		}

		wipeWithPattern(au, unusedPattern, originalReportedSize);

		assert(VMemManager::ValidateAllocUnit(au));

		if (alwaysValidateAll) VMemManager::ValidateAllAllocUnits();

		if (alwaysLogAll) log("                                                                 OK: %010p (hash: %d)", au->m_pReportedAddress, hashIndex);

		resetGlobals();

		#ifdef TEST_MEMORY_MANAGER
		log("EXIT : m_reallocator()");
		#endif

		return au->m_pReportedAddress;
	}
	catch(const vchar *err)
	{
		// Deal with the errors

		log(err);
		resetGlobals();

		#ifdef TEST_MEMORY_MANAGER
		log("EXIT : m_reallocator()");
		#endif

		return NULL;
	}
}

void VMemManager::Deallocator(const vchar *sourceFile, const vuint sourceLine, const vchar *sourceFunc, const vuint deallocationType, const void *reportedAddress)
{
	try
	{
		#ifdef TEST_MEMORY_MANAGER
		log("ENTER: m_deallocator()");
		#endif

		if (alwaysLogAll) log("      %-40s %8s(%010p)", ownerString(sourceFile, sourceLine, sourceFunc), allocationTypes[deallocationType], reportedAddress);

		VMemManager::VAllocationUnit	*au = findAllocUnit(reportedAddress);

		assert(au != NULL);
		if (au == NULL) throw "Request to deallocate RAM that was never allocated";
		assert(VMemManager::ValidateAllocUnit(au));
		assert(deallocationType != VMemManager::ALLOC_UNKNOWN);
		assert((deallocationType == VMemManager::ALLOC_DELETE       && au->m_uiAllocationType == VMemManager::ALLOC_NEW      ) ||
			 (deallocationType == VMemManager::ALLOC_DELETE_ARRAY && au->m_uiAllocationType == VMemManager::ALLOC_NEW_ARRAY) ||
			 (deallocationType == VMemManager::ALLOC_FREE         && au->m_uiAllocationType == VMemManager::ALLOC_MALLOC   ) ||
			 (deallocationType == VMemManager::ALLOC_FREE         && au->m_uiAllocationType == VMemManager::ALLOC_CALLOC   ) ||
			 (deallocationType == VMemManager::ALLOC_FREE         && au->m_uiAllocationType == VMemManager::ALLOC_REALLOC  ) ||
			 (deallocationType == VMemManager::ALLOC_UNKNOWN                                                ) );

		assert(au->m_bBreakOnDealloc == false);

		wipeWithPattern(au, releasedPattern);

		free(au->m_pActualAddress);

		vuint	hashIndex = ((vuint) au->m_pReportedAddress >> 4) & (hashSize - 1);
		if (hashTable[hashIndex] == au)
		{
			hashTable[hashIndex] = au->m_pNext;
		}
		else
		{
			if (au->m_pPrev)	au->m_pPrev->m_pNext = au->m_pNext;
			if (au->m_pNext)	au->m_pNext->m_pPrev = au->m_pPrev;
		}

		stats.m_uiTotalReportedMemory -= au->m_iReportedSize;
		stats.m_uiTotalActualMemory   -= au->m_iActualSize;
		stats.m_uiTotalAllocUnitCount--;

		memset(au, 0, sizeof(VMemManager::VAllocationUnit));
		au->m_pNext = reservoir;
		reservoir = au;

		resetGlobals();


		if (alwaysValidateAll) VMemManager::ValidateAllAllocUnits();
		if (staticDeinitTime) dumpLeakReport();
	}
	catch(const vchar *err)
	{
		log(err);
		resetGlobals();
	}

	#ifdef TEST_MEMORY_MANAGER
	log("EXIT : m_deallocator()");
	#endif
}

vbool VMemManager::ValidateAddress(const void *reportedAddress)
{
	return findAllocUnit(reportedAddress) != NULL;
}

vbool VMemManager::ValidateAllocUnit(const VMemManager::VAllocationUnit *allocUnit)
{
	long	*pre = (long *) allocUnit->m_pActualAddress;
	long	*post = (long *) ((vchar *)allocUnit->m_pActualAddress + allocUnit->m_iActualSize - paddingSize * sizeof(long));
	vbool	errorFlag = false;
	for (vuint i = 0; i < paddingSize; i++, pre++, post++)
	{
		if (*pre != (long) prefixPattern)
		{
			log("A memory allocation unit was corrupt because of an underrun:");
			VMemManager::DumpAllocUnit(allocUnit, "  ");
			errorFlag = true;
		}

		assert(*pre == (long) prefixPattern);

		if (*post != (long) postfixPattern)
		{
			log("A memory allocation unit was corrupt because of an overrun:");
			VMemManager::DumpAllocUnit(allocUnit, "  ");
			errorFlag = true;
		}

		assert(*post == (long) postfixPattern);
	}

	return !errorFlag;
}

vbool VMemManager::ValidateAllAllocUnits(void)
{
	vuint	errors = 0;
	vuint	allocCount = 0;
	for (vuint i = 0; i < hashSize; i++)
	{
		VMemManager::VAllocationUnit	*ptr = hashTable[i];
		while(ptr)
		{
			allocCount++;
			if (!VMemManager::ValidateAllocUnit(ptr)) errors++;
			ptr = ptr->m_pNext;
		}
	}

	if (allocCount != stats.m_uiTotalAllocUnitCount)
	{
		log("Memory tracking hash table corrupt!");
		errors++;
	}

	assert(allocCount == stats.m_uiTotalAllocUnitCount);
	assert(errors == 0);

	if (errors) log("While validting all allocation units, %d allocation unit(s) were found to have problems", errors);

	return errors != 0;
}

vuint	VMemManager::CalcUnused(const VMemManager::VAllocationUnit *allocUnit)
{
	const unsigned long	*ptr = (const unsigned long *) allocUnit->m_pReportedAddress;
	vuint		count = 0;

	for (vuint i = 0; i < allocUnit->m_iReportedSize; i += sizeof(long), ptr++)
	{
		if (*ptr == unusedPattern) 
		{
			count += sizeof(long);
		}
	}

	return count;
}

vuint VMemManager::CalcAllUnused(void)
{
	vuint	total = 0;
	for (vuint i = 0; i < hashSize; i++)
	{
		VMemManager::VAllocationUnit	*ptr = hashTable[i];
		while(ptr)
		{
			total += VMemManager::CalcUnused(ptr);
			ptr = ptr->m_pNext;
		}
	}

	return total;
}

void VMemManager::DumpAllocUnit(const VMemManager::VAllocationUnit *allocUnit, const vchar *prefix)
{
	log("%sAddress (reported): %010p",       prefix, allocUnit->m_pReportedAddress);
	log("%sAddress (actual)  : %010p",       prefix, allocUnit->m_pActualAddress);
	log("%sSize (reported)   : 0x%08X (%s)", prefix, allocUnit->m_iReportedSize, memorySizeString(allocUnit->m_iReportedSize));
	log("%sSize (actual)     : 0x%08X (%s)", prefix, allocUnit->m_iActualSize, memorySizeString(allocUnit->m_iActualSize));
	log("%sOwner             : %s(%d)::%s",  prefix, allocUnit->m_szSourceFile, allocUnit->m_uiSourceLine, allocUnit->m_szSourceFunc);
	log("%sAllocation type   : %s",          prefix, allocationTypes[allocUnit->m_uiAllocationType]);
	log("%sAllocation number : %d",          prefix, allocUnit->m_uiAllocationNumber);
}

void VMemManager::DumpMemoryReport(const vchar *filename, const vbool overwrite)
{
	FILE	*fp = NULL;
	
	if (overwrite)	fp = fopen(filename, "w+b");
	else		fp = fopen(filename, "ab");

	if (fp == NULL)
	{
		return;
	}

    static  vchar    timeString[25];
    memset(timeString, 0, sizeof(timeString));
    time_t  t = time(NULL);
    struct  tm *tme = localtime(&t);

	fprintf(fp, " ---------------------------------------------------------------------------------------------------------------------------------- \r\n");
    fprintf(fp, "|                                             Memory report for: %02d/%02d/%04d %02d:%02d:%02d                                               |\r\n", tme->tm_mon + 1, tme->tm_mday, tme->tm_year + 1900, tme->tm_hour, tme->tm_min, tme->tm_sec);
	fprintf(fp, " ---------------------------------------------------------------------------------------------------------------------------------- \r\n");
	fprintf(fp, "\r\n");
	fprintf(fp, "\r\n");
	fprintf(fp, " ---------------------------------------------------------------------------------------------------------------------------------- \r\n");
	fprintf(fp, "|                                                           T O T A L S                                                            |\r\n");
	fprintf(fp, " ---------------------------------------------------------------------------------------------------------------------------------- \r\n");
	fprintf(fp, "              Allocation unit count: %10s\r\n", insertCommas(stats.m_uiTotalAllocUnitCount));
	fprintf(fp, "            Reported to application: %s\r\n", memorySizeString(stats.m_uiTotalReportedMemory));
	fprintf(fp, "         Actual total memory in use: %s\r\n", memorySizeString(stats.m_uiTotalActualMemory));
	fprintf(fp, "           Memory tracking overhead: %s\r\n", memorySizeString(stats.m_uiTotalActualMemory - stats.m_uiTotalReportedMemory));
	fprintf(fp, "\r\n");
	fprintf(fp, " ---------------------------------------------------------------------------------------------------------------------------------- \r\n");
	fprintf(fp, "|                                                            P E A K S                                                             |\r\n");
	fprintf(fp, " ---------------------------------------------------------------------------------------------------------------------------------- \r\n");
	fprintf(fp, "              Allocation unit count: %10s\r\n", insertCommas(stats.m_uiPeakAllocUnitCount));
	fprintf(fp, "            Reported to application: %s\r\n", memorySizeString(stats.m_uiPeakReportedMemory));
	fprintf(fp, "                             Actual: %s\r\n", memorySizeString(stats.m_uiPeakActualMemory));
	fprintf(fp, "           Memory tracking overhead: %s\r\n", memorySizeString(stats.m_uiPeakActualMemory - stats.m_uiPeakReportedMemory));
	fprintf(fp, "\r\n");
	fprintf(fp, " ---------------------------------------------------------------------------------------------------------------------------------- \r\n");
	fprintf(fp, "|                                                      A C C U M U L A T E D                                                       |\r\n");
	fprintf(fp, " ---------------------------------------------------------------------------------------------------------------------------------- \r\n");
	fprintf(fp, "              Allocation unit count: %s\r\n", memorySizeString(stats.m_uiAccumulatedAllocUnitCount));
	fprintf(fp, "            Reported to application: %s\r\n", memorySizeString(stats.m_uiAccumulatedReportedMemory));
	fprintf(fp, "                             Actual: %s\r\n", memorySizeString(stats.m_uiAccumulatedActualMemory));
	fprintf(fp, "\r\n");
	fprintf(fp, " ---------------------------------------------------------------------------------------------------------------------------------- \r\n");
	fprintf(fp, "|                                                           U N U S E D                                                            |\r\n");
	fprintf(fp, " ---------------------------------------------------------------------------------------------------------------------------------- \r\n");
	fprintf(fp, "    Memory allocated but not in use: %s\r\n", memorySizeString(VMemManager::CalcAllUnused()));
	fprintf(fp, "\r\n");

	dumpAllocations(fp);

	fclose(fp);
}

VMemManager::VStats	VMemManager::GetMemoryStatistics(void)
{
	return stats;
}
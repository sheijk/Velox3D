#include <malloc.h>
#include <cstdio>

// include mem manager behaviour
#include "MemLocalSettings.h"
//-----------------------------------------------------------------------------

namespace v3d {
	typedef const char* VStringParam;
	typedef long vlong;
	typedef unsigned long vulong;

	const char* GetModuleName();
}

// memory logging
struct VMemLogEntry
{
	const char* pFileName;
	const char* pModuleName;
	long nLine;

	void* pAddress;
	size_t nSize;

	VMemLogEntry* pNext;

	VMemLogEntry(VMemLogEntry* next)
	{
		Clear();
		pNext = next;
	}

	VMemLogEntry()
	{
		pFileName = 0;
		pModuleName = 0;
		nLine = 0;

		pAddress = 0;
		nSize = 0;
		pNext = 0;
	}

	~VMemLogEntry()
	{
		Clear();
	}

	void Copy(const VMemLogEntry& other)
	{
		pFileName = other.pFileName;
		pModuleName = other.pModuleName;
		nLine = other.nLine;

		nSize = other.nSize;
		pAddress = other.pAddress;

		pNext = other.pNext;
	}

	void Clear()
	{
		pNext = 0;
		pModuleName = 0;
		pAddress = 0;
		pFileName = 0;
		nLine = 0;
		nSize = 0;
	}
};

namespace v3d {
	/**
	* Logs memory allocations and deallocations
	*/
	class IVMemLogger
	{
		enum AliveConstant { ObjectAlive = 0xfac2bea1, ObjectDead = 0x00000000 };

		AliveConstant m_Alive;

	public:
		IVMemLogger()			{ m_Alive = ObjectAlive; }
		virtual ~IVMemLogger()	{ m_Alive = ObjectDead; }

		bool IsAlive() const	{ return m_Alive == ObjectAlive; }

		virtual void LogMemAlloc(const VMemLogEntry& entry) = 0;
		virtual void LogMemRelease(const VMemLogEntry& entry) = 0;

		virtual v3d::vulong GetTotalAllocations()	= 0;
		virtual v3d::vulong GetTotalReleases()		= 0;
		virtual size_t GetTotalAllocatedMem()		= 0;
		virtual size_t GetTotalReleasedMem()		= 0;
		virtual size_t GetCurrentUsedMem()			= 0;

		virtual void PrintLeakReport() = 0;
		virtual void EnableLogging() = 0;
	};
} // namespace v3d

template<typename Key, typename Value>
class value_map
{
	struct Node
	{
		Key key;
		Value value;
		Node* pNext;

		Node() { pNext = 0; }
	};

	Node m_Root;

public:
	typedef Key key_type;
	typedef Value value_type;

	value_map() {}

	~value_map()
	{
		// free memory
		Node* pEntry = m_Root.pNext;

		while(pEntry != 0)
		{
			void* addr = pEntry;
			pEntry = pEntry->pNext;
			free(addr);
		}
	}

	value_type* insert(const key_type& key, const value_type& value)
	{
		// start at node
		Node* pNode = &m_Root;

		// loop until we are either at the list's end or we found a node
		// with value > new value
		while( pNode->pNext != 0 && pNode->pNext->key < key )
		{
			pNode = pNode->pNext;
		}

		value_type* pValue = 0;

		if( pNode->key != key )
		{
			// insert node with new value between pNode and pNode.next
			Node* pNewNode = (Node*)malloc(sizeof(Node));
			pNewNode->value = value;
			pNewNode->key = key;
			pNewNode->pNext = pNode->pNext;
			pNode->pNext = pNewNode;

			pValue = &(pNewNode->value);
		}
		else
		{
			pValue = &(pNode->value);
		}

		return pValue;
	};
};

class VMemLogger : public v3d::IVMemLogger
{
	v3d::vulong m_nTotalAllocations ;
	v3d::vulong m_nTotalReleases;

	size_t m_nTotalAllocatedMem;
	size_t m_nTotalReleasedMem;

	size_t m_nCurrentUsedMem;

	bool m_bLogginEnabled;

	struct String100
	{
		char character[100];

		String100() { character[0] = '*'; }
	};

	value_map<const char*, String100> m_StringTable;

	const char* GetInternalStringAddress(const char*);
public:
	VMemLogger();
	virtual ~VMemLogger();

	virtual void LogMemAlloc(const VMemLogEntry& entry);
	virtual void LogMemRelease(const VMemLogEntry& entry);

	v3d::vulong GetTotalAllocations()	{ return m_nTotalAllocations; }
	v3d::vulong GetTotalReleases()		{ return m_nTotalReleases; }
	size_t GetTotalAllocatedMem()		{ return m_nTotalAllocatedMem; }
	size_t GetTotalReleasedMem()		{ return m_nTotalReleasedMem; }
	size_t GetCurrentUsedMem()			{ return m_nCurrentUsedMem; }

	void PrintLeakReport();
	void EnableLogging();
};

VMemLogger::VMemLogger()
{
	m_nTotalAllocations = 0;
	m_nTotalReleases = 0;
	m_nTotalAllocatedMem = 0;
	m_nTotalReleasedMem = 0;
	m_nCurrentUsedMem = 0;

	m_bLogginEnabled = false;

	EnableLogging();
}

VMemLogger::~VMemLogger()
{
	if( m_bLogginEnabled )
		PrintLeakReport();

//	throw int(1);
}

void VMemLogger::EnableLogging()
{
	m_bLogginEnabled = true;
}

template<typename T>
class scope_deleter
{
	T* ptr;
	int check;

	enum Blah { NoInit = 0xF0A3 };

	scope_deleter(const scope_deleter&);
	void operator=(const scope_deleter&);
public:
	scope_deleter()
	{
		if( check != NoInit )
			ptr = 0;
	}

	scope_deleter(T* p)
	{
		ptr = 0;
		assign(p);
	}

	~scope_deleter()
	{
		reset();
	}

	void assign(T* p)
	{
		reset();
		check = NoInit;
		ptr = p;
	}

	void reset()
	{
		if( ptr != 0 )
			delete ptr;
		ptr = 0;
	}
};

// statistics
namespace {
	VMemLogEntry currentMemOp;
	
	VMemLogEntry lastLog;
	VMemLogEntry firstLog(&lastLog);

	scope_deleter<VMemLogger> loggerGuard;
	static v3d::IVMemLogger* pMemLogger = 0;

	v3d::IVMemLogger* GetLocalMemLogger()
	{
		if( 0 == pMemLogger )
		{
			VMemLogger* ptr = new VMemLogger();
			loggerGuard.assign(ptr);

			pMemLogger = ptr;
		}

		return pMemLogger;
	}

	void LogMemAlloc(const VMemLogEntry& entry)
	{
		currentMemOp.pModuleName = v3d::GetModuleName();

		v3d::IVMemLogger* pLogger = GetLocalMemLogger();

		if( pLogger != 0 && pLogger->IsAlive() )
		{
			pLogger->LogMemAlloc(entry);
		}
	}

	void LogMemRelease(const VMemLogEntry& entry)
	{
		currentMemOp.pModuleName = v3d::GetModuleName();

		v3d::IVMemLogger* pLogger = GetLocalMemLogger();

		if( pLogger != 0 && pLogger->IsAlive() )
		{
			GetLocalMemLogger()->LogMemRelease(entry);
		}
	}

} // anonymous namespace

namespace v3d {
	IVMemLogger* GetMemLogger()
	{
		return pMemLogger;
	}

	void SetMemLogger(IVMemLogger* in_pMemLogger)
	{
		//delete pMemLogger;
		loggerGuard.reset();

		pMemLogger = in_pMemLogger;

		VMemLogEntry* pEntry = firstLog.pNext;

		// move all statistics to new mem logger
		while( pEntry != 0 && pEntry != &lastLog )
		{
			// tell new logger
			pMemLogger->LogMemAlloc(*pEntry);
			
			pEntry = pEntry->pNext;
		}

		pEntry = firstLog.pNext;

		while( pEntry != 0 && pEntry != &lastLog )
		{
			VMemLogEntry* toBeDeleted = pEntry;

			pEntry = pEntry->pNext;

			// remove entry
			free(toBeDeleted);
		}
		
		firstLog.pNext = &lastLog;

	}
} // namespace v3d

const char* VMemLogger::GetInternalStringAddress(const char* in_strExternal)
{
	if( in_strExternal == 0 )
		return 0;

	String100 ext;

	String100* pAddress = m_StringTable.insert(in_strExternal, ext);

	// if string has not been copied, yet
	if( pAddress->character[0] == '*' )
	{
        const char* pChar = in_strExternal;
		int length = 1;

		// proceed to end of string, and count length
		while( *pChar != '\0' )
		{
			++length;
			++pChar;
		}

		if( length > 100 )
			length = 100;
		char* pDest = pAddress->character + length - 1;

		// copy string
		while( pDest >= pAddress->character )
		{
			*pDest = *pChar;
			--pDest;
			--pChar;
			--length;
		}

		pDest = pDest;
	}

	return pAddress->character;
}

void VMemLogger::LogMemAlloc(const VMemLogEntry& entry)
{
	if( m_bLogginEnabled == false )
		return;

	m_nTotalAllocations++;
	m_nTotalAllocatedMem += entry.nSize;
	m_nCurrentUsedMem += entry.nSize;

	// create new entry
	VMemLogEntry* pEntry = 
		reinterpret_cast<VMemLogEntry*>(malloc(sizeof(VMemLogEntry)));

	// store data
	pEntry->Copy(entry);

	// store filename to filename list and update reference
	pEntry->pFileName = GetInternalStringAddress(pEntry->pFileName);
	pEntry->pModuleName = GetInternalStringAddress(pEntry->pModuleName);

	// set new entry as first log list element
	pEntry->pNext = firstLog.pNext;
	firstLog.pNext = pEntry;
}

void VMemLogger::LogMemRelease(const VMemLogEntry& entry)
{
	m_nTotalReleases++;

	void* addr = entry.pAddress;

	if( 0 == addr )
		return;

	VMemLogEntry* pEntry = &firstLog;

	if( pEntry == 0 )
		return;

	while( pEntry->pNext != 0 )
	{
		// if we found the log entry for the given address
		if( pEntry->pNext->pAddress == addr )
		{
			void* entry = pEntry->pNext;

			// remove it
			pEntry->pNext = pEntry->pNext->pNext;

			// release it's memory
			free(entry);

			return;
		}

		pEntry = pEntry->pNext;
	}
}

void SendDebugMessage(const char*);

void VMemLogger::PrintLeakReport()
{
#ifdef V3D_MEM_ENABLE_LOGGING
	char buffer[1000];

	std::sprintf(buffer, "Leak report\n");
	std::printf("%s", buffer);
	SendDebugMessage(buffer);

	VMemLogEntry* pEntry = firstLog.pNext;
	long nLeakCount = 0;
	size_t nLeakSize = 0;

	while(pEntry != 0 && pEntry != &lastLog )
	{
		std::sprintf(buffer, "[%s#%s:%d] Size %d\n", 
			pEntry->pModuleName,
			pEntry->pFileName, 
			pEntry->nLine, 
			int(pEntry->nSize));
		std::printf("%s", buffer);
		SendDebugMessage(buffer);
		
		++nLeakCount;
		nLeakSize += pEntry->nSize;

		pEntry = pEntry->pNext;
	}

	std::sprintf(buffer, "\n%d bytes allocated in %d allocations\n",
		int(GetTotalAllocatedMem()), int(GetTotalAllocations()));
	std::printf("%s", buffer);
	SendDebugMessage(buffer);

	std::sprintf(buffer, "%d releases\n", GetTotalReleases());
	std::printf("%s", buffer);
	SendDebugMessage(buffer);

	std::sprintf(buffer, "\n%d bytes of memory leaked in %d places\n\n", 
		nLeakSize, nLeakCount);
	std::printf("%s", buffer);
	SendDebugMessage(buffer);
#else // no logging enabled
	SendDebugMessage("\n\nNo memory logging information available\n\n");
#endif // V3D_MEM_ENABLE_LOGGING
}

namespace v3d {
	void SetOwnerStatus(
		v3d::VStringParam in_sFile,
		v3d::vlong in_iLine,
		v3d::VStringParam in_sFunction
		)
	{
#ifdef V3D_MEM_ENABLE_LOGGING
		currentMemOp.pFileName = in_sFile;
		currentMemOp.nLine = in_iLine;
		//currentMemOp.pFunction = in_sFunction;
#endif
	}

	void* AllocMem(size_t size)
	{
		// allocate the memory
		void* addr = malloc(size);

#ifdef V3D_MEM_ENABLE_LOGGING
		// store logging info
		currentMemOp.pAddress = addr;
		currentMemOp.nSize = size;

		LogMemAlloc(currentMemOp);

#ifdef V3D_MEM_SHOW_ALLOCRELEASE
		printf("Allocation: %s[%d] %d bytes @ %p\n",
			currentMemOp.pFileName, int(currentMemOp.nLine),
			int(size), addr);
#else
#ifdef V3D_MEM_SHOW_SHORTALLOCRELEASE
		printf(".a.");
#endif // V3D_MEM_SHOW_SHORTALLOCRELEASE
#endif // V3D_MEM_SHOW_ALLOCRELEASE

		currentMemOp.Clear();
#endif // V3D_MEM_ENABLE_LOGGING
		return addr;
	}

	void FreeMem(void* addr)
	{
#ifdef V3D_MEM_ENABLE_LOGGING
		// log release of memory
		currentMemOp.pAddress = addr;
		LogMemRelease(currentMemOp);

#ifdef V3D_MEM_SHOW_ALLOCRELEASE
		printf("Release:    %s[%d] @ %p\n",
			currentMemOp.pFileName, int(currentMemOp.nLine), addr);
#else
#ifdef V3D_MEM_SHOW_SHORTALLOCRELEASE
		printf(".r.");
#endif
#endif // V3D_MEM_SHOW_ALLOCRELEASE

		currentMemOp.Clear();
#endif // V3D_MEM_ENABLE_LOGGING

		// release memory
		free(addr);
	}
} // namespace v3d

//-----------------------------------------------------------------------------
// public usage info:

namespace v3d { namespace mem {
	vulong GetTotalAllocationCalls() 
	{
		if( pMemLogger != 0 )
			return pMemLogger->GetTotalAllocations();
		else
			return 0;
	}

	vulong GetTotalReleaseCalls()
	{
		if( pMemLogger != 0 )
			return pMemLogger->GetTotalReleases();
		else
			return 0;
	}

	size_t GetTotalAllocatedMemory()
	{
		if( pMemLogger != 0 )
			return pMemLogger->GetTotalAllocatedMem();
		else
			return 0;
	}

	size_t GetTotalReleasedMemory()
	{
		if( pMemLogger != 0 )
			return pMemLogger->GetTotalReleasedMem();
		else
			return 0;
	}

	size_t GetCurrentUsedMemory()
	{
		if( pMemLogger != 0 )
			return pMemLogger->GetCurrentUsedMem();
		else
			return 0;
	}

	void PrintLeakReport()
	{
		if( pMemLogger != 0 )
			pMemLogger->PrintLeakReport();
		else
		{
			SendDebugMessage("no memory logger available");
		}
	}

	void EnableLogging()
	{
		if( pMemLogger != 0 )
			GetLocalMemLogger()->EnableLogging();
	}

}} // namespace v3d::mem

#ifdef V3D_WIN32

#include <windows.h>

void SendDebugMessage(const char* text)
{
	OutputDebugString(text);
}
#else // V3D_WIN32

void SendDebugMessage(const char* text)
{
    // empty default implementation - nsn
    // FIXME
}
#endif // V3D_WIN32

//-----------------------------------------------------------------------------

#ifndef V3D_VMEMMANAGER_H
#define V3D_VMEMMANAGER_H

#include <Core/VTypes.h>

#include <string>

#ifndef __FUNCTION__
	#define	__FUNCTION__ "??"
#endif

namespace VMemManager
{
	class VAllocationUnit
	{
	public :
		
		vint				m_iActualSize;
		vint				m_iReportedSize;
		void*				m_pActualAddress;
		void*				m_pReportedAddress;
		vchar				m_szSourceFile[40];
		vchar				m_szSourceFunc[40];
		vuint				m_uiSourceLine;
		vuint				m_uiAllocationType;
		vbool				m_bBreakOnDealloc;
		vbool				m_bBreakOnRealloc;
		vuint				m_uiAllocationNumber;
		VAllocationUnit*	m_pNext;
		VAllocationUnit*	m_pPrev;
	};

	class VStats
	{
	public :

		vuint				m_uiTotalReportedMemory;
		vuint				m_uiTotalActualMemory;
		vuint				m_uiPeakReportedMemory;
		vuint				m_uiPeakActualMemory;
		vuint				m_uiAccumulatedReportedMemory;
		vuint				m_uiAccumulatedActualMemory;
		vuint				m_uiAccumulatedAllocUnitCount;
		vuint				m_uiTotalAllocUnitCount;
		vuint				m_uiPeakAllocUnitCount;
	};

	extern const vuint		ALLOC_UNKNOWN;
	extern const vuint		ALLOC_NEW;
	extern const vuint		ALLOC_NEW_ARRAY;
	extern const vuint		ALLOC_MALLOC;
	extern const vuint		ALLOC_CALLOC;
	extern const vuint		ALLOC_REALLOC;
	extern const vuint		ALLOC_DELETE;
	extern const vuint		ALLOC_DELETE_ARRAY;
	extern const vuint		ALLOC_FREE;

	void					SetOwner(const vchar* in_pszFile, const vuint in_uiLine, const vchar* in_pszFunc);
	vbool&					BreakOnRealloc(void* in_pReportedAddress);
	vbool&					BreakOnDealloc(void* in_pReportedAddress);
	void*					Allocator(const vchar *sourceFile, const vuint in_uiSourceLine, 
								const vchar* in_pszSourceFunc, const vuint in_uiAllocationType, 
								const vuint in_uiReportedSize);
	void*					Reallocator(const vchar* in_pszSourceFile, const vuint in_uiSourceLine, 
								const vchar* in_pszSourceFunc, const vuint in_uiReallocationType, 
								const vuint in_uiReportedSize, void* in_pReportedAddress);
	void					Deallocator(const vchar* in_pszSourceFile, const vuint in_uiSourceLine, 
								const vchar* in_pszSourceFunc, const vuint in_uiDeallocationType, 
								const void* in_pReportedAddress);
	vbool					ValidateAddress(const void* in_pReportedAddress);
	vbool					ValidateAllocUnit(const VAllocationUnit* in_pAllocationUnit);
	vbool					ValidateAllAllocUnits(void);
	vuint					CalcUnused(const VAllocationUnit* in_pAllocationUnit);
	vuint					CalcAllUnused(void);
	void					DumpAllocUnit(const VAllocationUnit* in_pAllocationUnit, 
								const vchar* in_pszPrefix = "");
	void					DumpMemoryReport(const vchar* in_pszFilename = "memreport.log", 
								const vbool in_bOverwrite = true);
	VStats					GetMemoryStatistics(void);
};

void*						operator new (vuint in_uiReportedSize);
void*						operator new [] (vuint in_uiReportedSize);
void*						operator new (vuint in_iReportedSize, const vchar* in_pszSourceFile, vuint in_uiSourceLine);
void*						operator new [] (vuint in_iReportedSize, const vchar* in_pszSourceFile, vuint in_uiSourceLine);
void						operator delete (void* in_pReportedAddress);
void						operator delete [] (void* in_pReportedAddress);

#endif // V3D_VMEMMANAGER_H

#ifdef	new
	#undef	new
#endif

#ifdef	delete
	#undef	delete
#endif

#ifdef	malloc
	#undef	malloc
#endif

#ifdef	calloc
	#undef	calloc
#endif

#ifdef	realloc
	#undef	realloc
#endif

#ifdef	free
	#undef	free
#endif

#define	new				(VMemManager::SetOwner(__FILE__,__LINE__,__FUNCTION__),false) ? NULL : new
#define	delete			(VMemManager::SetOwner(__FILE__,__LINE__,__FUNCTION__),false) ? VMemManager::SetOwner("",0,"") : delete
#define	malloc(sz)		VMemManager::Allocator(__FILE__,__LINE__,__FUNCTION__,VMemManager::ALLOC_MALLOC,sz)
#define	calloc(sz)		VMemManager::Allocator(__FILE__,__LINE__,__FUNCTION__,VMemManager::ALLOC_CALLOC,sz)
#define	realloc(ptr,sz)	VMemManager::Reallocator(__FILE__,__LINE__,__FUNCTION__,VMemManager::ALLOC_REALLOC,sz,ptr)
#define	free(ptr)		VMemManager::Deallocator(__FILE__,__LINE__,__FUNCTION__,VMemManager::ALLOC_FREE,ptr)
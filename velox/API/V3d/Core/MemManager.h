#include <cstdlib>
#include <new>
//-----------------------------------------------------------------------------
//#define	__FUNCTION__ "??"
//-----------------------------------------------------------------------------
namespace v3d {
	typedef const char* VStringParam;
	typedef long vlong;
	typedef unsigned long vulong;

	// interface to get memory usage info
	namespace mem {
		vulong GetTotalAllocationCalls();
		vulong GetTotalReleaseCalls();

		size_t GetTotalAllocatedMemory();
		size_t GetTotalReleasedMemory();

		size_t GetCurrentUsedMemory();

		void PrintLeakReport();
		
		void EnableLogging();
	} // namespace mem

	/** 
	 * sets the line, file and function of the last allocation
	 * never call this function
	 */
	void SetOwnerStatus(
		v3d::VStringParam in_sFile,
		v3d::vlong in_iLine,
		v3d::VStringParam in_sFunction
		);

	/** 
	 * used internally by the mem manager to allocate memory, do not use
	 * call this yourself
	 */
	void* AllocMem(size_t size);

	/**
	 * used internally by the mem manager to release memory, do not call
	 * this function yourself
	 */
	void FreeMem(void* addr);

	class IVMemLogger;

	/** returns the memory allocation/release logger. for use by kernel only */
	IVMemLogger* GetMemLogger();
	/** sets a new memory logger. for use by kernel only */
	void SetMemLogger(IVMemLogger* in_pMemLogger);
} // namespace v3d

//-----------------------------------------------------------------------------

static void *operator new(size_t size)
{
	return v3d::AllocMem(size);
}

static void *operator new[](size_t size)
{
	return v3d::AllocMem(size);
}

static void operator delete(void* size)
{
	v3d::FreeMem(size);
}

static void operator delete[](void* size)
{
	v3d::FreeMem(size);
}

//-----------------------------------------------------------------------------
#define	new	(SetOwnerStatus(__FILE__,__LINE__, "???"),false) ? NULL : new
#define delete (SetOwnerStatus(__FILE__,__LINE__, "???"),false) ? NULL : delete
//-----------------------------------------------------------------------------
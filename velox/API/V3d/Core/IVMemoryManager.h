#ifndef V3D_IVMEMORYMANAGER_2004_07_19_H
#define V3D_IVMEMORYMANAGER_2004_07_19_H
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * Collects information about allocated memory (for debug versions, etc)
 *
 * @author sheijk
 */
struct IVMemoryManager
{
	virtual void* Allocate(
		unsigned int in_nSize, 
		const char* in_pcModuleName
		) = 0;

	virtual void Free(void* in_pAddress, const char* in_pcModuleName) = 0;

	virtual void SetOwnerStatus(
		const char* in_sFile,
		long in_iLine,
		const char* in_sFunction
		) = 0;
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVMEMORYMANAGER_2004_07_19_H
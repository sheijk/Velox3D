#ifndef V3D_IVTEMPDATAPROVIDER_H
#define V3D_IVTEMPDATAPROVIDER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VNamedObject.h>
#include <v3d/Vfs/IVStream.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Provides a method to create a temporal file on disc
 */

class IVTempDataProvider : VNamedObject
{
public:

	IVTempDataProvider(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent)
	{
	}
		
	/**
	 * Copies the buffer into a file on disc ind returns local file name
	 * @param in_pBuffer: the buffer to be copied
	 *        in_nBytes:  size to be copied
	 */

	virtual VStringParam CreateFile(void* in_pBuffer, vuint in_nBytes) = 0;
	
	/**
	 * Writes the stream into a binary flile
	 */
	virtual VStringParam CreateFile(IVStream* in_pStream) = 0;

	/**
	 * Returns an empty file name
	 */

	virtual VStringParam CreateFile() = 0;
    	
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVTEMPDATAPROVIDER_H

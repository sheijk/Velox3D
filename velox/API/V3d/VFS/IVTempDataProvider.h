/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVTEMPDATAPROVIDER_H
#define V3D_IVTEMPDATAPROVIDER_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VNamedObject.h>
#include <V3d/VFS/IVStream.h>
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Provides a method to create a temporal files on disc
 * @author: ins
 */
#undef CreateFile //windows defines sucks..
class IVTempDataProvider : public VNamedObject
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
	 * Writes the stream into a binary file
	 */
	virtual VStringParam CreateFile(IVStream* in_pStream) = 0;

	/**
	 * Returns an empty file name
	 */

	virtual VStringParam CreateFile() = 0;

	virtual ~IVTempDataProvider() {}
};

//-----------------------------------------------------------------------------
} // namespace vfs
template<>
inline v3d::vfs::IVTempDataProvider* QueryService<v3d::vfs::IVTempDataProvider>()
{
	return QueryObject<v3d::vfs::IVTempDataProvider>("tempfile.service");
}
} // namespace v3d
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#endif // V3D_IVTEMPDATAPROVIDER_H


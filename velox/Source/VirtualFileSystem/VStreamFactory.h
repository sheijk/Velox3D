/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VStreamFactory_H
#define V3D_VStreamFactory_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/VFS/IVStreamFactory.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
//TODO: insert documentation here
*/
class VStreamFactory : public IVStreamFactory
{
public:
	VStreamFactory(VStringParam in_strName);
	virtual ~VStreamFactory();

	virtual FileStreamPtr CreateFileStream(
		VStringParam in_strName, 
		VCreationFlags in_OpenMode,
		VAccessModeFlags in_Access);

	virtual StreamPtr CreateMemoryStream(
		IVStream::ByteCount in_nInitialSize = 0);
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VStreamFactory_H


/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVFile_H
#define V3D_IVFile_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/VFS/IVFileSysObject.h>
#include <v3d/VFS/VFlags.h>
#include <v3d/VFS/IVBufferStream.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Represents a file. Use it to get information about files and to open them
 */
class IVFile : public IVFileSystemObject
{
public:
	virtual ~IVFile() {};

	/** a (smart) pointer to a file stream */
	typedef VSharedPtr<IVBufferStream> FileStreamPtr;

	/** opens the file with the given access mode */
	virtual FileStreamPtr Open(VAccessModeFlags in_Access) const = 0;

	/** delete the content of the file and set it's size to 0 */
	virtual void Clear() = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVFile_H


/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VACCESSRIGHTS_H
#define V3D_VACCESSRIGHTS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Interface for getting access rights for a file system object.
 * Each function returns whether a specific operations may be performed
 * on the associated object. (the associated object is the one which
 * returned this interface)
 */
class IVAccessRights
{
public:
	virtual ~IVAccessRights() {};

	/** Returns whether it is allowed to create a file inside dir */
	virtual vbool AllowCreateFile() const = 0;

	/** Retuns whether it is allowed to create a subdirectory in dir */
	virtual vbool AllowCreateDir() const = 0;
	
	/** Returns whether it's allowed delete the current element */
	virtual vbool AllowDelete() const = 0;
	
	/** Returns whether the content of the dir/file may be read */
	virtual vbool AllowReadAccess() const = 0;
	
	/** Returns whether data may be written to the file */
	virtual vbool AllowWriteAccess() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VACCESSRIGHTS_H


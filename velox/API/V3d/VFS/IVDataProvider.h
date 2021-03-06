/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVDataProvider_H
#define V3D_IVDataProvider_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/VFS/VFlags.h>
#include <V3d/VFS/IVOfflineStream.h>
#include <V3d/VFS/VMountOptions.h>
#include <V3d/VFS/IVDirectory.h>
#include <V3d/VFS/IVFile.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------
class VDirectory;

// fix some of the troubles caused by windows.h
#undef CreateFile

/**
 * A "plugin" that can create a stream from an xml file descriptions. 
 * Registers itself to the vfs, handles all file descriptions with 
 * a specific "type" attribute
 */
class IVDataProvider
{
public:
	virtual ~IVDataProvider() {}

	typedef VPointer<IVBufferStream>::SharedPtr StreamPtr;
	typedef VPointer<IVDirectory>::SharedPtr DirPtr;
	typedef VPointer<IVFile>::SharedPtr FilePtr;

	/** returns the type id */
	virtual VStringRetVal GetId() const = 0;

	/** opens a (virtual) file */
	virtual StreamPtr OpenFile(
		VStringParam in_strSource, 
		VAccessModeFlags in_Access) = 0;

	/** creates a dir from mount info */
	virtual DirPtr CreateMountedDir(
		IVDirectory* in_pParent, const VMountOptions& in_MountOptions) = 0;

	virtual void UpdateDir(const std::string& path, VDirectory* io_pDir) = 0;

	virtual vbool IsDirectory(VStringParam in_strPossibleDir) = 0;
	virtual vbool IsFile(VStringParam in_strPossibleFile) = 0;

	// create files (?)
	virtual DirPtr CreateDir(const VMountOptions& in_Options) = 0;
	virtual void DeleteDir(VStringParam in_strDir) = 0;
	virtual FilePtr CreateFile(const VMountOptions& in_Options) = 0;
	virtual void DeleteFile(VStringParam in_strSource) = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs 
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDataProvider_H


/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VAccessRights_H
#define V3D_VAccessRights_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVAccessRights.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/VFS/VAccessRightsFlags.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
//TODO: insert documentation here
*/
class VAccessRights : public IVAccessRights
{
public:
	typedef VPointer<IVAccessRights>::SharedPtr AccessRightsPtr;

	enum AccessType 
	{ 
		NoAccess = 0, ReadAccess = 1, 
		WriteAccess = 2, RWAccess = 3 
	};

	enum DeleteMode { DeletingAllowed, DeletingForbidden };
private:
	vbool m_bAllowCreateFile;
	vbool m_bAllowCreateDir;
	vbool m_bAllowDelete;
	vbool m_bAllowReadAccess;
	vbool m_bAllowWriteAccess;

	static vbool FlagsSet(AccessType val, AccessType flags);

public:
	VAccessRights(vbool alwCF, vbool alwCD, 
		vbool alwDel, vbool alwRA, vbool alwWA);

	VAccessRights(const VAccessRightsFlags& accRightFlags);

	VAccessRights(const IVAccessRights& source);

	virtual ~VAccessRights();

	/** creates acccess rights for a file */
	static AccessRightsPtr CreateFileAR(AccessType access, DeleteMode dm);
	
	/** creates access rights for a dir where no files or subdirs
		can be created */
	static AccessRightsPtr CreateRODirAR(DeleteMode dm);

	/** creates access rights for a dir where files and subdirs 
		can be created */
	static AccessRightsPtr CreateDirAR(DeleteMode dm);

	virtual vbool AllowCreateFile() const;
	virtual vbool AllowCreateDir() const;
	virtual vbool AllowDelete() const;
	virtual vbool AllowReadAccess() const;
	virtual vbool AllowWriteAccess() const;
};

VAccessRights::AccessType GetAccMode(vbool alwRead, vbool alwWrite);
VAccessRights::AccessType GetAccMode(IVAccessRights& ar);
VAccessRights::DeleteMode GetDelMode(vbool alwDel);

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VAccessRights_H


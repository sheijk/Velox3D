#include "VAccessRights.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VAccessRights::VAccessRights(
	vbool alwCF, vbool alwCD, vbool alwDel, 
	vbool alwRA, vbool alwWA)
{
	m_bAllowCreateFile = alwCF;
	m_bAllowCreateDir = alwCD;
	m_bAllowDelete = alwDel;
	m_bAllowReadAccess = alwRA;
	m_bAllowWriteAccess = alwWA;
}

VAccessRights::VAccessRights(const VAccessRightsFlags& accRightFlags)
{
	m_bAllowCreateFile = accRightFlags.allowCreateFile;
	m_bAllowCreateDir = accRightFlags.allowCreateDir;
	m_bAllowReadAccess = accRightFlags.allowRead;
	m_bAllowWriteAccess = accRightFlags.allowWrite;
	m_bAllowDelete = accRightFlags.allowDelete;
}

VAccessRights::VAccessRights(const IVAccessRights& source)
{
	m_bAllowCreateFile = source.AllowCreateFile();
	m_bAllowCreateDir = source.AllowCreateDir();
	m_bAllowDelete = source.AllowDelete();
	m_bAllowReadAccess = source.AllowReadAccess();
	m_bAllowWriteAccess = source.AllowWriteAccess();
}

/**
 * d'tor
 */
VAccessRights::~VAccessRights()
{
}

vbool VAccessRights::FlagsSet(AccessType val, AccessType flags)
{
	return (val & flags) == flags;
}

VAccessRights::AccessRightsPtr VAccessRights::CreateFileAR(
	AccessType access, DeleteMode dm)
{
	return AccessRightsPtr( new VAccessRights(
		false, false, dm == DeletingAllowed, 
		FlagsSet(access, ReadAccess), FlagsSet(access, WriteAccess)) );
}

VAccessRights::AccessRightsPtr VAccessRights::CreateRODirAR(DeleteMode dm)
{
	return AccessRightsPtr( new VAccessRights(
		false, false, dm == DeletingAllowed, true, true) );
}

VAccessRights::AccessRightsPtr VAccessRights::CreateDirAR(DeleteMode dm)
{
	return AccessRightsPtr( new VAccessRights(
		true, true, dm == DeletingAllowed, true, true) );
}

vbool VAccessRights::AllowCreateFile() const
{
	return m_bAllowCreateFile;
}

vbool VAccessRights::AllowCreateDir() const
{
	return m_bAllowCreateDir;
}

vbool VAccessRights::AllowDelete() const
{
	return m_bAllowDelete;
}

vbool VAccessRights::AllowReadAccess() const
{
	return m_bAllowReadAccess;
}

vbool VAccessRights::AllowWriteAccess() const
{
	return m_bAllowWriteAccess;
}

VAccessRights::AccessType GetAccMode(vbool alwRead, vbool alwWrite)
{
	int mode = VAccessRights::NoAccess;

	if( alwRead ) mode |= VAccessRights::ReadAccess;
	if( alwWrite) mode |= VAccessRights::WriteAccess;

	return (VAccessRights::AccessType)mode;
}

VAccessRights::AccessType GetAccMode(IVAccessRights& ar)
{
	return GetAccMode(ar.AllowReadAccess(), ar.AllowWriteAccess());
}

VAccessRights::DeleteMode GetDelMode(vbool alwDel)
{
	return alwDel ? 
		VAccessRights::DeletingAllowed : 
		VAccessRights::DeletingForbidden;
}
//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------

#include "VFile.h"
//-----------------------------------------------------------------------------
#include <v3d/VFS/IVAccessRights.h>
#include <v3d/VFS/IVDataProvider.h>
#include <v3d/VFS/IVDataProviderPool.h>
#include <v3d/Core/VObjectRegistry.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VFile::VFile()
{
}

VFile::VFile(const CreationInfo& in_Descr)
{
	m_strName = in_Descr.name;
	m_strSource = in_Descr.source;
	m_strTypeId = in_Descr.type;
}

/**
 * d'tor
 */
VFile::~VFile()
{
}

VStringRetVal VFile::GetName() const
{
	return VStringRetVal(m_strName.c_str());
}

VStringRetVal VFile::GetPath() const
{
	return VStringRetVal(m_strPath.c_str());
}

IVFileSystemObject::AccessRightsPtr VFile::GetAccessRights() const
{
	return m_pAccessRights.Get();
}
	
IVFile::FileStreamPtr VFile::Open(VAccessModeFlags in_Access) const
{
	// get data provider
	IVDataProviderPool* pDPP = QueryObject<IVDataProviderPool>("vfs.dpp");
	IVDataProvider& dataProv = pDPP->GetDataProvider(m_strTypeId.c_str());

	// let it create a stream
	return dataProv.OpenFile(m_strSource.c_str(), in_Access);
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------

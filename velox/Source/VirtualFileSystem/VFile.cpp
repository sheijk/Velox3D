#include "VFile.h"
//-----------------------------------------------------------------------------
#include <v3d/VFS/IVAccessRights.h>
#include <v3d/VFS/IVDataProvider.h>
#include <v3d/VFS/IVDataProviderPool.h>
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/VFS/VIOException.h>

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
	m_pAccessRights = in_Descr.pAccRights;
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

VStringRetVal VFile::GetSource() const
{
	return VStringRetVal(m_strSource.c_str());
}

IVFileSystemObject::AccessRightsPtr VFile::GetAccessRights() const
{
	return m_pAccessRights.Get();
}
	
IVFile::FileStreamPtr VFile::Open(VAccessModeFlags in_Access) const
{
	// check access rights
	if( (in_Access & VReadAccess == VReadAccess) 
		&& (! m_pAccessRights->AllowReadAccess()) )
	{
		V3D_THROW(VIllegalOperationException, 
			("file \"" + m_strName + "\" does not allow read access").c_str());
	}

	if( (in_Access & VWriteAccess == VWriteAccess)
		&& (! m_pAccessRights->AllowWriteAccess()) )
	{
		V3D_THROW(VIllegalOperationException,
			("file \"" + m_strName + "\" does not allow write access").c_str());
	}

	// get data provider
	IVDataProviderPool* pDPP = QueryObject<IVDataProviderPool>("vfs.dpp");
	IVDataProvider& dataProv = pDPP->GetDataProvider(m_strTypeId.c_str());

	// let it create a stream
	return dataProv.OpenFile(m_strSource.c_str(), in_Access);
}

void VFile::Clear()
{
	// open the file
	FileStreamPtr pFileStream = this->Open(VWriteAccess);

	// and set it's size to zero
	pFileStream->SetSize(0);
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------

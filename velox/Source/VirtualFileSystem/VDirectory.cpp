#include "VDirectory.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/VFS/IVAccessRights.h>
#include <v3d/Core/Wrappers/VSTLDerefIteratorPol.h>
#include <v3d/VFS/VIOException.h>
#include <v3d/VFS/IVDataProviderPool.h>
#include <v3d/Core/VObjectRegistry.h>

#include "VfsUtils.h"
#include "VAccessRights.h"

#include <algorithm>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VDirectory::VDirectory()
{
}

VDirectory::VDirectory(
	std::string in_strName, 
	std::string in_strTypeId,
	std::string in_strSource,
	SharedAccessRightsPtr in_pAccessRights)
{
	m_strName = in_strName;
	m_strTypeId = in_strTypeId;
	m_strSource = in_strSource;

	m_pAccessRights = in_pAccessRights;
}

/**
 * d'tor
 */
VDirectory::~VDirectory()
{
}

VStringRetVal VDirectory::GetName() const
{
	return VStringRetVal(m_strName.c_str());
}

VStringRetVal VDirectory::GetSource() const
{
	return VStringRetVal(m_strSource.c_str());
}

IVFileSystemObject::AccessRightsPtr VDirectory::GetAccessRights() const
{
	return m_pAccessRights.Get();
}

IVDirectory::DirIterRange VDirectory::SubDirs()
{
	typedef VSTLDerefIteratorPol<
		DirList::iterator, 
		IVDirectory> DirIterPol;

	return DirIterRange(
		DirIter(new DirIterPol(m_Dirs.begin())),
		DirIter(new DirIterPol(m_Dirs.end())) );
}

IVDirectory::ConstDirIterRange VDirectory::SubDirs() const
{
	typedef VSTLDerefIteratorPol<
		DirList::const_iterator, 
		const IVDirectory
	> DirIterPol;

	return ConstDirIterRange(
		ConstDirIter(new DirIterPol(m_Dirs.begin())),
		ConstDirIter(new DirIterPol(m_Dirs.end())) );
}

IVDirectory::FileIterRange VDirectory::Files()
{
	typedef VSTLDerefIteratorPol<
		FileList::iterator, 
		IVFile
	> FileIterPol;

	return FileIterRange(
		FileIter(new FileIterPol(m_Files.begin())),
		FileIter(new FileIterPol(m_Files.end())) );
}

IVDirectory::ConstFileIterRange VDirectory::Files() const
{
	typedef VSTLDerefIteratorPol<
		FileList::const_iterator, 
		const IVFile
	> FileIterPol;

	return ConstFileIterRange(
		ConstFileIter(new FileIterPol(m_Files.begin())),
		ConstFileIter(new FileIterPol(m_Files.end())) );
}

void VDirectory::AddSubdir(DirPtr in_pSubdir)
{
	m_Dirs.push_back(in_pSubdir);
}

void VDirectory::AddFile(FilePtr in_pFile)
{
	m_Files.push_back(in_pFile);
}

IVDirectory& VDirectory::CreateSubdir(
	VStringParam in_strName,
	const VAccessRightsFlags& in_AccessRights)
{
	// check access rights
	if( GetAccessRights()->AllowCreateDir() )
	{
		// let the data provider create the subdir
		IVDataProviderPool* pDPP = QueryObject<IVDataProviderPool>("vfs.dpp");
		IVDataProvider* pDP = &(pDPP->GetDataProvider(m_strTypeId.c_str()));

		VMountOptions mountOptions;
		mountOptions.SetName(in_strName);
		mountOptions.SetAccessRights(VMountOptions::AccessRightsPtr(
			new VAccessRights(in_AccessRights)));
		mountOptions.SetSource(m_strSource.c_str());
		mountOptions.SetType(m_strTypeId.c_str());

		IVDataProvider::DirPtr pDir = pDP->CreateDir(mountOptions);

		// add the subdir
		this->AddSubdir(pDir);

		return *pDir;
	}
	// throw exception if creation of subdirs is prohibited
	else
	{
		V3D_THROW(VIllegalOperationException, "tried to create subdir in "
			"directory without permission");
	}
}

/**
 * wraps Result function(T*) to Result f(T) oder Result f(T&)
 * for STL style functors
 */
template<
	typename Func, 
	typename Result, 
	typename T, 
	typename SmartPointer = T* >
class VDerefPtr
{
	Func f;
public:
	VDerefPtr(Func ff) : f(ff) {}

	Result operator()(SmartPointer pT)
	{
		return f(*pT);
	}
};

//TODO: use this function everywhere in this file and add it to VDirectory
IVDataProvider* GetDataProvider(std::string in_strId)
{
	IVDataProviderPool* pDPP = QueryObject<IVDataProviderPool>("vfs.dpp");
	return &(pDPP->GetDataProvider(in_strId.c_str()));
}

void VDirectory::DeleteSubdir(VStringParam in_strName)
{
	// find subdir
	DirList::iterator dirIt = std::find_if(
		m_Dirs.begin(), m_Dirs.end(), 
		VDerefPtr<VCompareFSOName, vbool, IVFileSystemObject, DirPtr>(
			VCompareFSOName(in_strName)));

	// if dir does not exist there's no need to delete it
	if( m_Dirs.end() == dirIt ) 
	{
		return;
	}

	// check permission to delete dirs
	if( (*dirIt)->GetAccessRights()->AllowDelete() )
	{
		std::string dirToBeRemoved = (*dirIt)->GetSource().AsCString();

		// remove the directory from subdir list
		m_Dirs.erase(dirIt);

		// let the data provider delete the directory
		GetDataProvider(m_strTypeId)->DeleteDir(dirToBeRemoved.c_str());
	}
	//TODO: exception werfen wenn fehlende rechte
}

void VDirectory::CreateFile(
	VStringParam in_strName,
	const VAccessRightsFlags& in_AccessRights)
{

	if( GetAccessRights()->AllowCreateFile() )
	{
		VMountOptions mountOpt;
		mountOpt.SetName(in_strName);
		mountOpt.SetSource(GetSource());
		mountOpt.SetType(m_strTypeId.c_str());
		mountOpt.SetAccessRights(VMountOptions::AccessRightsPtr(
			new VAccessRights(in_AccessRights)));

		// let the data provider create the file
		IVDataProvider::FilePtr pFile 
			= GetDataProvider(m_strTypeId.c_str())->CreateFile(mountOpt);

		// add a file representation
		AddFile(pFile);
	}
	else
	{
		std::string message = "tried to create file \"";
		message += in_strName;
		message += "\", in dir \"";
		message += GetName();
		message += "\"without permission";

		V3D_THROW(VIllegalOperationException, message.c_str());
	}
}

void VDirectory::DeleteFile(VStringParam in_strName)
{
	// find file
	FileList::iterator fileIt = std::find_if(
		m_Files.begin(), m_Files.end(),
		VDerefPtr<VCompareFSOName, vbool, IVFile, FilePtr>(
		VCompareFSOName(in_strName)) );

	if( m_Files.end() == fileIt )
		return;

	// check access rights
	if( (*fileIt)->GetAccessRights()->AllowDelete() )
	{
		std::string fileToBeRemoved = (*fileIt)->GetSource().AsCString();

		// remove from files list
		m_Files.erase(fileIt);

		// delete file
		GetDataProvider(m_strTypeId)->DeleteFile(fileToBeRemoved.c_str());
	}
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------

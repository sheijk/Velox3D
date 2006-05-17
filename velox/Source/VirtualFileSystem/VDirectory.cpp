#include "VDirectory.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/VFS/IVAccessRights.h>
#include <v3d/VFS/VIOException.h>
#include <v3d/VFS/IVDataProviderPool.h>
#include <v3d/Core/VObjectRegistry.h>

#include "VfsUtils.h"
#include "VAccessRights.h"
#include <V3d/VFS/IVDataProviderPool.h>

#include <V3d/Core/VIOStream.h>
#include <V3d/Core/VLogging.h>

#include <algorithm>
//-----------------------------------------------------------------------------
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
	m_pParent = 0;
}

VDirectory::VDirectory(
	IVDirectory* in_pParent,
	std::string in_strName, 
	std::string in_strTypeId,
	std::string in_strSource,
	SharedAccessRightsPtr in_pAccessRights)
{
	m_pParent = in_pParent;

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

IVDirectory::DirIter VDirectory::SubDirs()
{
	Update();

	return CreateDerefIterator<IVDirectory>(m_Dirs.begin(), m_Dirs.end());
}

IVDirectory::ConstDirIter VDirectory::SubDirs() const
{
	Update();

	return CreateDerefIterator<const IVDirectory>(m_Dirs.begin(), m_Dirs.end());
}

IVDirectory::FileIter VDirectory::Files()
{
	Update();

	return CreateDerefIterator<IVFile>(m_Files.begin(), m_Files.end());
}

IVDirectory::ConstFileIter VDirectory::Files() const
{
	Update();

	return CreateDerefIterator<const IVFile>(m_Files.begin(), m_Files.end());
}

void VDirectory::AddSubdir(DirPtr in_pSubdir)
{
	if( GetSubDir(in_pSubdir->GetName()) == 0)
		m_Dirs.push_back(in_pSubdir);
}

void VDirectory::AddFile(FilePtr in_pFile)
{
	if( GetFile(in_pFile->GetName()) == 0 )
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

IVDataProvider* VDirectory::MyDataProvider() const
{
	return &VServicePtr<IVDataProviderPool>()->GetDataProvider(m_strTypeId.c_str());
}

std::string VDirectory::GetQualifiedName() const
{
	if( GetParent() != 0 )
	{
		return GetParent()->GetQualifiedName() + "/" + m_strName;
	}
	else
	{
		return "";
	}		
}

IVDirectory* VDirectory::GetParent()
{
	return m_pParent;
}

const IVDirectory* VDirectory::GetParent() const
{
	return m_pParent;
}

template<typename T>
T* non_const(const T* t)
{
	return const_cast<T*>(t);
}

void VDirectory::Update() const
{
	try
	{
		if( m_strTypeId.empty() == false )
		{
			VDirectory* self = non_const(this);
			MyDataProvider()->UpdateDir(m_strSource, non_const(this));
		}
	}
	catch(VException& e)
	{
		V3D_LOGLN("error: " << e.ToString());
	}
}

IVDirectory* VDirectory::GetSubDir(const VString& name)
{
	for(DirList::iterator dir = m_Dirs.begin(); dir != m_Dirs.end(); ++dir)
	{
		if( (*dir)->GetName() == name )
			return dir->Get();
	}

	return 0;
}

IVFile* VDirectory::GetFile(const VString& name)
{
	for(FileList::iterator file = m_Files.begin(); file != m_Files.end(); ++file)
	{
		if( (*file)->GetName() == name )
			return file->Get();
	}

	return 0;
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------

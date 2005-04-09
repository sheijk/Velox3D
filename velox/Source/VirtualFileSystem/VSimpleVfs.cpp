#include "VSimpleVfs.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>

#include <v3d/VFS/IVStreamFactory.h>
#include <v3d/VFS/IVAccessRights.h>
#include <v3d/VFS/VIOException.h>
#include <v3d/VFS/IVDataProviderPool.h>
#include <v3d/VFS/VMountOptions.h>

#include <V3d/Utils/VSimpleTokenizer.h>

#include <v3d/XML/IVXMLService.h>

#include "VFile.h"
#include "VDirectory.h"
#include "VAccessRights.h"
#include "VfsUtils.h"
#include "VxmlIniReader.h"

#include <algorithm>
#include <string>

#include <boost/filesystem/operations.hpp>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

IVDataProvider& GetDataProvider(std::string in_strId)
{
	//TODO: make static member and cache data prov. pool

	IVDataProviderPool* pDPP = QueryObject<IVDataProviderPool>("vfs.dpp");

	return pDPP->GetDataProvider(in_strId.c_str());
}

/**
 * standard c'tor
 */
VSimpleVfs::VSimpleVfs(
					   VStringParam in_strName, 
					   VStringParam in_strCfgFile,
					   VNamedObject* in_pParent)
	: IVFileSystem(in_strName, in_pParent)
{
	// create root dir
	m_pRootDirSP.Assign(new VDirectory(
		"",
		"",
		boost::filesystem::current_path().string(),
		VAccessRights::CreateRODirAR(VAccessRights::DeletingForbidden)));

	// load vfs.xml file
	ParseInitFile();
}

void VSimpleVfs::ParseInitFile()
{
	// create visitor
	VXmlIniReader reader(m_pRootDirSP.Get());
	
	// get xml service
	xml::IVXMLService* pXmlServ = QueryObject<xml::IVXMLService>("xml.service");

	// let it parse the ini file
	pXmlServ->Visit(reader, "vfs.xml");
}

/**
 * d'tor
 */
VSimpleVfs::~VSimpleVfs()
{
}

IVFileSystem::FileStreamPtr VSimpleVfs::OpenFile(
	VStringParam in_strPathAndName,
	VAccessModeFlags in_Access)
{
	IVDirectory* pDir;
	
	// get dir
	pDir = GetDir(in_strPathAndName);

	// get file
	std::string strPathAndName = in_strPathAndName;
	std::string strFileName;
	strFileName.assign(
		std::find(strPathAndName.rbegin(), strPathAndName.rend(), '/').base(),
		strPathAndName.end() );

	// open it
	VDirectory::FileIter fileIter = pDir->Files();
	while(fileIter.HasNext())
	{
		if( strFileName == fileIter->GetName().AsCString() )
			break;
		else
			++fileIter;
	}

	if( !fileIter.HasNext() )
	{
		std::string errorMsg = "file \"";
		errorMsg += strFileName;
		errorMsg += "\" does not exist";

		V3D_THROW(VIOException, errorMsg.c_str());
	}

	IVFile::FileStreamPtr pFileStream = fileIter->Open(in_Access);

	return pFileStream;
}

IVDirectory* VSimpleVfs::GetDir(VStringParam in_strDir)
{
	if( in_strDir[0] != '/' )
	{
		V3D_THROW(VIOException, "paths must start with '/', \""
			+ VString(in_strDir) + "\" is illegal"
			);
	}

	IVDirectory* pCurrDir = m_pRootDirSP.Get();

	std::string pathAndName = in_strDir;
	std::string::iterator pos = pathAndName.begin();
	std::string::iterator substrEnd = pos;
	const std::string::iterator end(pathAndName.end());
	std::string currDirName = "/";
	std::string fileName;

	while((substrEnd = std::find(++pos, end, '/')) != end)
	{		
		// get current dir name
		currDirName.assign(pos, substrEnd);

		// find it in current directory
		VDirectory::DirIter nextDir = pCurrDir->SubDirs();
		VDirectory* tmp = (VDirectory*)&(*nextDir);
		VCompareFSOName fsoCmp(currDirName);
		while( nextDir.HasNext() )
		{
			if( fsoCmp(*nextDir) ) break;
			++nextDir;
		}

		if( !nextDir.HasNext() )
		{
			V3D_THROW(VIOException, "could not find directory \"" 
				+ VString(currDirName.c_str()) + "\"");
		}

		pCurrDir = &(*nextDir);

		pos = substrEnd;
	}

	fileName.assign(pos, substrEnd);

	// return dir
	return pCurrDir;
}

typedef utils::VSimpleTokenizer::Iterator TokenIter;

namespace {
	const IVDirectory* GetSubDir(const IVDirectory* in_pDir, const std::string& in_strName)
	{
		IVDirectory::ConstDirIter dirIter = in_pDir->SubDirs();

		while(dirIter.HasNext())
		{
			if( std::string(dirIter->GetName().AsCString()) == in_strName )
				return &*dirIter;

			++dirIter;
		}

		return 0;
	}

	const IVDirectory* GetDirectory(
		const IVDirectory* in_pParent, 
		TokenIter in_RemainingPath, 
		const TokenIter in_PathEnd)
	{
		V3D_ASSERT(in_pParent != 0);

		if( in_PathEnd == in_RemainingPath )
			return in_pParent;

		std::string nextName = *in_RemainingPath;

		const IVDirectory* pNext = GetSubDir(in_pParent, nextName);

		if( pNext != 0 )
		{
			++in_RemainingPath;
			return GetDirectory(pNext, in_RemainingPath, in_PathEnd);
		}
		else
		{
			return 0;
		}
	}

	const IVFile* GetFile(const IVDirectory* in_pParent, const std::string& in_strName)
	{
		IVDirectory::ConstFileIter fileIter = in_pParent->Files();

		while(fileIter.HasNext())
		{
			if( std::string(fileIter->GetName().AsCString()) == in_strName )
			{
				return &*fileIter;
			}

			++fileIter;
		}

		return 0;
	}
} // anonymous namespace

vbool VSimpleVfs::ExistsDir(VStringParam in_strDir)
{
	V3D_ASSERT(in_strDir[0] != '\0');

	utils::VSimpleTokenizer tokens(in_strDir+1, '/');
	
	const IVDirectory* pDir = GetDirectory(
		m_pRootDirSP.Get(), 
		tokens.TokenBegin(), 
		tokens.TokenEnd());

	return pDir != 0;
}

vbool VSimpleVfs::ExistsFile(VStringParam in_strFile)
{
	V3D_ASSERT(in_strFile[0] != '\0');

	utils::VSimpleTokenizer tokens(in_strFile+1, '/');

	TokenIter lastDir = tokens.TokenEnd();
	--lastDir;

	const IVDirectory* pDir = GetDirectory(
		m_pRootDirSP.Get(), 
		tokens.TokenBegin(), 
		lastDir);

	if( pDir == 0 )
		return false;

	const IVFile* pFile = GetFile(pDir, *lastDir);

	return pFile != 0;
}

vbool VSimpleVfs::Exists(VStringParam in_strFSObject)
{
	return 
		ExistsDir(in_strFSObject) || 
		ExistsFile(in_strFSObject);
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------

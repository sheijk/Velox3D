/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VTempDataProvider.h"
#include <windows.h>
#include <sstream>
#include <fstream>
#include <V3d/Core/MemManager.h>
#undef CreateFile
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------


VTempDataProvider::VTempDataProvider() :
IVTempDataProvider("tempfile.service", 0)
{
	m_nFileCount = -1;

	// make costumization here...
	m_sTempFileFolder = "~temp\\";
	m_sTempFileExtension = ".tmp";
	m_sTempFileName = "tempfile";

	GetWorkDir();

	std::string sDir;
	sDir = m_sWorkingDir;
	sDir += m_sTempFileFolder;

	CreateDirectory(sDir.c_str(),0);

}
//-----------------------------------------------------------------------------

void VTempDataProvider::GetWorkDir()
{
	vchar* pWorkDir = new vchar[SizeWorkDir];
	GetModuleFileName(0, pWorkDir, SizeWorkDir);

	std::string sDir = pWorkDir;
	std::size_t nPos = sDir.rfind('\\');
	m_sWorkingDir = sDir.substr(0, nPos+1);

	delete pWorkDir;
}
//-----------------------------------------------------------------------------

VTempDataProvider::~VTempDataProvider()
{
	DeleteFiles();
}
//-----------------------------------------------------------------------------

VStringParam VTempDataProvider::GetFileName()
{
	std::ostringstream inputStream;
	
	m_nFileCount++;
	inputStream << m_nFileCount;
	
	m_sFilename = m_sWorkingDir;
	m_sFilename += m_sTempFileFolder;
	m_sFilename += m_sTempFileName;
	m_sFilename += inputStream.str();
	m_sFilename += m_sTempFileExtension;

	return m_sFilename.c_str();
}

//-----------------------------------------------------------------------------

VStringParam VTempDataProvider::CreateFile()
{
	return GetFileName();
}
//-----------------------------------------------------------------------------

VStringParam VTempDataProvider::CreateFile(IVStream* in_pStream)
{
	vulong theByteCount = 0;
	vulong theCurrentPosition = in_pStream->GetPos();

	in_pStream->SetPos(vfs::IVStream::End,0);
	theByteCount = in_pStream->GetPos();

	in_pStream->SetPos(vfs::IVStream::Begin, theCurrentPosition);

	vuchar* theDataBuffer = new vuchar[theByteCount]; //TODO error checking
	in_pStream->Read(theDataBuffer, theByteCount);

	VStringParam theFile = CreateFile(theDataBuffer, theByteCount);
	delete [] theDataBuffer;

	m_sFilelist.push_back(theFile);
    return theFile;
}
//-----------------------------------------------------------------------------

VStringParam VTempDataProvider::CreateFile(void* in_pBuffer, vuint in_nBytes)
{
	std::ofstream theFile;
	
	VStringParam theName = GetFileName();
	
	//TODO: some error handling...
	theFile.open( theName , std::ios::out | std::ios::binary);
	if(theFile.is_open())
		theFile.write((vchar*)in_pBuffer, in_nBytes);
	theFile.close();

	return theName;
}
//-----------------------------------------------------------------------------

void VTempDataProvider::DeleteFiles()
{
	typedef std::list<std::string>::iterator FilelistIter;

	for (FilelistIter i = m_sFilelist.begin(); i != m_sFilelist.end(); i++)
	{
		DeleteFile(i->c_str());
	}

	std::string sRemoveDir = m_sWorkingDir;
	sRemoveDir += m_sTempFileFolder;

	RemoveDirectory(sRemoveDir.c_str());


}
//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------


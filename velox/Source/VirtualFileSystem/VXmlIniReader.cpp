#include "VXmlIniReader.h"
//-----------------------------------------------------------------------------
#include <v3d/VFS/IVDirectory.h>
#include <v3d/XML/IVXMLElement.h>
#include <v3d/VFS/VIOException.h>
#include <v3d/VFS/IVDataProviderPool.h>
#include <v3d/Core/VObjectRegistry.h>

#include "VAccessRights.h"
#include "VDirectory.h"
#include "VFile.h"

#include <string>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------
using namespace xml;
using namespace std;

/**
 * standard c'tor
 */
VXmlIniReader::VXmlIniReader(VDirectory* in_pDestDir)
	: m_pDestDir(in_pDestDir), m_State(Initial)
{
	m_DirStack.push(m_pDestDir);
}

/**
 * d'tor
 */
VXmlIniReader::~VXmlIniReader()
{
}

void strToLower(std::string& str)
{
	for(string::iterator it = str.begin(); it != str.end(); ++it)
	{
		*it = tolower(*it);
	}
}

IVDataProvider& GetDataProvider(const string& type)
{
	return QueryObject<IVDataProviderPool>("vfs.dpp")->GetDataProvider(type.c_str());
}

VMountOptions::AccessRightsPtr CreateAccessRights(const string& flagStr)
{
	VAccessRightsFlags flags;

	for(string::const_iterator it = flagStr.begin(); it != flagStr.end(); ++it)
	{
		switch(*it)
		{
		case 'r': flags.allowRead = true; break;
		case 'w': flags.allowWrite = true; break;
		case 'x': flags.allowDelete = true; break;
		case 'f': flags.allowCreateFile = true; break;
		case 'd': flags.allowCreateDir = true; break;
		}
	}

	return VMountOptions::AccessRightsPtr(
		new VAccessRights(flags));
}

void VXmlIniReader::OnElementClose(IVXMLElement* pElement)
{
	string elementName = pElement->GetName().AsCString();

	switch(m_State) {
	case ParseFileSystem:
		{
			if( elementName == "directory" )
			{
				// remove top element of dir stack
				m_DirStack.pop();
			}
		} break;
	}
}

void VXmlIniReader::OnElementOpen(IVXMLElement* pElement)
{
	string elementName = pElement->GetName().AsCString();

	strToLower(elementName);

	switch(m_State)
	{
	case Initial:
		{
			if( elementName == "vfs" )
				m_State = Options;
			else
			{
				string errorMsg = "xml ini file invalid expected \"vfs\", got \"";
				errorMsg += elementName;
				errorMsg += "\"";

				V3D_THROW(VIOException, errorMsg.c_str());
			}
		} break;
	case Options:
		{
			if( elementName == "filesystem" )
				m_State = ParseFileSystem;
			else
				V3D_THROW(VIOException, 
					"xml ini file invalid, expected \"filesystem\"");
		} break;
	case ParseFileSystem:
		{
			if( elementName == "mount" )
			{
				string name, type, source, access;

				try
				{
					// get attributes
					name = pElement->GetAttribute("name")->GetValue().GetSafe<string>();
					type = pElement->GetAttribute("type")->GetValue().GetSafe<string>();
					source = pElement->GetAttribute("source")->GetValue().GetSafe<string>();
					access = pElement->GetAttribute("rights")->GetValue().GetSafe<string>();

					IVDataProvider& dataProv = GetDataProvider(type);

					// if it is a directory
					if( dataProv.IsDirectory(source.c_str()) )
					{
						VMountOptions mountOptions;
						mountOptions.SetName(name.c_str());
						mountOptions.SetSource(source.c_str());
						mountOptions.SetType(type.c_str());
						mountOptions.SetAccessRights(CreateAccessRights(access));

						// mount it and add to root dir
						VDirectory::DirPtr pDir = 
							dataProv.CreateMountedDir(mountOptions);
						m_DirStack.top()->AddSubdir(pDir);
					}
					// if it is a file
					else if( dataProv.IsFile(source.c_str()) )
					{
						// add it to root dir
						VFile::CreationInfo fileInfo;
						fileInfo.name = name;
						fileInfo.source = source;
						fileInfo.type = type;
						fileInfo.pAccRights = CreateAccessRights(access);

						VDirectory::FilePtr pFile(new VFile(fileInfo));

						m_DirStack.top()->AddFile(pFile);
					}

				}
				catch(VXMLException&)
				{
					V3D_THROW(VIOException, "did not find element");
				}
			}
			else if( elementName == "directory" )
			{
				string access, name;

				name = pElement->GetAttribute("name")->GetValue().GetSafe<string>();
				access = "rw";

				// create new dir
				VDirectory* pDir = new VDirectory(
					name, "", "", CreateAccessRights(access));

				// add it to last dir
				m_DirStack.top()->AddSubdir(VDirectory::DirPtr(pDir));

				// add dir to dir stack
				m_DirStack.push(pDir);
			}
			else
				V3D_THROW(VIOException, "xml init file error. "
					"expected \"mount\"");
		} break;
	}
}

void VXmlIniReader::OnFileEnd()
{
}

void VXmlIniReader::OnComment(VStringParam pText)
{
}

void VXmlIniReader::OnText(VStringParam pText)
{
}



//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------

#include "VConfigProvider.h"
//-----------------------------------------------------------------------------
#include <v3d/VFS/IVFileSystem.h>
#include <v3d/XML/IVXMLService.h>
#include <v3d/Core/VObjectRegistry.h>

#include <string>

#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace config {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VConfigProvider::VConfigProvider(VStringParam in_strName)
	: IVConfigProvider(in_strName, 0)
{
}

/**
 * d'tor
 */
VConfigProvider::~VConfigProvider()
{
}

std::string GetConfigFileName(VStringParam in_strCfgId)
{
	std::string ret("/cfg/");
	ret = ret + in_strCfgId;
	return ret;
}

void VConfigProvider::ParseConfigFile(
	VStringParam in_strCfgFileId, v3d::xml::IVXMLVisitor& io_Visitor)
{
	// query xml service
	xml::IVXMLService& xmlService = 
		*QueryObject<xml::IVXMLService>("xml.service");

	// parse file
	xmlService.ParseVfsXMLFile(
		GetConfigFileName(in_strCfgFileId).c_str(), 
		&io_Visitor);
}

VConfigProvider::IVXMLWriterPtr VConfigProvider::CreateConfigFileWriter(
	VStringParam in_strCfgFileId)
{
	// query xml service
	xml::IVXMLService& xmlService = 
		*QueryObject<xml::IVXMLService>("xml.service");
	
	// return writer
	return xmlService.CreateXMLWriter(
		GetConfigFileName(in_strCfgFileId).c_str());
}

//-----------------------------------------------------------------------------
} // namespace config
} // namespace v3d
//-----------------------------------------------------------------------------

/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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
	xmlService.Visit(io_Visitor,
		GetConfigFileName(in_strCfgFileId).c_str());
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


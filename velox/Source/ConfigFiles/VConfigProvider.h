/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VConfigProvider_H
#define V3D_VConfigProvider_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Config/IVConfigProvider.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace config {
//-----------------------------------------------------------------------------

/**
 * Simple config provider
 * id -> /cfg/id in the virtual file system
 */
class VConfigProvider : public IVConfigProvider
{
public:
	VConfigProvider(VStringParam in_strName																								);
	virtual ~VConfigProvider();

	virtual void ParseConfigFile(
		VStringParam in_strCfgFileId, 
		v3d::xml::IVXMLVisitor& io_Visitor);

	virtual IVXMLWriterPtr CreateConfigFileWriter(
		VStringParam in_strCfgFileId);
};

//-----------------------------------------------------------------------------
} // namespace config
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VConfigProvider_H


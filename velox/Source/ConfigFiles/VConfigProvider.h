#ifndef V3D_VConfigProvider_H
#define V3D_VConfigProvider_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Config/IVConfigProvider.h>
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

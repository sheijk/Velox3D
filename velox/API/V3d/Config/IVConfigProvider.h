#ifndef V3D_IVConfigProvider_H
#define V3D_IVConfigProvider_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VNamedObject.h>

#include <v3d/XML/IVXMLVisitor.h>
#include <v3d/XML/IVXMLWriter.h>

#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VServicePtr.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace config {
//-----------------------------------------------------------------------------

/**
 * Load and save xml config files
 * Config files are identified by string ids. The same id always addresses
 * the same config file. The exact mapping to files/etc is defined by
 * the implementation
 *
 * @author sheijk
 */
class IVConfigProvider : public VNamedObject
{
public:
	IVConfigProvider(VStringParam in_strName, VNamedObject* in_pParent)
		: VNamedObject(in_strName, in_pParent)
	{
	}

	/**
	 * Let a config file be parsed by the provided visitor
	 *
	 * @param in_strCfgFileId id/name of the config file
	 * (meaning based on agreement)
	 * @param io_Visitor the visitor to be used
	 */
	virtual void ParseConfigFile(
		VStringParam in_strCfgFileId,
		v3d::xml::IVXMLVisitor& io_Visitor) = 0;

	typedef VPointer<xml::IVXMLWriter>::SharedPtr IVXMLWriterPtr;

	/**
	 * Creates a xml file writer which can be used to write the
	 * config file. (Note: previous content has to be stored and written
	 * to the file again by the user)
	 *
	 * @param in_strCfgFileId the file id
	 */
	virtual IVXMLWriterPtr CreateConfigFileWriter(
		VStringParam in_strCfgFileId) = 0;
};

//-----------------------------------------------------------------------------
} // namespace config
} // namespace v3d
//-----------------------------------------------------------------------------
template<>
inline v3d::config::IVConfigProvider* v3d::QueryService<v3d::config::IVConfigProvider>()
{
	return QueryObject<v3d::config::IVConfigProvider>("config.provider");
}
//-----------------------------------------------------------------------------
#endif // V3D_IVConfigProvider_H

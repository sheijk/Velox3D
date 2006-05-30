#ifndef V3D_VMODELLOADER_2005_02_13_H
#define V3D_VMODELLOADER_2005_02_13_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Resource.h>
#include <V3d/Graphics.h>
#include <V3dLib/Graphics.h>

#include <V3d/Core/SmartPtr/VAutoPtr.h>

#include <string>
#include <map>
//-----------------------------------------------------------------------------
namespace v3d { 

namespace xml {
	class IVXMLElement;
}

namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

V3D_DECLARE_EXCEPTION(VModelLoadingException, VException);

/**
 * Loads a mesh from an xml file
 *
 * @author sheijk
 */
class VModelLoader
{
public:
	VModelLoader();
	virtual ~VModelLoader();

	void LoadMesh(
		VStringParam in_strFileName, 
		resource::VResourceId in_pResource);

private:
	void CheckRootNode(xml::IVXMLElement* in_pRootNode);
	graphics::VModelMesh CreateMeshNode(
		xml::IVXMLElement* in_pMeshNode, 
		resource::VResourceId in_pResource);

	std::string m_strCurrentFile;

	VMeshDescription::GeometryType GetGeometryType(const std::string& in_strName);
	std::map<std::string, VMeshDescription::GeometryType> m_PrimitiveNames;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VMODELLOADER_2005_02_13_H

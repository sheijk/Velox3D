#ifndef V3D_VMESHPART_2005_09_22_H
#define V3D_VMESHPART_2005_09_22_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/VMeshPartBase.h>

namespace v3d { namespace graphics {
	class IVMesh;
	class IVMaterial;
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VMeshPart : public VMeshPartBase
{
public:
	VMeshPart(
		resource::VResourceDataPtr<const graphics::IVMesh> in_hMesh,
		resource::VResourceDataPtr<const graphics::IVMaterial> in_hMaterial
		);

	VMeshPart(
		const std::string& in_strMeshResource,
		const std::string& in_strMaterialResource
		);

	virtual void SendGeometry(graphics::IVDevice& in_Device) const;

private:
	resource::VResourceDataPtr<const graphics::IVMesh> m_hMesh;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VMESHPART_2005_09_22_H

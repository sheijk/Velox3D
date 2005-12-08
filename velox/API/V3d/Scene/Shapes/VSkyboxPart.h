#ifndef V3D_VSKYBOXPART_2005_12_01_H
#define V3D_VSKYBOXPART_2005_12_01_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VPartBase.h>
#include <V3d/Scene/IVShapePart.h>
#include <V3dLib/EntityParts/VRigidBodyPart.h>
#include <V3d/Resource.h>
#include <V3d/Graphics/IVMaterial.h>
#include <V3d/Scene/IVSceneManagerPart.h>

#include <vector>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
	class IVDevice;
	class IVMaterial;
}}

namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VSkyboxPart : public entity::VPartBaseAdapter<IVGraphicsPart>
{
public:
	VSkyboxPart();
	virtual ~VSkyboxPart();

	/** 
	 * Use in_strDirectory/*.extension as textures
	 * * = left/right/front/back/top/bottom
	 */
	void SetTextureDir(
		const std::string& in_strDirectory, 
		const std::string& in_strExtension);

	// inherited
	virtual void UpdateAndCull(const graphics::IVCamera& in_Camera);
	virtual VRangeIterator<const IVShapePart> GetVisibleMeshes() const;

	virtual void Activate();
	virtual void Deactivate();

private:
	class VSide : public entity::VPartBaseAdapter<IVShapePart>
	{
	public:
		VSide(VSkyboxPart* in_pContainer, 
			math::VVector3f in_Pos,
			math::VVector3f in_Right, 
			math::VVector3f in_Up);

		void SetMaterial(
			resource::VResourceDataPtr<const graphics::IVMaterial> in_hMaterial);

		virtual void Activate();
		virtual void Deactivate();

		virtual void SendGeometry(graphics::IVDevice& in_Device) const;
		virtual const graphics::IVMaterial& GetMaterial() const;
		virtual const math::VRBTransform& GetModelTransform() const;
		virtual void UpdateAndCull(const graphics::IVCamera& in_Camera);
		virtual VRangeIterator<const IVShapePart> GetVisibleMeshes() const;

		virtual const VTypeInfo& GetTypeInfo() const { return IVShapePart::GetTypeInfo(); }

	private:
		resource::VResourceDataPtr<const graphics::IVMaterial> m_hMaterial;
		VSkyboxPart* m_pContainer;

		math::VVector3f m_Position;
		math::VVector3f m_Right;
		math::VVector3f m_Up;
	};

	const math::VRBTransform& GetModelTransform() const;

	std::vector<VSide> m_Sides;
	entity::VPartConnection<entity::VRigidBodyPart> m_pRigidBodyPart;
	entity::VPartConnection<scene::IVSceneManagerPart> m_pSceneManager;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VSkyboxPart, v3d::scene::IVGraphicsPart);
//-----------------------------------------------------------------------------
#endif // V3D_VSKYBOXPART_2005_12_01_H

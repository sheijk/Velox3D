#ifndef V3D_VMODELPART_2005_05_22_H
#define V3D_VMODELPART_2005_05_22_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Scene/IVSceneManagerPart.h>
#include <V3d/Scene/IVGraphicsPart.h>

#include <V3d/Entity/VPartBase.h>
#include <V3d/Entity/VUnconnectedPart.h>
#include <V3d/Graphics/VModel.h>
#include <v3dLib/EntityParts/VRigidBodyPart.h>

#include <V3d/Graphics/IVDevice.h>

#include <string>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VModelPart : public entity::VPartBaseAdapter<IVGraphicsPart>
{
public:
	VModelPart(const graphics::VModel& in_Model);
	VModelPart();

	void AddMesh(
		VStringParam in_strMeshResource, 
		VStringParam in_strMaterialResource);
	
	void Add(const graphics::VModelMesh in_ModelMesh);
	void Add(const graphics::VModel& in_Model);

	void RemoveAllMeshes();

	virtual void UpdateAndCull(const graphics::IVCamera& in_Camera);
	virtual VRangeIterator<const IVShapePart> GetVisibleMeshes() const;

    // derived from IVPart:
	virtual void Activate();
	virtual void Deactivate();

	virtual void Send(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer = 0);

	static std::string GetDefaultId();

private:
	struct MeshPart : public entity::VUnconnectedPartAdapter<IVShapePart>
	{
		virtual void SendGeometry(graphics::IVDevice& in_Device) const
		{
			in_Device.RenderMesh(&*m_hMesh);
		}
	
		virtual const math::VRBTransform& GetModelTransform() const
		{
			return m_pModelPart->m_ModelTransform;
		}
	
		virtual const graphics::IVMaterial& GetMaterial() const
		{
			return *m_hMaterial;
		}
		
		virtual void UpdateAndCull(const graphics::IVCamera& in_Camera)
		{
		}

		virtual VRangeIterator<const IVShapePart> GetVisibleMeshes() const
		{
			return CreateSingleValueIterator<const IVShapePart>(this);
		}

		virtual void Activate() {}
		virtual void Deactivate() {}

        VModelPart* m_pModelPart;
		resource::VResourceDataPtr<const graphics::IVMesh> m_hMesh;
		resource::VResourceDataPtr<const graphics::IVMaterial> m_hMaterial;
	};

	math::VRBTransform m_ModelTransform;

	typedef std::list<VSharedPtr<MeshPart> > MeshList;
	MeshList m_Meshes;

	entity::VPartConnection<IVSceneManagerPart> m_pParent;
	entity::VPartConnection<entity::VRigidBodyPart> m_RigidBodyPart;

	std::string m_strMeshRes;
	std::string m_strMatRes;
	
	std::string m_strModel;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VMODELPART_2005_05_22_H

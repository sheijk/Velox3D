/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VMODELPART_2005_05_22_H
#define V3D_VMODELPART_2005_05_22_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Scene/IVSceneManagerPart.h>
#include <V3d/Scene/IVGraphicsPart.h>
#include <V3d/Entity/IVPart.h>
#include <V3d/Entity/VUnconnectedPart.h>
#include <V3d/Graphics/VModel.h>
#include <V3d/Entity/VRigidBodyPart.h>
#include <V3d/Graphics/IVDevice.h>

#include <string>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VModelPart : public IVGraphicsPart
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

	const math::VRBTransform& GetModelTransform() const;
	void SetModelTransform(const math::VRBTransform& in_Transform);

	static std::string GetDefaultId();
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	virtual void OnActivate();
	virtual void OnDeactivate();

	void ChangeMaterialForAllMeshes(const std::string& in_strResourceName);
	virtual void OnMessage(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer = 0);

	struct MeshPart : public entity::VUnconnectedPartAdapter<IVShapePart>
	{
		virtual void SendGeometry(graphics::IVDevice& in_Device) const;
		virtual const math::VRBTransform& GetModelTransform() const;
		virtual const graphics::IVMaterial& GetMaterial() const;
		virtual vuint GetPassCount() const;
		virtual void ApplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const;
		virtual void UnapplyPassStates(vuint in_nPassNum, graphics::IVDevice& in_Device) const;
		virtual void UpdateAndCull(const graphics::IVCamera& in_Camera);
		virtual VRangeIterator<const IVShapePart> GetVisibleMeshes() const;

        VModelPart* m_pModelPart;
		resource::VResourceDataPtr<const graphics::IVMesh> m_hMesh;
		resource::VResourceDataPtr<const graphics::IVMaterial> m_hMaterial;
	};

	typedef std::list<VSharedPtr<MeshPart> > MeshList;
	MeshList m_Meshes;

	entity::VNodeConnection<IVSceneManagerPart> m_pParent;
	entity::VNodeConnection<entity::VRigidBodyPart> m_RigidBodyPart;

	std::string m_strMeshRes;
	std::string m_strMatRes;
	
	std::string m_strModel;

	vbool m_bIsActive;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VModelPart, v3d::scene::IVGraphicsPart);
//-----------------------------------------------------------------------------
#endif // V3D_VMODELPART_2005_05_22_H


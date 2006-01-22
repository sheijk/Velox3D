#ifndef V3D_VMESHPARTBASE_2005_09_22_H
#define V3D_VMESHPARTBASE_2005_09_22_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVShapePart.h>
#include <V3d/Scene/IVSceneManagerPart.h>

#include <V3d/Graphics/Parameters/IVParameterValue.h>
#include <V3d/Entity/VPartBase.h>

#include <V3d/Resource/VResourceDataPtr.h>
#include <V3dLib/EntityParts/VRigidBodyPart.h>

#include <map>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Base class for parts which display a single mesh. Only the SendGeometry
 * function will need to be overridden
 *
 * @author sheijk
 */
class VMeshPartBase : public entity::VPartBaseAdapter<IVShapePart>
{
public:
	VMeshPartBase(resource::VResourceDataPtr<const graphics::IVMaterial> in_hMaterial);
	VMeshPartBase(const std::string& in_strMaterialResource);

	virtual ~VMeshPartBase();

	virtual void SendGeometry(graphics::IVDevice& in_Device) const = 0;

	virtual const graphics::IVMaterial& GetMaterial() const;
	virtual void SetMaterial(
		resource::VResourceDataPtr<const graphics::IVMaterial> in_hMaterial);
	virtual const math::VRBTransform& GetModelTransform() const;
	virtual void SetModelTransform(const math::VRBTransform& in_Transform);

	void AddParamValue(const std::string& in_strParamName, 
		VSharedPtr<graphics::IVParameterValue> in_pValue);
	void RemoveParamValue(const std::string& in_strParamName);

	virtual void UpdateAndCull(const graphics::IVCamera& in_Camera) {}
	virtual VRangeIterator<const IVShapePart> GetVisibleMeshes() const;

	virtual void Activate();
	virtual void Deactivate();

protected:
	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

	entity::VPartConnection<IVSceneManagerPart> m_pSceneManager;
	entity::VPartConnection<entity::VRigidBodyPart> m_pRigidBody;

	void ApplyParameterValues() const;

	typedef std::map<std::string, VSharedPtr<graphics::IVParameterValue> > ParamValueMap;
	ParamValueMap m_ParameterValues;

	resource::VResourceDataPtr<graphics::IVMaterial> m_hMaterial;
	//math::VRBTransform m_Transform;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VMESHPARTBASE_2005_09_22_H

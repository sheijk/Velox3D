#ifndef V3D_VMIRRORSHOOTING_2005_12_10_H
#define V3D_VMIRRORSHOOTING_2005_12_10_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/Shootings/VShootingBase.h>
#include <V3d/Scene/VSimpleShooting.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3dLib/Graphics/Misc/VCamera.h>
#include <V3d/Resource/VResourceDataPtr.h>
#include <V3d/Math/VPlane.h>
#include <V3d/Graphics/Parameters/VGenericValue.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VMirrorShooting : public VShootingBase
{
public:
	VMirrorShooting();
	virtual ~VMirrorShooting();

	void SetRenderTargetResource(const std::string& in_strResourceName);
	std::string GetRenderTargetResource() const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

	math::VPlane GetPlane() const;
	void SetPlane(const math::VPlane& in_Plane);

	VSharedPtr<graphics::VFloat44ParamValue> GetTextureMatrixValue() const;

	// overridden
	virtual void Activate();
	virtual void Render();

	virtual void Deactivate();
	virtual void UpdateAndCull();

private:
	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer);

	virtual graphics::IVDevice* GetRenderTarget();
	virtual graphics::IVCamera* GetCamera();
	virtual scene::IVGraphicsPart* GetScene();

	entity::VPartConnection<VSimpleShooting> m_pMainShooting;

	resource::VResourceDataPtr<graphics::IVDevice> m_pRenderTarget;
	VSharedPtr<graphics::VFloat44ParamValue> m_pTextureMatrixValue;
	graphics::VCamera m_Camera;
	math::VPlane m_Plane;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VMirrorShooting, v3d::scene::VShootingBase);
//-----------------------------------------------------------------------------
#endif // V3D_VMIRRORSHOOTING_2005_12_10_H

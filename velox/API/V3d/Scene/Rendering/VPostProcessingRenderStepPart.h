#ifndef V3D_VPOSTPROCESSINGRENDERSTEPPART_2005_11_06_H
#define V3D_VPOSTPROCESSINGRENDERSTEPPART_2005_11_06_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>

#include <V3d/Graphics/Parameters/VMaterialSetup.h>

#include <V3d/Scene/IVRenderStepPart.h>
#include <V3d/Scene/IVGraphicsPart.h>

#include <V3d/Resource/VResourceDataPtr.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
	class IVDevice;
	class IVMaterial;
	class IVTexture;
}} // namespace v3d::graphics

namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VPostProcesssingRenderStepPart : public IVRenderStepPart
{
public:
	VPostProcesssingRenderStepPart();

	virtual void Render(IVGraphicsPart* in_pScene);

	graphics::IVDevice* GetPredecessorDevice() const;
	void SetOutputDevice(graphics::IVDevice* in_OutputDevice);

	void SetPostProcessingShader(
		resource::VResourceDataPtr<graphics::IVMaterial> in_hShader);

	virtual const VTypeInfo& GetTypeInfo() const;

	void AddMaterialParameter(VStringParam in_strParamName, 
		VSharedPtr<graphics::IVParameterValue> in_Value);

private:
	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

	resource::VResourceDataPtr<graphics::IVDevice> m_hOffscreenDevice;
	resource::VResourceDataPtr<graphics::IVMaterial> m_hPostProcessingShader;
	resource::VResourceDataPtr<graphics::IVTexture> m_hOffscreenTexture;

	graphics::VMaterialSetup m_MaterialSetup;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VPostProcesssingRenderStepPart, v3d::scene::IVRenderStepPart);
//-----------------------------------------------------------------------------
#endif // V3D_VPOSTPROCESSINGRENDERSTEPPART_2005_11_06_H

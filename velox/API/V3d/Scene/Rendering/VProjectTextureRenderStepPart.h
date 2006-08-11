#ifndef V3D_VPROJECTTEXTURERENDERSTEPPART_2005_10_19_H
#define V3D_VPROJECTTEXTURERENDERSTEPPART_2005_10_19_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Math/VMatrix.h>
#include <V3d/Math/VVector.h>
#include <V3d/Math/VRBTransform.h>

#include <V3d/Resource/VResourceDataPtr.h>

#include <V3d/Graphics/IVTexture.h>

#include <V3d/Scene/IVRenderStepPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VProjectTextureRenderStepPart : public IVRenderStepPart
{
public:
	VProjectTextureRenderStepPart();
	virtual ~VProjectTextureRenderStepPart();

	virtual void Render(IVGraphicsPart* in_pScene);

	math::VRBTransform GetProjectorOrientation() const;
	void SetProjectorOrientation(const math::VRBTransform& in_ProjectorOrientation);

	resource::VResourceDataPtr<const graphics::IVTexture> GetTexture() const;
	void SetTexture(const resource::VResourceDataPtr<const graphics::IVTexture>& in_Texture);

	vfloat32 GetTextureSize() const;
	void SetTextureSize(const vfloat32& in_TextureSize);

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	math::VMatrix44f CalculateTextureMatrix();

private:
	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

	math::VRBTransform m_ProjectorOrientation;
	resource::VResourceDataPtr<const graphics::IVTexture> m_pTexture;
	vfloat32 m_fTextureSize;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VProjectTextureRenderStepPart, v3d::scene::IVRenderStepPart);
//-----------------------------------------------------------------------------
#endif // V3D_VPROJECTTEXTURERENDERSTEPPART_2005_10_19_H

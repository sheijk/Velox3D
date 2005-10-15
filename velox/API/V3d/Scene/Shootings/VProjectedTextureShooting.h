#ifndef V3D_VPROJECTEDTEXTURESHOOTING_2005_10_15_H
#define V3D_VPROJECTEDTEXTURESHOOTING_2005_10_15_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Math/VMatrix.h>
#include <V3d/Math/VVector.h>
#include <V3dLib/Math/VRBTransform.h>

#include <V3d/Resource/VResourceDataPtr.h>

#include <V3d/Graphics/IVTexture.h>

#include <V3d/Scene/VSimpleShooting.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VProjectedTextureShooting : public VSimpleShooting
{
public:
	VProjectedTextureShooting();

	void Render();

	math::VRBTransform GetProjectorOrientation() const;
	void SetProjectorOrientation(const math::VRBTransform& in_ProjectorOrientation);

	resource::VResourceDataPtr<const graphics::IVTexture> GetTexture() const;
	void SetTexture(const resource::VResourceDataPtr<const graphics::IVTexture>& in_Texture);

	vfloat32 GetTextureSize() const;
	void SetTextureSize(const vfloat32& in_TextureSize);

protected:
	VMatrix44f CalculateTextureMatrix();

private:
	math::VRBTransform m_ProjectorOrientation;
	resource::VResourceDataPtr<const graphics::IVTexture> m_pTexture;
	vfloat32 m_fTextureSize;
 
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VPROJECTEDTEXTURESHOOTING_2005_10_15_H

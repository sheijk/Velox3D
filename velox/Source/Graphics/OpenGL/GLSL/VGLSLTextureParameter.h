#ifndef V3D_VGLSLTEXTUREPARAMETER_2005_11_28_H
#define V3D_VGLSLTEXTUREPARAMETER_2005_11_28_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "VGLSLParameter.h"
#include <V3d/Resource/VResourceDataPtr.h>
#include "../Textures/VTexture2D.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VGLSLTextureParameter : public VGLSLParameter
{
public:
	VGLSLTextureParameter(
		GLhandleARB in_hProgram, 
		VStringParam in_strName,
		vuint in_nTextureUnit);

	virtual ~VGLSLTextureParameter();

	virtual void ApplyTexture(VStringParam in_strResourceName) const;
	virtual std::string TextureResource() const;

	void BindTexture();
	void UnbindTexture();

private:
	mutable resource::VResourceDataPtr<IVTexture> m_pTexture;
	vuint m_nTextureUnit;
	mutable vbool m_bWasFineLastTime;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VGLSLTEXTUREPARAMETER_2005_11_28_H

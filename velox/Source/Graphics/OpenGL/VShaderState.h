#ifndef V3D_VSHADERSTATE_2005_11_26_H
#define V3D_VSHADERSTATE_2005_11_26_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "IVOpenGLRenderState.h"

#include "GLSL/VGLSLShader.h"
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VShaderState : public IVOpenGLRenderState
{
public:
	VShaderState(IVShader* in_pShader, IVStateCategory* in_pCategory);
	virtual ~VShaderState();

	virtual void Apply() const;
	virtual const IVStateCategory* GetCategory() const;

	IVShader* GetShader();
private:
	IVShader* m_pShader;
	IVStateCategory* m_pCategory;
	static IVShader* s_pActiveShader;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VSHADERSTATE_2005_11_26_H

#ifndef V3D_VCGFXPASS_2005_08_17_H
#define V3D_VCGFXPASS_2005_08_17_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "../../DeviceBase/VRenderStateList.h"
#include "VCGFXState.h"

#include <V3d/OpenGL.h>
#include <CG/cg.h>
#include <CG/cgGL.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VCGFXMaterial;

/**
 */
class VCGFXPass : public VRenderStateList
{
public:
	VCGFXPass(
		RenderStateList in_DefaultStates, 
		CGpass in_Pass, CGeffect in_Effect, CGtechnique in_Technique,
		VCGFXMaterial* in_pMaterial);
	virtual ~VCGFXPass();

	static vbool CanRealize(const VRenderPass& in_Pass);

	void Bind();
	void Unbind();

private:
	CGpass m_Pass;
	CGeffect m_Effect;
	CGtechnique m_Technique;
	VCGFXMaterial* m_pMaterial;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VCGFXPASS_2005_08_17_H

#ifndef V3D_VGLSLPASS_2005_11_26_H
#define V3D_VGLSLPASS_2005_11_26_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "../../DeviceBase/VRenderStateList.h"
#include <string>
#include "../VShaderCategory.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VGLSLPass : public VRenderStateList
{
public:
	VGLSLPass(RenderStateList in_DefaultStates, const VRenderPass& in_Pass);
	virtual ~VGLSLPass();

	static vbool CanRealize(const VRenderPass& in_Pass);
	
	static void SetCategories(VShaderCategory* in_pShaderCategory);

private:
	static VShaderCategory* s_pShaderCategory;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VGLSLPASS_2005_11_26_H

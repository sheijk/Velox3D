#ifndef V3D_VVERTEXSHADERCATEGORY_2005_03_23_H
#define V3D_VVERTEXSHADERCATEGORY_2005_03_23_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/IVStateCategory.h>
#include "VCGVertexShaderState.h"
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VCGShaderCategory : public IVStateCategory
{
protected:
	IVRenderState* CreateShaderState(
		const VState* in_pState, 
		VCGVertexShaderState::ShaderMode in_DisableMode);
};

/**
 * @author sheijk
 */
class VVertexShaderCategory : public VCGShaderCategory
{
public:
	virtual IVRenderState* CreateState(const VRenderPass& in_Pass);
};

class VPixelShaderCategory : public VCGShaderCategory
{
public:
	virtual IVRenderState* CreateState(const VRenderPass& in_Pass);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VVERTEXSHADERCATEGORY_2005_03_23_H

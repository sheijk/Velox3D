#ifndef V3D_EFFECTUTILS_2004_09_22_H
#define V3D_EFFECTUTILS_2004_09_22_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Graphics/VEffectDescription.h>
#include <V3dLib/Graphics/Geometry/VColor4f.h>
#include <V3dLib/Graphics/Materials/StateTypes.h>
#include <v3d/Graphics/VBuffer.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/** creates a state which sets the materials default color */
VState DefaultColorState(VColor4f in_Color);

/** creates a state for the color buffer write mask */
VState ColorBufferWriteMaskState(VColorBufferMask in_Mask);
VState ColorBufferWriteMaskState(
	vbool writeRed, vbool writeGreen, vbool writeBlue, vbool writeAlpha);

/** creates a state with texture options */
VState TextureState(
	IVBuffer<vbyte>* hBuffer,
	vuint width, vuint height,
	VTextureFilter magnificationFilter, VTextureFilter minificationFilter,
	VTextureWrapMode texCoordWrapU, VTextureWrapMode texCoordWrapV,
	const VMatrix44f* pTextureMatrix = 0
	);

/** creates a state for polygon mode */
VState PolygonModeState(VPolygonMode frontMode, VPolygonMode backMode);

/** creates a state for z-buffer modes */
VState DepthBufferState(
	VDepthTest depthTest, 
	VDepthTestEnable enableDepthTest, 
	VDepthWriteMode writeMode);

/** creates a state for alpha blending */
VState BlendingState(
	VBlendEnable enable,
	VBlendFactor source,
	VBlendFactor dest);

//-----------------------------------------------------------------------------

/**
 * Returns a render pass with the default values for all attributes which will
 * be used if they are not explicitly set
 */
void MakeDefaultMaterial(VRenderPass& pass);

/** Creates a colored wire frame material */
void MakeWireFrameMaterial(VRenderPass& pass);

/**
 * Returns a material which will be used if no shader path could be found which
 * can be rendered on the device
 */
//void MakeErrorMaterial(VRenderPass& pass);


/**
 * Returns a render pass which will render a wireframe
 */

//-----------------------------------------------------------------------------

/** prints an effect description to the velox console */
void PrintEffectDescription(const VEffectDescription& effect);

//-----------------------------------------------------------------------------
}} // namespace v3d::grapics
//-----------------------------------------------------------------------------
#endif // V3D_EFFECTUTILS_2004_09_22_H

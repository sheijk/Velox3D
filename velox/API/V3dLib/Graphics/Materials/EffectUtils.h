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
	VTextureWrapMode texCoordWrapU, VTextureWrapMode texCoordWrapV
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

/** prints an effect description to the velox console */
void PrintEffectDescription(const VEffectDescription& effect);

//-----------------------------------------------------------------------------
}} // namespace v3d::grapics
//-----------------------------------------------------------------------------
#endif // V3D_EFFECTUTILS_2004_09_22_H

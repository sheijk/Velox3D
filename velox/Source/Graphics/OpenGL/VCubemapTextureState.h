#ifndef V3D_VCUBEMAPTEXTURESTATE_2005_02_23_H
#define V3D_VCUBEMAPTEXTURESTATE_2005_02_23_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include "IVOpenGLRenderState.h"

#include <V3d/Resource/VResourceDataPtr.h>
#include "VTextureState.h"

#include <V3d/OpenGL.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
//TODO: insert documentation here
 */
class VCubemapTextureState : public IVOpenGLRenderState
{
public:
	VCubemapTextureState(
		resource::VResourceDataPtr<const VTextureStatePosX> in_nPosXTextureId,
		resource::VResourceDataPtr<const VTextureStatePosY> in_nPosYTextureId,
		resource::VResourceDataPtr<const VTextureStatePosZ> in_nPosZTextureId,
		resource::VResourceDataPtr<const VTextureStateNegX> in_nNegXTextureId,
		resource::VResourceDataPtr<const VTextureStateNegY> in_nNegYTextureId,
		resource::VResourceDataPtr<const VTextureStateNegZ> in_nNegZTextureId
		);

	virtual ~VCubemapTextureState();

	virtual void Apply() const;

private:
	const resource::VResourceDataPtr<const VTextureStatePosX> m_nPosXTextureId;
	const resource::VResourceDataPtr<const VTextureStatePosY> m_nPosYTextureId;
	const resource::VResourceDataPtr<const VTextureStatePosZ> m_nPosZTextureId;
	const resource::VResourceDataPtr<const VTextureStateNegX> m_nNegXTextureId;
	const resource::VResourceDataPtr<const VTextureStateNegY> m_nNegYTextureId;
	const resource::VResourceDataPtr<const VTextureStateNegZ> m_nNegZTextureId;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VCUBEMAPTEXTURESTATE_2005_02_23_H

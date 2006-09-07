/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCUBEMAPTEXTURESTATE_2005_02_23_H
#define V3D_VCUBEMAPTEXTURESTATE_2005_02_23_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include "IVOpenGLRenderState.h"

#include <V3d/Resource/VResourceDataPtr.h>
#include "Textures/VBaseTexture.h"

#include <V3d/OpenGL.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
//TODO: insert documentation here
 */
/*class VCubemapTextureState : public IVOpenGLRenderState
{
public:
	VCubemapTextureState(
		resource::VResourceDataPtr<const VCubemapPosX> in_nPosXTextureId,
		resource::VResourceDataPtr<const VCubemapPosY> in_nPosYTextureId,
		resource::VResourceDataPtr<const VCubemapPosZ> in_nPosZTextureId,
		resource::VResourceDataPtr<const VCubemapNegX> in_nNegXTextureId,
		resource::VResourceDataPtr<const VCubemapNegY> in_nNegYTextureId,
		resource::VResourceDataPtr<const VCubemapNegZ> in_nNegZTextureId
		);

	virtual ~VCubemapTextureState();

	virtual void Apply() const;

private:
	const resource::VResourceDataPtr<const VCubemapPosX> m_nPosXTextureId;
	const resource::VResourceDataPtr<const VCubemapPosY> m_nPosYTextureId;
	const resource::VResourceDataPtr<const VCubemapPosZ> m_nPosZTextureId;
	const resource::VResourceDataPtr<const VCubemapNegX> m_nNegXTextureId;
	const resource::VResourceDataPtr<const VCubemapNegY> m_nNegYTextureId;
	const resource::VResourceDataPtr<const VCubemapNegZ> m_nNegZTextureId;
};*/

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VCUBEMAPTEXTURESTATE_2005_02_23_H


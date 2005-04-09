#include "VCubemapTextureState.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VCubemapTextureState::VCubemapTextureState(
	resource::VResourceDataPtr<const VTextureStatePosX> in_nPosXTextureId,
	resource::VResourceDataPtr<const VTextureStatePosY> in_nPosYTextureId,
	resource::VResourceDataPtr<const VTextureStatePosZ> in_nPosZTextureId,
	resource::VResourceDataPtr<const VTextureStateNegX> in_nNegXTextureId,
	resource::VResourceDataPtr<const VTextureStateNegY> in_nNegYTextureId,
	resource::VResourceDataPtr<const VTextureStateNegZ> in_nNegZTextureId
	) :
	m_nPosXTextureId(in_nPosXTextureId),
	m_nPosYTextureId(in_nPosYTextureId),
	m_nPosZTextureId(in_nPosZTextureId),
	m_nNegXTextureId(in_nNegXTextureId),
	m_nNegYTextureId(in_nNegYTextureId),
	m_nNegZTextureId(in_nNegZTextureId)
{
}

void VCubemapTextureState::Apply() const
{
	// bind textures
	m_nPosXTextureId->Apply();
	m_nNegXTextureId->Apply();
	m_nPosYTextureId->Apply();
	m_nNegYTextureId->Apply();
	m_nPosZTextureId->Apply();
	m_nNegYTextureId->Apply();

	// enable texture coordinate auto generation
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	//glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
	//glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
	//glTexGenf(GL_R, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_CUBE_MAP);

	//glEnable(GL_AUTO_NORMAL);
}

/**
 * d'tor
 */
VCubemapTextureState::~VCubemapTextureState()
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

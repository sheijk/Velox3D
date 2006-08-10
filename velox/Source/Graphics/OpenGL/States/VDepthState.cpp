#include "VDepthState.h"
//-----------------------------------------------------------------------------

#include <V3d/Graphics/VEffectDescription.h>

#include <V3d/Graphics/Materials/VModeTypeInfo.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VDepthState::VDepthState()
{
	m_DepthFunction = GL_LESS;
	m_bDepthWrite = true;
	m_bDepthTestEnabled = true;

	Parse(VRenderPass());
}

VDepthState::~VDepthState()
{
}

void VDepthState::Parse(const VRenderPass& in_Pass)
{
	VState const* depthState = in_Pass.GetStateByName("depth");
	if( depthState != 0 )
	{
		std::string depthTest = "onless";
		vbool depthWrite = true;
		vbool enable = true;

		depthState->GetParameter("function", depthTest);
		depthState->GetParameter("write", depthWrite);
		depthState->GetParameter("enable", enable);

		m_DepthFunction = GetDepthTestInfo().GetGLEnum(depthTest);
		m_bDepthWrite = depthWrite;
		m_bDepthTestEnabled = enable;
	}
}

void VDepthState::Apply() const
{
	if( m_bDepthTestEnabled )
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
	glDepthFunc(m_DepthFunction);
	glDepthMask(m_bDepthWrite);
}

void VDepthState::Unapply() const
{
	//TODO: verify these are the opengl default settings
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(true);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

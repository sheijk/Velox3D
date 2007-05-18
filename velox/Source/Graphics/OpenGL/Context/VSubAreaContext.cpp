/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include "VSubAreaContext.h"
//-----------------------------------------------------------------------------
#include <V3d/OpenGL.h>
#include <V3d/Core/VException.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VSubAreaContext::VSubAreaContext(VSharedPtr<IVRenderContext> in_pParentContext)
{
	m_pParentContext = in_pParentContext;
}

/**
 * d'tor
 */
VSubAreaContext::~VSubAreaContext()
{
}

void VSubAreaContext::SetArea(vint left, vint top, vint right, vint bottom)
{
	m_nLeft = left;
	m_nTop = top;
	m_nRight = right;
	m_nBottom = bottom;
}

void VSubAreaContext::SetReallySwap(vbool yesno)
{
	m_bReallySwap = yesno;
}

vbool VSubAreaContext::GetReallySwap()
{
	return m_bReallySwap;
}

void VSubAreaContext::MakeCurrent()
{
	if( m_pParentContext != 0 )
	{
		m_pParentContext->MakeCurrent();

		//glViewport( m_nLeft, m_nTop, m_nRight - m_nLeft, m_nTop - m_nBottom );
	}
}

void VSubAreaContext::SwapBuffers()
{
	if( m_bReallySwap && m_pParentContext != 0 )
	{
		m_pParentContext->SwapBuffers();
	}
}

VDisplaySettings* VSubAreaContext::GetDisplaySettings()
{
	if( m_pParentContext != 0 )
	{
		return m_pParentContext->GetDisplaySettings();
	}
	else
	{
		V3D_THROW(VException, "Could not return display settings, parent context is null");
	}
}

IVRenderContext* VSubAreaContext::CreateOffscreenContext(const VDisplaySettings* in_pDisplaySettings)
{
	if( m_pParentContext != 0 )
	{
		return m_pParentContext->CreateOffscreenContext(in_pDisplaySettings);
	}
	else
	{
		V3D_THROW(VException, "Could not create offscreen context, parent context is null");
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------


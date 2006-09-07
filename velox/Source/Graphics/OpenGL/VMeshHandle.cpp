/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VMeshHandle.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VMeshHandle::VMeshHandle(VMeshBase* in_hBuffer)
{
	m_pMesh = in_hBuffer;
}

/**
 * d'tor
 */
VMeshHandle::~VMeshHandle()
{
}

VMeshBase* VMeshHandle::GetGLMesh() const
{
	return m_pMesh;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------


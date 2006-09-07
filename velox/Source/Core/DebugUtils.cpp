/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Core/DebugUtils.h>
//-----------------------------------------------------------------------------

#include <GL/glfw.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VThreadId IdOfCurrentThread()
{
	return glfwGetThreadID();
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------


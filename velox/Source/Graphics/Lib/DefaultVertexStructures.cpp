/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Graphics/Geometry.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

v3d::graphics::VVertexDataLayout VTexturedVertex::layout;
v3d::graphics::VVertexDataLayout VColoredVertex::layout;
v3d::graphics::VVertexDataLayout VColoredTextureVertex::layout;
v3d::graphics::VVertexDataLayout VSimpleVertex::layout;

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------


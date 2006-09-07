/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCOLOREDTEXTUREVERTEX_H
#define V3D_VCOLOREDTEXTUREVERTEX_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/Geometry/VVertex3f.h>
#include <V3d/Graphics/Geometry/VTexCoord2f.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
#include <V3d/Graphics/Geometry/VVertexDataLayout.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * A vertex with position, color and texture coordinate
 *
 * @author sheijk
 */
struct VColoredTextureVertex
{
	// still need to be moved..
	typedef v3d::graphics::VVertex3f VVector3f;
	typedef v3d::graphics::VTexCoord2f VTexCoord2f;
	typedef v3d::graphics::VColor4f VColor4f;
	typedef v3d::graphics::VVertexDataLayout VVertexDataLayout;

	VColoredTextureVertex()
	{
		VVertexDataLayout::SetPositionOffset<VColoredTextureVertex>();
		VVertexDataLayout::SetColorOffset<VColoredTextureVertex>();
		VVertexDataLayout::SetTexCoordOffset<VColoredTextureVertex>();
	}

	VVector3f position;
	VColor4f color;
	VTexCoord2f texCoords;

	static VVertexDataLayout layout;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCOLOREDTEXTUREVERTEX_H


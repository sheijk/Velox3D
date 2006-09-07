/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VTEXTUREDVERTEX_H
#define V3D_VTEXTUREDVERTEX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Graphics/Geometry/VVertexDataLayout.h>
#include <V3d/Graphics/Geometry/VVertex3f.h>
#include <V3d/Graphics/Geometry/VTexCoord2f.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A textured with a position and one textur coordinate
 *
 * @author sheijk
 */
struct VTexturedVertex
{
	typedef v3d::graphics::VVertex3f VVector3f;
	typedef v3d::graphics::VTexCoord2f VTexCoord2f;
	typedef v3d::graphics::VVertexDataLayout VVertexDataLayout;

	VVector3f position;
	VTexCoord2f texCoords;

	static VVertexDataLayout layout;

	VTexturedVertex()
	{
		VVertexDataLayout::SetPositionOffset<VTexturedVertex>();
		VVertexDataLayout::SetTexCoordOffset<VTexturedVertex>();
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTUREDVERTEX_H


#ifndef V3D_VCOLOREDTEXTUREVERTEX_H
#define V3D_VCOLOREDTEXTUREVERTEX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Utils/Graphics/VVector3f.h>
#include <v3d/Utils/Graphics/VTexCoord2f.h>
#include <v3d/Utils/Graphics/VColor4f.h>
#include <v3d/Utils/Graphics/VVertexDataLayout.h>

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
	typedef v3d::utils::graphics::VVector3f VVector3f;
	typedef v3d::utils::graphics::VTexCoord2f VTexCoord2f;
	typedef v3d::utils::graphics::VColor4f VColor4f;
	typedef v3d::utils::graphics::VVertexDataLayout VVertexDataLayout;

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

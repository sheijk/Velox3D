#ifndef V3D_VCOLOREDTEXTUREVERTEX_H
#define V3D_VCOLOREDTEXTUREVERTEX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3dLib/Graphics/Geometry/VVector3f.h>
#include <V3dLib/Graphics/Geometry/VTexCoord2f.h>
#include <V3dLib/Graphics/Geometry/VColor4f.h>
#include <V3dLib/Graphics/Geometry/VVertexDataLayout.h>

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
	typedef v3d::graphics::VVector3f VVector3f;
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

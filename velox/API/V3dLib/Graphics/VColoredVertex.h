#ifndef V3D_VCOLOREDVERTEX_H
#define V3D_VCOLOREDVERTEX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Utils/Graphics/VVertexDataLayout.h>
#include <v3d/Utils/Graphics/VVector3f.h>
#include <v3d/Utils/Graphics/VColor4f.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Vertex with position and color
 *
 * @author sheijk
 */
struct VColoredVertex
{
	typedef v3d::utils::graphics::VVector3f VVector3f;
	typedef v3d::utils::graphics::VColor4f VColor4f;
	typedef v3d::utils::graphics::VVertexDataLayout VVertexDataLayout;

	VColoredVertex()
	{
		VVertexDataLayout::SetPositionOffset<VColoredVertex>();
		VVertexDataLayout::SetColorOffset<VColoredVertex>();
	}

	VVector3f position;
	VColor4f color;

	static VVertexDataLayout layout;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCOLOREDVERTEX_H

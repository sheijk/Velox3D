#ifndef V3D_VCOLOREDVERTEX_H
#define V3D_VCOLOREDVERTEX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3dLib/Graphics/Geometry/VVertexDataLayout.h>
#include <v3dLib//Graphics/Geometry/VVertex3f.h>
#include <V3dLib/Graphics/Geometry/VColor4f.h>

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
	typedef v3d::graphics::VVertex3f VVector3f;
	typedef v3d::graphics::VColor4f VColor4f;
	typedef v3d::graphics::VVertexDataLayout VVertexDataLayout;

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

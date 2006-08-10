#ifndef V3D_VSIMPLEVERTEX_H
#define V3D_VSIMPLEVERTEX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Graphics/Geometry/VVertex3f.h>
#include <V3d/Graphics/Geometry/VVertexDataLayout.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * The simplest vertex structure of all
 *
 * @author sheijk
 */
struct VSimpleVertex
{
	typedef v3d::graphics::VVertex3f VVertex3f;
	typedef v3d::graphics::VVertexDataLayout VVertexDataLayout;

	VSimpleVertex()
	{
		VVertexDataLayout::SetPositionOffset<VSimpleVertex>();
	}

	VVertex3f position;

	static VVertexDataLayout layout;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSIMPLEVERTEX_H

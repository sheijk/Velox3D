#ifndef V3D_VSIMPLEVERTEX_H
#define V3D_VSIMPLEVERTEX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Utils/Graphics/VVector3f.h>
#include <v3d/Utils/Graphics/VVertexDataLayout.h>

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
	typedef v3d::utils::graphics::VVector3f VVector3f;
	typedef v3d::utils::graphics::VVertexDataLayout VVertexDataLayout;

	VSimpleVertex()
	{
		VVertexDataLayout::SetPositionOffset<VSimpleVertex>();
	}

	VVector3f position;

	static VVertexDataLayout layout;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSIMPLEVERTEX_H

#ifndef V3D_VTEXTUREDVERTEX_H
#define V3D_VTEXTUREDVERTEX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Utils/Graphics/VVertexDataLayout.h>
#include <v3d/Utils/Graphics/VVector3f.h>
#include <v3d/Utils/Graphics/VTexCoord2f.h>

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
	typedef v3d::utils::graphics::VVector3f VVector3f;
	typedef v3d::utils::graphics::VTexCoord2f VTexCoord2f;
	typedef v3d::utils::graphics::VVertexDataLayout VVertexDataLayout;

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

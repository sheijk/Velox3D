#ifndef V3D_VSCENEGRAPHTOOLS_H
#define V3D_VSCENEGRAPHTOOLS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/SimpleSG/IVNode.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics{
namespace simplesg {
//-----------------------------------------------------------------------------

/**
 * Generates the absolute transformations from the relative transformations
 * of the node's parents
 */
void UpdateLocations(
	v3d::graphics::simplesg::IVNode* in_pNode, 
	const VMatrix44f& in_Transform
	);

//-----------------------------------------------------------------------------
} // namespace simplesg
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSCENEGRAPHTOOLS_H

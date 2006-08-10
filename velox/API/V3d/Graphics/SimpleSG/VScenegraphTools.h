#ifndef V3D_VSCENEGRAPHTOOLS_H
#define V3D_VSCENEGRAPHTOOLS_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/SimpleSG/IVNode.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics{
//-----------------------------------------------------------------------------

/**
 * Generates the absolute transformations from the relative transformations
 * of the node's parents
 */
void UpdateLocations(
	v3d::graphics::IVNode* in_pNode, 
	const VMatrix44f& in_Transform
	);

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSCENEGRAPHTOOLS_H

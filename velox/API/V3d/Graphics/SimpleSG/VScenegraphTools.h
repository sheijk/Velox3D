/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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
	const math::VMatrix44f& in_Transform
	);

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSCENEGRAPHTOOLS_H


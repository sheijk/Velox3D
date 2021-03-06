/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVRENDERSTATE_H
#define V3D_IVRENDERSTATE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/RangeIter/VRangeIterator.h>
#include <V3d/Graphics/IVParameter.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
class IVStateCategory;

class IVRenderState
{
public:
	virtual const IVStateCategory* GetCategory() const = 0;

	virtual ~IVRenderState() {}

	virtual VRangeIterator<IVParameter> Parameters() = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVRENDERSTATE_H


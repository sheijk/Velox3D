/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VRESIZABLEGEOMETRY_2004_04_10_H
#define V3D_VRESIZABLEGEOMETRY_2004_04_10_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics.h>
#include <V3d/Graphics/Geometry/VDynamicGeometryData.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

template<typename VertexStructure>
class VResizeableGeometryData : public VDynamicGeometryData<VertexStructure>
{
public:
	void ResizeVertexBuffer(vuint in_nSize)
	{
		VDynamicGeometryData<VertexStructure>::ResizeVertexBuffer(in_nSize);
	}

	void ResizeIndexBuffer(vuint in_nSize)
	{
		VDynamicGeometryData<VertexStructure>::ResizeIndexBuffer(in_nSize);
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VRESIZABLEGEOMETRY_2004_04_10_H


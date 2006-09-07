/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VHEIGHTMAP_H
#define V3D_VHEIGHTMAP_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/Geometry/VVertex3f.h>
#include <V3d/Graphics/Geometry/VTexCoord2f.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
#include <V3d/Graphics/VBuffer.h>
#include <V3d/Graphics/Geometry/VDynamicGeometryData.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics{
//-----------------------------------------------------------------------------

/**
 * A heightmap generation geometry provider
 *
 * @author sheijk
 */
template <typename VertexStructure>
class VHeightmapMesh : public VDynamicGeometryData<VertexStructure>
{
	vuint m_nWidth;
	vuint m_nHeight;

	vuint GetVertexCount() const;
	vuint GetIndexCount() const;

	vuint GetVertexNum(vuint x, vuint y) const;
	vfloat32 GetHeight(vuint x, vuint y) const;

public:
	VHeightmapMesh(vuint in_nWidth, vuint in_nHeight);
	VHeightmapMesh();

	void ResetSize(vuint in_nWidth, vuint in_nHeight);

	void GenerateCoordinatesAtZ(vfloat32 in_nZ);
	//void GenerateCoordinates();
	void GenerateTexCoords();
	void GenerateIndices();

	vuint GetWidth() const;
	vuint GetHeight() const;
	VertexStructure& GetVertex(vuint x, vuint y);
	const VertexStructure& GetVertex(vuint x, vuint y) const;
};

//-----------------------------------------------------------------------------
#include "VHeightmapMesh.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VHEIGHTMAP_H


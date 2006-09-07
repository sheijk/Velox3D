/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

template<typename VertexStructure>
VGeometryData<VertexStructure>::VGeometryData(
	GeometryType in_GeometryType,
	vuint in_nVertexCount, 
	vuint in_nIndexCount
	) :
indices(new vuint[in_nIndexCount], in_nIndexCount),
vertices(new VertexStructure[in_nVertexCount], in_nVertexCount),
type(in_GeometryType)
{
}



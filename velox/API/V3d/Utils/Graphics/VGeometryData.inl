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


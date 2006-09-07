/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

template<typename VertexStructure, typename Operation>
void ForEachVertex(VBuffer<VertexStructure>& buffer, Operation& op)
{
	for(vuint index = 0; index < buffer.GetSize(); ++index)
	{
		op(buffer[index]);
	}
}

//-----------------------------------------------------------------------------

template<typename VertexStructure>
void InverseX(VertexStructure& vertex)
{
	vertex.position.x = - vertex.position.x;
}

template<typename VertexStructure>
void InverseY(VertexStructure& vertex)
{
	vertex.position.y = - vertex.position.y;
}

template<typename VertexStructure>
void InverseZ(VertexStructure& vertex)
{
	vertex.position.z = - vertex.position.z;
}

template<typename VertexStructure>
void SwitchYZ(VertexStructure& vertex)
{
	vfloat32 temp = vertex.position.z;
	vertex.position.z = vertex.position.y;
	vertex.position.y = temp;
}

template<typename VertexStructure>
void MirrorTexCoordU(VertexStructure& vertex)
{
	vertex.texCoords.u = 1 - vertex.texCoords.u;
}

template<typename VertexStructure>
void MirrorTexCoordV(VertexStructure& vertex)
{
	vertex.texCoords.v = 1 - vertex.texCoords.v;
}

template<typename VertexStructure>
void SwitchTextCoordUV(VertexStructure& vertex)
{
	vfloat32 u = vertex.texCoords.u;
	vertex.texCoords.u = vertex.texCoords.v;
	vertex.texCoords.v = u;
}



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



template<typename VertexStructure>
v3d::graphics::VMeshDescription BuildMeshDescription(
	v3d::graphics::IVDevice& in_Device,
	VertexStructure pVertices[],
	const vuint in_cnVertexCount
	)
{
	using namespace v3d::graphics;

	// create float buffer
	const floatBufSize = in_cnVertexCount * sizeof(ColoredVertex);
	const floatCount = floatBufSize / sizeof(vfloat32);
	vfloat32* vertexData = new vfloat32[floatCount];

	memcpy(vertexData, pVertices, floatBufSize);

	ColoredVertex* cv = (ColoredVertex*)vertexData;

	VFloatBuffer floatBuf(vertexData, floatBufSize);

	IVDevice::FloatBufferHandle bufHandle
		= in_Device.CreateBuffer(&floatBuf, VFloatBuffer::DropData);

	// create mesh description
	VMeshDescription descr;

	// set vertex coord info
	descr.triangleVertices = VMeshDescription::FloatDataRef(
		bufHandle, 
		ColoredVertex::layout.vertexOffset, 
		in_cnVertexCount, 
		sizeof(ColoredVertex) / sizeof(float)
		);

	// set color info, if contained
	if( VVertexDataLayout::IsValidOffset(VertexStructure::layout.colorOffset) )
	{
		descr.triangleColors = VMeshDescription::FloatDataRef(
			bufHandle,
			ColoredVertex::layout.colorOffset,
			in_cnVertexCount,
			sizeof(ColoredVertex) / sizeof(float)
			);
	}

	//TODO: set tex coord, etc

	return descr;
}

template<typename VertexStructure>
v3d::graphics::VMeshDescription BuildMeshDescription(
	v3d::graphics::IVDevice& in_Device,
	VertexStructure pVertices[],
	const vuint in_cnVertexCount
	)
{
	using namespace v3d::graphics;

	// create float buffer
	const floatBufSize = in_cnVertexCount * sizeof(VertexStructure);
	const floatCount = floatBufSize / sizeof(vfloat32);
	vfloat32* vertexData = new vfloat32[floatCount];

	memcpy(vertexData, pVertices, floatBufSize);

	VertexStructure* cv = (VertexStructure*)vertexData;

	//VFloatBuffer floatBuf(vertexData, floatBufSize);
	IVDevice::Buffer geomBuf(reinterpret_cast<vbyte*>(vertexData), 4 * floatBufSize);

	IVDevice::BufferHandle bufHandle = in_Device.CreateBuffer(
		IVDevice::VertexBuffer, 
		&geomBuf, 
		IVDevice::Buffer::DropData
		);

	//IVDevice::FloatBufferHandle bufHandle
	//	= in_Device.CreateBuffer(&floatBuf, VFloatBuffer::DropData);

	// create mesh description
	VMeshDescription descr;

	const VVertexDataLayout& layout(VertexStructure::layout);

	// set vertex coord info
	descr.triangleVertices = VMeshDescription::ByteDataRef(
		bufHandle, 
		layout.vertexOffset, 
		in_cnVertexCount, 
		sizeof(VertexStructure) / sizeof(float)
		);

	// set color info, if contained
	if( VVertexDataLayout::IsValidOffset(layout.colorOffset) )
	{
		descr.triangleColors = VMeshDescription::ByteDataRef(
			bufHandle,
			layout.colorOffset,
			in_cnVertexCount,
			sizeof(VertexStructure) / sizeof(float)
			);
	}

	// set tex coord if contained
	if( VVertexDataLayout::IsValidOffset(layout.texCoordOffset) )
	{
		descr.triangleTexCoords = VMeshDescription::ByteDataRef(
			bufHandle,
			layout.texCoordOffset,
			in_cnVertexCount,
			sizeof(VertexStructure) / sizeof(float)
			);
	}

	//TODO: set tex coord, etc

	return descr;
}

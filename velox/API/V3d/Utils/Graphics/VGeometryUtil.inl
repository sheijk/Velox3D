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
		vuint(layout.positionOffset), 
		in_cnVertexCount, 
		sizeof(VertexStructure) / sizeof(float)
		);

	// set color info, if contained
	if( VVertexDataLayout::IsValidOffset(layout.colorOffset) )
	{
		descr.triangleColors = VMeshDescription::ByteDataRef(
			bufHandle,
			vuint(layout.colorOffset),
			in_cnVertexCount,
			sizeof(VertexStructure) / sizeof(float)
			);
	}

	// set tex coord if contained
	if( VVertexDataLayout::IsValidOffset(layout.texCoordOffset) )
	{
		descr.triangleTexCoords = VMeshDescription::ByteDataRef(
			bufHandle,
			vuint(layout.texCoordOffset),
			in_cnVertexCount,
			sizeof(VertexStructure) / sizeof(float)
			);
	}

	//TODO: set tex coord, etc

	return descr;
}

template<typename VertexStructure>
v3d::graphics::VMeshDescription BuildMeshDescription(
	v3d::graphics::IVDevice& in_Device,
	VertexStructure in_pVertices[],
	vuint in_nVertexCount,
	vuint in_pIndices[],
	vuint in_nIndexCount
	)
{
	using namespace v3d::graphics;

	// build mesh without indices
	VMeshDescription md = 
		v3d::utils::graphics::BuildMeshDescription(
		in_Device, in_pVertices, in_nVertexCount);

	const vuint cnIndexBufferSize = in_nIndexCount * sizeof(vuint);
	VByteBuffer indexBuffer(new vbyte[cnIndexBufferSize], cnIndexBufferSize);
	memcpy(indexBuffer.GetDataAddress(), in_pIndices, cnIndexBufferSize);

	// add indices
	if( in_pIndices && in_nIndexCount > 0 )
	{
		md.triangleIndices = VMeshDescription::ByteDataRef(
			in_Device.CreateBuffer(
			IVDevice::VertexBuffer,
			&indexBuffer,
			VByteBuffer::DropData
			),
			0,
			in_nIndexCount,
			1
			);
	}

	return md;
}
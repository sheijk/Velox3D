VMeshDescription BuildMeshDescription(
	IVBuffer<vbyte>* bufHandle,
	VVertexDataLayout layout,
	vuint cnVertexCount
	)
{
	VMeshDescription descr;

	// set vertex coord info
	descr.triangleVertices = VMeshDescription::ByteDataRef(
		bufHandle, 
		vuint(layout.positionOffset), 
		cnVertexCount, 
		vuint(layout.vertexSize / sizeof(vfloat32))
		);

	// set color info, if contained
	if( VVertexDataLayout::IsValidOffset(layout.colorOffset) )
	{
		descr.triangleColors = VMeshDescription::ByteDataRef(
			bufHandle,
			vuint(layout.colorOffset),
			cnVertexCount,
			vuint(layout.vertexSize / sizeof(vfloat32))
			);
	}

	// set tex coord if contained
	if( VVertexDataLayout::IsValidOffset(layout.texCoordOffset) )
	{
		descr.triangleTexCoords = VMeshDescription::ByteDataRef(
			bufHandle,
			vuint(layout.texCoordOffset),
			cnVertexCount,
			vuint(layout.vertexSize / sizeof(vfloat32))
			);
	}

	return descr;
}

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
	IVDevice::Buffer geomBuf(reinterpret_cast<vbyte*>(vertexData), floatBufSize);

	IVDevice::BufferHandle bufHandle = in_Device.CreateBuffer(
		IVDevice::VertexBuffer, 
		&geomBuf, 
		IVDevice::Buffer::CopyData
		);

	//IVDevice::FloatBufferHandle bufHandle
	//	= in_Device.CreateBuffer(&floatBuf, VFloatBuffer::DropData);

	const VVertexDataLayout& layout(VertexStructure::layout);

	// create mesh description
	VMeshDescription descr = BuildMeshDescription(
		bufHandle, 
		layout, 
		in_cnVertexCount);

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
		v3d::graphics::BuildMeshDescription(
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
			VByteBuffer::CopyData
			),
			0,
			in_nIndexCount,
			1
			);
	}

	return md;
}

template<typename GeometryProvider>
v3d::graphics::IVDevice::MeshHandle BuildMesh(
	v3d::graphics::IVDevice& device,
	GeometryProvider& provider, 
	v3d::graphics::VMaterialDescription& mat)
{
	v3d::graphics::VMeshDescription meshDescr = BuildMeshDescription(
		device,
		provider.GetVertexBuffer().GetDataAddress(),
		provider.GetVertexBuffer().GetSize(),
		provider.GetIndexBuffer().GetDataAddress(),
		provider.GetIndexBuffer().GetSize()
		);

	meshDescr.geometryType = provider.GetGeometryType();

	return device.CreateMesh(meshDescr, mat);
}

template<typename VertexStructure>
void GenerateInterpolatedTexCoords(
	v3d::graphics::VBuffer<VertexStructure>& buffer,
	vuint width,
	vuint height
	)
{
	V3D_ASSERT(width * height == buffer.GetSize());

	const vfloat32 deltax = 1.0f / vfloat32(width);
	const vfloat32 deltay = 1.0f / vfloat32(height);

	for(vuint x = 0; x < width; ++x)
	for(vuint y = 0; y < height; ++y)
	{
		buffer[x + y*width].texCoords.u = x * deltax;
		buffer[x + y*width].texCoords.v = y * deltay;
	}    
}


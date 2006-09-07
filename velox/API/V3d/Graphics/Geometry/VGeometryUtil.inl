/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

template<typename GeometryProvider>
VVertexFormat BuildFormat(GeometryProvider& in_Geometry)
{
	VVertexDataLayout layout = in_Geometry.GetVertexBuffer()[0].layout;
	vuint cnVertexCount = in_Geometry.GetVertexBuffer().GetSize();

	VVertexFormat format;

	// set vertex coord info
	if( VVertexDataLayout::IsValidOffset(layout.positionOffset) )
	{
		VDataFormat coordFormat;
		coordFormat.SetFirstIndex(vuint(layout.positionOffset));
		coordFormat.SetCount(cnVertexCount);
		coordFormat.SetStride(vuint(layout.vertexSize / sizeof(vfloat32)));

		format.SetCoordinateFormat(coordFormat);
	}

	// set color info, if contained
	if( VVertexDataLayout::IsValidOffset(layout.colorOffset) )
	{
		VDataFormat colorFormat;
		colorFormat.SetFirstIndex(vuint(layout.colorOffset));
		colorFormat.SetCount(cnVertexCount);
		colorFormat.SetStride(vuint(layout.vertexSize / sizeof(vfloat32)));

		format.SetColorFormat(colorFormat);
	}

	// set tex coord if contained
	if( VVertexDataLayout::IsValidOffset(layout.texCoordOffset) )
	{
		VDataFormat texCoordFormat;
		texCoordFormat.SetFirstIndex(vuint(layout.texCoordOffset));
		texCoordFormat.SetCount(cnVertexCount);
		texCoordFormat.SetStride(vuint(layout.vertexSize / sizeof(vfloat32)));

		format.SetTexCoordCount(1);
		format.SetTexCoordFormat(0, texCoordFormat);
	}

	return format;
}

template<typename GeometryProvider>
resource::VResourceId BuildResource(
						  const std::string& in_strResourceName,
						  const GeometryProvider& in_Geometry
						  )
{
	// create resource
	resource::VResourceId res = 
		resource::VResourceManagerPtr()->CreateResource(
			in_strResourceName.c_str());

	// add vertex buffer to resource manager
	VVertexFormat vertexFormat = BuildFormat(in_Geometry);
	res->AddData(new VVertexBuffer(in_Geometry.GetVertexBuffer(), vertexFormat));

	// add mesh description
	VMeshDescription* pMoonMD = new VMeshDescription(vertexFormat);

	pMoonMD->SetGeometryType(in_Geometry.GetGeometryType());

	if( vertexFormat.GetCoordinateFormat().GetCount() > 0 )
		pMoonMD->SetCoordinateResource(res->GetQualifiedName());

	if( vertexFormat.GetColorFormat().GetCount() > 0 )
		pMoonMD->SetColorResource(res->GetQualifiedName());

	for(vuint texCoordId = 0; 
		texCoordId < vertexFormat.GetTexCoordCount(); 
		++texCoordId)
	{
		pMoonMD->SetTexCoordResource(texCoordId, res->GetQualifiedName());
	}

	// if indices are present, create a subresource called indices,
	// add index buffer to them and adjust the mesh descr format
	if( in_Geometry.GetIndexBuffer().GetSize() > 0 &&
		in_Geometry.GetIndexBuffer().GetDataAddress() != 0 )
	{
		// create index format and add index informatio to mesh description
		VVertexFormat indexFormat;
		indexFormat.SetIndexFormat(
			VDataFormat(0, in_Geometry.GetIndexBuffer().GetSize(), 0));
		pMoonMD->SetIndexFormat(indexFormat.GetIndexFormat());
		pMoonMD->SetIndexResource(in_strResourceName + "/indices");

		// add index buffer to sub resource
		resource::VResourceId indexres = res->AddSubResource("indices");
		indexres->AddData(
			new VVertexBuffer(in_Geometry.GetIndexBuffer(), indexFormat));
	}

	res->AddData(pMoonMD);

	return res;
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



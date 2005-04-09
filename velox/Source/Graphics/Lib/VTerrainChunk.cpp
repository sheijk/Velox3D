//#include <V3dLib/Graphics/Generators/VTerrainChunkMesh.h>
////-----------------------------------------------------------------------------
//
////-----------------------------------------------------------------------------
//namespace v3d { 
//namespace graphics {
////-----------------------------------------------------------------------------
//
//v3d::image::IVImageFactory& VTerrainChunk::ImageService()
//{
//	return *QueryObject<v3d::image::IVImageFactory>("image.service");
//}
//
//vuint VTerrainChunk::GetVertexCount()
//{
//	return m_nWidth * m_nHeight;
//}
//
//vuint VTerrainChunk::GetIndexCount()
//{
//	return m_nWidth * (m_nHeight-1) * 2 + ((m_nHeight-1) * 2);
//}
//
//vuint VTerrainChunk::GetVertexNum(vuint x, vuint y)
//{
//	return y * m_nWidth + x;
//}
//
//VTerrainChunk::VertexStructure& VTerrainChunk::GetVertex(vuint x, vuint y)
//{
//	return GetVertexBuffer()[y * m_nWidth + x];
//}
//
//const VTerrainChunk::VertexStructure& VTerrainChunk::GetVertex(vuint x, vuint y) const
//{
//	return GetVertexBuffer()[y * m_nWidth + x];
//}
//
//vfloat32 VTerrainChunk::GetHeight(vuint x, vuint y)
//{
//	return vfloat32(m_pHeightmap->GetData()[y * m_nWidth + x]) / 30.0f;
//}
//
//void VTerrainChunk::GenerateCoordinates()
//{
//	vfloat32 left = -15;
//	vfloat32 right = 15;
//	vfloat32 top = -15;
//	vfloat32 bottom = 15;
//
//	const vfloat32 xdelta = (right - left) / m_nWidth;
//	const vfloat32 ydelta = (bottom - top) / m_nHeight;
//    
//	for(vint x = 0; x < m_nWidth; ++x)
//	{
//		for(vint y = 0; y < m_nHeight; ++y)
//		{
//            GetVertex(x, y).position.x = x * xdelta + left;
//			GetVertex(x, y).position.y = y * ydelta + top;
//			GetVertex(x, y).position.z = GetHeight(x, y);
//		}
//	}
//}
//
//void VTerrainChunk::GenerateTexCoords()
//{
//	GenerateInterpolatedTexCoords(GetVertexBuffer(), m_nWidth, m_nHeight);
//}
//
//void VTerrainChunk::GenerateIndices()
//{
//	vuint num = 0;
//
//	// for each y
//	for(vuint y = 0; y < m_nHeight - 1; ++y)
//	{
//		// create strip
//		for(vint x = 0; x < m_nWidth; ++x)
//		{
//			GetIndexBuffer()[num] = GetVertexNum(x, y);
//			++num;
//
//			GetIndexBuffer()[num] = GetVertexNum(x, y + 1);
//			++num;
//		}
//
//		// add degenerated triangle
//        GetIndexBuffer()[num] = GetVertexNum(x - 1, y + 1);
//		++num;
//		GetIndexBuffer()[num] = GetVertexNum(0, y + 1);
//		++num;
//	}
//
//	V3D_ASSERT(num == GetIndexBuffer().GetSize());
//}
//
//VTerrainChunk::VTerrainChunk(
//	VStringParam in_strHeighmapFile,
//	VStringParam in_strTexture
//	)
//{
//	SetGeometryType(VMeshDescription::TriangleStrip);
//
//	m_strTextureFileName = in_strTexture;
//
//	m_pHeightmap = ImageService().CreateImage(in_strHeighmapFile);
//	m_pTexture = ImageService().CreateImage(in_strTexture);
//
//	m_nHeight = m_pHeightmap->GetHeight();
//	m_nWidth = m_pHeightmap->GetWidth();
//
//	ResizeVertexBuffer(GetVertexCount());
//	ResizeIndexBuffer(GetIndexCount());        
//
//	GenerateCoordinates();
//	GenerateIndices();
//	GenerateTexCoords();
//}
//
//VMaterialDescription VTerrainChunk::GetMaterialDescription(IVDevice& device)
//{
//	VMaterialDescription matDescr =
//		BuildTextureMaterial(&device, m_strTextureFileName.c_str());
//
//	matDescr.depthTestFunction = VMaterialDescription::DepthOnLess;
//	//matDescr.depthWriteMask = VMaterialDescription::DepthReadOnly;
//
//	//matDescr.AddTexture(CreateTextureRef(device, *m_pTexture));
//
//	return matDescr;
//}
//
//vuint VTerrainChunk::GetWidth() const
//{
//	return m_nWidth;
//}
//
//vuint VTerrainChunk::GetHeight() const 
//{
//	return m_nHeight;
//}
//
////-----------------------------------------------------------------------------
//} // namespace graphics
//} // namespace v3d
////-----------------------------------------------------------------------------

/*
template <typename VertexStructure>
VBox::VBox( vfloat32 in_fHeight, vfloat32 in_fWidth, vfloat32 in_fDepth ) 
: m_fHeight(in_fHeight), m_fWidth(in_fWidth), m_fDepth(in_fDepth)
{
	buffer = VBuffer(new VertexStructure[36], 36);
}
*/
using namespace v3d::graphics;

template <typename VertexStructure> 
void VBox<VertexStructure>::CreateCoordinates()
{
	vfloat32 fHeightHalf = m_fHeight / 2.0f;
	vfloat32 fWidthHalf = m_fWidth / 2.0f;
	vfloat32 fDepthHalf = m_fDepth / 2.0f;

	//front face
	buffer[0].vertex = VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[1].vertex = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[2].vertex = VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf);
	
	buffer[3].vertex = VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[4].vertex = VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf);
	buffer[5].vertex = VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);

	//top face
	buffer[6].vertex = VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);
	buffer[7].vertex = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);
	buffer[8].vertex = VVector3f( -fWidthHalf, +fHeightHalf, -fDepthHalf);

	buffer[9].vertex =  VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);
	buffer[10].vertex = VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf);
	buffer[11].vertex = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);


	//back face
	buffer[12].vertex = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[13].vertex = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);
	buffer[14].vertex = VVector3f( +fWidthHalf, -fHeightHalf, -fDepthHalf);
	
	buffer[15].vertex = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[16].vertex = VVector3f( -fWidthHalf, +fHeightHalf, -fDepthHalf);
	buffer[17].vertex = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);
	
	//bottom face
	buffer[18].vertex = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[19].vertex = VVector3f( +fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[20].vertex = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);

    buffer[21].vertex = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[22].vertex = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[23].vertex = VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf);

	//right face
	buffer[24].vertex = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[25].vertex = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);
	buffer[26].vertex = VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf);


	buffer[27].vertex = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[28].vertex = VVector3f( +fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[29].vertex = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);


	//left face
	buffer[30].vertex = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[31].vertex = VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);
	buffer[32].vertex = VVector3f( -fWidthHalf, +fHeightHalf, -fDepthHalf);

	buffer[33].vertex = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[34].vertex = VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[35].vertex = VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);

}

template <typename VertexStructure>
void VBox<VertexStructure>::CreateTextureCoordinates()
{
	//front face
	buffer[0].texCoord = VTexCoord2f(0.0f, 0.0f);
	buffer[1].texCoord = VTexCoord2f(1.0f, 0.0f);
	buffer[2].texCoord = VTexCoord2f(1.0f, 1.0f);

	buffer[3].texCoord = VTexCoord2f(0.0f, 0.0f);
	buffer[4].texCoord = VTexCoord2f(1.0f, 1.0f);
	buffer[5].texCoord = VTexCoord2f(0.0f, 1.0f);
	
	//top face
	buffer[6].texCoord = VTexCoord2f(0.0f, 0.0f);
	buffer[7].texCoord = VTexCoord2f(1.0f, 1.0f);
	buffer[8].texCoord = VTexCoord2f(0.0f, 1.0f);

	buffer[9].texCoord = VTexCoord2f(0.0f, 0.0f);
	buffer[10].texCoord = VTexCoord2f(1.0f, 0.0f);
	buffer[11].texCoord = VTexCoord2f(1.0f, 1.0f);

	//back face

	buffer[12].texCoord = VTexCoord2f(1.0f, 0.0f);
	buffer[13].texCoord = VTexCoord2f(0.0f, 1.0f);
	buffer[14].texCoord = VTexCoord2f(0.0f, 0.0f);
	
	buffer[15].texCoord = VTexCoord2f(1.0f, 0.0f);
	buffer[16].texCoord = VTexCoord2f(1.0f, 1.0f);
	buffer[17].texCoord = VTexCoord2f(0.0f, 1.0f);
	
	//bottom face
	buffer[18].texCoord = VTexCoord2f(1.0f, 0.0f);
	buffer[19].texCoord = VTexCoord2f(0.0f, 0.0f);
	buffer[20].texCoord = VTexCoord2f(0.0f, 1.0f);

	buffer[21].texCoord = VTexCoord2f(1.0f, 0.0f);
	buffer[22].texCoord = VTexCoord2f(0.0f, 1.0f);
	buffer[23].texCoord = VTexCoord2f(1.0f, 1.0f);

	//right face
	buffer[24].texCoord = VTexCoord2f(0.0f, 0.0f);
	buffer[25].texCoord = VTexCoord2f(1.0f, 1.0f);
	buffer[26].texCoord = VTexCoord2f(0.0f, 1.0f);

	buffer[27].texCoord = VTexCoord2f(0.0f, 0.0f);
	buffer[28].texCoord = VTexCoord2f(1.0f, 0.0f);
	buffer[29].texCoord = VTexCoord2f(1.0f, 1.0f);

	//bottom face
	buffer[30].texCoord = VTexCoord2f(0.0f, 0.0f);
	buffer[31].texCoord = VTexCoord2f(1.0f, 1.0f);
	buffer[32].texCoord = VTexCoord2f(0.0f, 1.0f);

	buffer[33].texCoord = VTexCoord2f(0.0f, 0.0f);
	buffer[34].texCoord = VTexCoord2f(1.0f, 0.0f);
	buffer[35].texCoord = VTexCoord2f(1.0f, 1.0f);
}
/*
template <typename VertexStructure>
v3d::graphics::VByteBuffer VBox<VertexStructure>::GetByteBuffer()
{
	return VByteBuffer( reinterpret_cast<vbyte*>( buffer.GetDataAdress() ),
						buffer.GetSize() * sizeof(VertexStructure)  );
}*/


using namespace v3d::graphics;

template <typename VertexStructure> 
void VBox<VertexStructure>::CreateCoordinates()
{
	vfloat32 fHeightHalf = m_fHeight / 2.0f;
	vfloat32 fWidthHalf = m_fWidth / 2.0f;
	vfloat32 fDepthHalf = m_fDepth / 2.0f;

	//front face
	buffer[0].position = VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[1].position = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[2].position = VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf);
	
	buffer[3].position = VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[4].position = VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf);
	buffer[5].position = VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);

	//top face
	buffer[6].position = VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);
	buffer[7].position = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);
	buffer[8].position = VVector3f( -fWidthHalf, +fHeightHalf, -fDepthHalf);

	buffer[9].position =  VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);
	buffer[10].position = VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf);
	buffer[11].position = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);


	//back face
	buffer[12].position = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[13].position = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);
	buffer[14].position = VVector3f( +fWidthHalf, -fHeightHalf, -fDepthHalf);
	
	buffer[15].position = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[16].position = VVector3f( -fWidthHalf, +fHeightHalf, -fDepthHalf);
	buffer[17].position = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);
	
	//bottom face
	buffer[18].position = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[19].position = VVector3f( +fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[20].position = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);

    buffer[21].position = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[22].position = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[23].position = VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf);

	//right face
	buffer[24].position = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[25].position = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);
	buffer[26].position = VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf);


	buffer[27].position = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[28].position = VVector3f( +fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[29].position = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);


	//left face
	buffer[30].position = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[31].position = VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);
	buffer[32].position = VVector3f( -fWidthHalf, +fHeightHalf, -fDepthHalf);

	buffer[33].position = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	buffer[34].position = VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf);
	buffer[35].position = VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);

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

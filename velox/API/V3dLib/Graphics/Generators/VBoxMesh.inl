template <typename VertexStructure> 
void VBoxMesh<VertexStructure>::GenerateCoordinates()
{
	using namespace v3d::graphics;

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
void VBoxMesh<VertexStructure>::GenerateTexCoords()
{
	using namespace v3d::graphics;

	//front face
	buffer[0].texCoords = VTexCoord2f(0.0f, 0.0f);
	buffer[1].texCoords = VTexCoord2f(1.0f, 0.0f);
	buffer[2].texCoords = VTexCoord2f(1.0f, 1.0f);

	buffer[3].texCoords = VTexCoord2f(0.0f, 0.0f);
	buffer[4].texCoords = VTexCoord2f(1.0f, 1.0f);
	buffer[5].texCoords = VTexCoord2f(0.0f, 1.0f);
	
	//top face
	buffer[6].texCoords = VTexCoord2f(0.0f, 0.0f);
	buffer[7].texCoords = VTexCoord2f(1.0f, 1.0f);
	buffer[8].texCoords = VTexCoord2f(0.0f, 1.0f);

	buffer[9].texCoords = VTexCoord2f(0.0f, 0.0f);
	buffer[10].texCoords = VTexCoord2f(1.0f, 0.0f);
	buffer[11].texCoords = VTexCoord2f(1.0f, 1.0f);

	//back face

	buffer[12].texCoords = VTexCoord2f(1.0f, 0.0f);
	buffer[13].texCoords = VTexCoord2f(0.0f, 1.0f);
	buffer[14].texCoords = VTexCoord2f(0.0f, 0.0f);
	
	buffer[15].texCoords = VTexCoord2f(1.0f, 0.0f);
	buffer[16].texCoords = VTexCoord2f(1.0f, 1.0f);
	buffer[17].texCoords = VTexCoord2f(0.0f, 1.0f);
	
	//bottom face
	buffer[18].texCoords = VTexCoord2f(1.0f, 0.0f);
	buffer[19].texCoords = VTexCoord2f(0.0f, 0.0f);
	buffer[20].texCoords = VTexCoord2f(0.0f, 1.0f);

	buffer[21].texCoords = VTexCoord2f(1.0f, 0.0f);
	buffer[22].texCoords = VTexCoord2f(0.0f, 1.0f);
	buffer[23].texCoords = VTexCoord2f(1.0f, 1.0f);

	//right face
	buffer[24].texCoords = VTexCoord2f(0.0f, 0.0f);
	buffer[25].texCoords = VTexCoord2f(1.0f, 1.0f);
	buffer[26].texCoords = VTexCoord2f(0.0f, 1.0f);

	buffer[27].texCoords = VTexCoord2f(0.0f, 0.0f);
	buffer[28].texCoords = VTexCoord2f(1.0f, 0.0f);
	buffer[29].texCoords = VTexCoord2f(1.0f, 1.0f);

	//bottom face
	buffer[30].texCoords = VTexCoord2f(0.0f, 0.0f);
	buffer[31].texCoords = VTexCoord2f(1.0f, 1.0f);
	buffer[32].texCoords = VTexCoord2f(0.0f, 1.0f);

	buffer[33].texCoords = VTexCoord2f(0.0f, 0.0f);
	buffer[34].texCoords = VTexCoord2f(1.0f, 0.0f);
	buffer[35].texCoords = VTexCoord2f(1.0f, 1.0f);
}

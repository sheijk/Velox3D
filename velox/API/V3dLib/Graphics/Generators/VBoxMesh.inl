template <typename VertexStructure> 
void VBoxMesh<VertexStructure>::GenerateCoordinates()
{
	using namespace v3d::graphics;

	vfloat32 fHeightHalf = m_fHeight / 2.0f;
	vfloat32 fWidthHalf = m_fWidth / 2.0f;
	vfloat32 fDepthHalf = m_fDepth / 2.0f;

	//front face
	GetVertexBuffer()[0].position = VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf);
	GetVertexBuffer()[1].position = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);
	GetVertexBuffer()[2].position = VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf);
	
	GetVertexBuffer()[3].position = VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf);
	GetVertexBuffer()[4].position = VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf);
	GetVertexBuffer()[5].position = VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);

	//top face
	GetVertexBuffer()[6].position = VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);
	GetVertexBuffer()[7].position = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);
	GetVertexBuffer()[8].position = VVector3f( -fWidthHalf, +fHeightHalf, -fDepthHalf);

	GetVertexBuffer()[9].position =  VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);
	GetVertexBuffer()[10].position = VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf);
	GetVertexBuffer()[11].position = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);


	//back face
	GetVertexBuffer()[12].position = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	GetVertexBuffer()[13].position = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);
	GetVertexBuffer()[14].position = VVector3f( +fWidthHalf, -fHeightHalf, -fDepthHalf);
	
	GetVertexBuffer()[15].position = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	GetVertexBuffer()[16].position = VVector3f( -fWidthHalf, +fHeightHalf, -fDepthHalf);
	GetVertexBuffer()[17].position = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);
	
	//bottom face
	GetVertexBuffer()[18].position = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	GetVertexBuffer()[19].position = VVector3f( +fWidthHalf, -fHeightHalf, -fDepthHalf);
	GetVertexBuffer()[20].position = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);

    GetVertexBuffer()[21].position = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	GetVertexBuffer()[22].position = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);
	GetVertexBuffer()[23].position = VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf);

	//right face
	GetVertexBuffer()[24].position = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);
	GetVertexBuffer()[25].position = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);
	GetVertexBuffer()[26].position = VVector3f( +fWidthHalf, +fHeightHalf, +fDepthHalf);


	GetVertexBuffer()[27].position = VVector3f( +fWidthHalf, -fHeightHalf, +fDepthHalf);
	GetVertexBuffer()[28].position = VVector3f( +fWidthHalf, -fHeightHalf, -fDepthHalf);
	GetVertexBuffer()[29].position = VVector3f( +fWidthHalf, +fHeightHalf, -fDepthHalf);


	//left face
	GetVertexBuffer()[30].position = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	GetVertexBuffer()[31].position = VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);
	GetVertexBuffer()[32].position = VVector3f( -fWidthHalf, +fHeightHalf, -fDepthHalf);

	GetVertexBuffer()[33].position = VVector3f( -fWidthHalf, -fHeightHalf, -fDepthHalf);
	GetVertexBuffer()[34].position = VVector3f( -fWidthHalf, -fHeightHalf, +fDepthHalf);
	GetVertexBuffer()[35].position = VVector3f( -fWidthHalf, +fHeightHalf, +fDepthHalf);

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

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
	GetVertexBuffer()[0].texCoords = VTexCoord2f(0.0f, 0.0f);
	GetVertexBuffer()[1].texCoords = VTexCoord2f(1.0f, 0.0f);
	GetVertexBuffer()[2].texCoords = VTexCoord2f(1.0f, 1.0f);

	GetVertexBuffer()[3].texCoords = VTexCoord2f(0.0f, 0.0f);
	GetVertexBuffer()[4].texCoords = VTexCoord2f(1.0f, 1.0f);
	GetVertexBuffer()[5].texCoords = VTexCoord2f(0.0f, 1.0f);
	
	//top face
	GetVertexBuffer()[6].texCoords = VTexCoord2f(0.0f, 0.0f);
	GetVertexBuffer()[7].texCoords = VTexCoord2f(1.0f, 1.0f);
	GetVertexBuffer()[8].texCoords = VTexCoord2f(0.0f, 1.0f);

	GetVertexBuffer()[9].texCoords = VTexCoord2f(0.0f, 0.0f);
	GetVertexBuffer()[10].texCoords = VTexCoord2f(1.0f, 0.0f);
	GetVertexBuffer()[11].texCoords = VTexCoord2f(1.0f, 1.0f);

	//back face

	GetVertexBuffer()[12].texCoords = VTexCoord2f(1.0f, 0.0f);
	GetVertexBuffer()[13].texCoords = VTexCoord2f(0.0f, 1.0f);
	GetVertexBuffer()[14].texCoords = VTexCoord2f(0.0f, 0.0f);
	
	GetVertexBuffer()[15].texCoords = VTexCoord2f(1.0f, 0.0f);
	GetVertexBuffer()[16].texCoords = VTexCoord2f(1.0f, 1.0f);
	GetVertexBuffer()[17].texCoords = VTexCoord2f(0.0f, 1.0f);
	
	//bottom face
	GetVertexBuffer()[18].texCoords = VTexCoord2f(1.0f, 0.0f);
	GetVertexBuffer()[19].texCoords = VTexCoord2f(0.0f, 0.0f);
	GetVertexBuffer()[20].texCoords = VTexCoord2f(0.0f, 1.0f);

	GetVertexBuffer()[21].texCoords = VTexCoord2f(1.0f, 0.0f);
	GetVertexBuffer()[22].texCoords = VTexCoord2f(0.0f, 1.0f);
	GetVertexBuffer()[23].texCoords = VTexCoord2f(1.0f, 1.0f);

	//right face
	GetVertexBuffer()[24].texCoords = VTexCoord2f(0.0f, 0.0f);
	GetVertexBuffer()[25].texCoords = VTexCoord2f(1.0f, 1.0f);
	GetVertexBuffer()[26].texCoords = VTexCoord2f(0.0f, 1.0f);

	GetVertexBuffer()[27].texCoords = VTexCoord2f(0.0f, 0.0f);
	GetVertexBuffer()[28].texCoords = VTexCoord2f(1.0f, 0.0f);
	GetVertexBuffer()[29].texCoords = VTexCoord2f(1.0f, 1.0f);

	//bottom face
	GetVertexBuffer()[30].texCoords = VTexCoord2f(0.0f, 0.0f);
	GetVertexBuffer()[31].texCoords = VTexCoord2f(1.0f, 1.0f);
	GetVertexBuffer()[32].texCoords = VTexCoord2f(0.0f, 1.0f);

	GetVertexBuffer()[33].texCoords = VTexCoord2f(0.0f, 0.0f);
	GetVertexBuffer()[34].texCoords = VTexCoord2f(1.0f, 0.0f);
	GetVertexBuffer()[35].texCoords = VTexCoord2f(1.0f, 1.0f);
}

#include <v3dLib/Graphics/Renderers/BSP/VBSPRenderer.h>
#include <string>

#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d::utils;

VBSPRenderer::VBSPRenderer(IVDevice* in_pDevice, IVCamera* in_pCamera)
{
	m_iNumSortedLightmapElements	= 0;
	m_pLightmapCoordsSorted			= 0;
	m_pLightmapCoords				= 0;
	m_pDevice						= in_pDevice;   

	m_pCamera						= in_pCamera;

	m_TexEffectList.reserve(200);
	m_LightEffectList.reserve(20);
}
//-----------------------------------------------------------------------------

void VBSPRenderer::Create(VStringParam in_sName)
{
	m_Level.Create(in_sName);

	CreateTextures();
	AddLightmapEffect();

 	CreateVertexBuffer();
	CreateLightmapCoords();
	BuildMesh();
	
}
//-----------------------------------------------------------------------------

VBSPRenderer::~VBSPRenderer()
{
}

//-----------------------------------------------------------------------------
void VBSPRenderer::Delete()
{
	//clean meshlist
	std::list<IVDevice::MeshHandle>::iterator iterBegin = m_MeshList.begin();

	for(iterBegin; iterBegin != m_MeshList.end(); ++iterBegin)
	{
		m_pDevice->DeleteMesh(*iterBegin);
	}

	std::list<IVDevice::BufferHandle>::iterator iterBufferHandle;
	iterBufferHandle = m_BufferHandleList.begin();

	for(; iterBufferHandle != m_BufferHandleList.end(); ++iterBufferHandle)
	{
		m_pDevice->DeleteBuffer(*iterBufferHandle);
	}
}
//-----------------------------------------------------------------------------

void VBSPRenderer::Render()
{
	for (int i = 0; i < m_Bla; i++)
	{
		//RenderMesh(*m_pDevice, m_MeshLightTable[i]);
		RenderMesh(*m_pDevice, m_MeshTextureTable[i]);
	}

	//int leafIndex = FindLeaf(m_pCamera->GetPosition());

	//// Grab the cluster that is assigned to the leaf
	//int cluster = m_Level.GetLeafPointer()[leafIndex].iCluster;

	//// Initialize our counter variables (start at the last leaf and work down)
	//int i = m_Level.GetLeafCount();
	//
	////g_VisibleFaces = 0;

	//// Go through all the leafs and check their visibility
	//while(i--)
	//{
	//	// Get the current leaf that is to be tested for visibility from our camera's leaf
	//	VQ3BSPImporter::BSPLeaf* pLeaf = &(m_Level.GetLeafPointer()[i]);
 //       
	//	// If the current leaf can't be seen from our cluster, go to the next leaf
	//	if(!IsClusterVisible(cluster, pLeaf->iCluster)) 
	//		continue;

	//	//// If the current leaf is not in the camera's frustum, go to the next leaf
	//	//if(!g_Frustum.BoxInFrustum((float)pLeaf->min.x, (float)pLeaf->min.y, (float)pLeaf->min.z,
	//	//	(float)pLeaf->max.x, (float)pLeaf->max.y, (float)pLeaf->max.z))
	//	//	continue;

	//	// If we get here, the leaf we are testing must be visible in our camera's view.
	//	// Get the number of faces that this leaf is in charge of.
	//	int faceCount = pLeaf->iNumLeafFaces;

	//	// Loop through and render all of the faces in this leaf
	//	while(faceCount--)
	//	{
	//		// Grab the current face index from our leaf faces array
	//		int faceIndex = m_Level.GetLeafFacePointer()[pLeaf->iLeafFace + faceCount];
	//		if(faceIndex < m_Bla)
	//		{
	//		//	RenderMesh(*m_pDevice, m_MeshLightTable[faceIndex]);
	//			RenderMesh(*m_pDevice, m_MeshTextureTable[faceIndex]);
	//		}
	//	}
	//}
}
//-----------------------------------------------------------------------------

void VBSPRenderer::CreateVertexBuffer()
{

	m_GeometryData.ResizeVertexBuffer(m_Level.GetVertexCount());
	m_GeometryData.SetGeometryType(VMeshDescription::GeometryType::TriangleFan);
	
	m_pLightmapCoords = new vfloat32[2 * m_Level.GetVertexCount()];
		
	//write all geometry data from the importer to a device usable format
	for (int i=0; i < m_Level.GetVertexCount(); i++)
	{
		m_GeometryData.GetVertexBuffer()[i].position.x = m_Level.GetVertexPointer()[i].Vertex.x;
		m_GeometryData.GetVertexBuffer()[i].position.y = m_Level.GetVertexPointer()[i].Vertex.y;
		m_GeometryData.GetVertexBuffer()[i].position.z = m_Level.GetVertexPointer()[i].Vertex.z;

		m_GeometryData.GetVertexBuffer()[i].texCoords.u = m_Level.GetVertexPointer()[i].TextureCoord.u;
		m_GeometryData.GetVertexBuffer()[i].texCoords.v = m_Level.GetVertexPointer()[i].TextureCoord.v;

		m_pLightmapCoords[i*2]    = m_Level.GetVertexPointer()[i].LightmapCoord.u;
		m_pLightmapCoords[i*2+1]  = m_Level.GetVertexPointer()[i].LightmapCoord.v;
	}
}
//-----------------------------------------------------------------------------

void VBSPRenderer::BuildMesh()
{
	VMeshDescription meshTextured = 
		BuildMeshDescription<VTexturedVertex>(
		*m_pDevice,
		m_GeometryData.GetVertexBuffer().GetDataAddress(),
		m_Level.GetVertexCount()
		);

	VEffectDescription* pDefaultEffect = new VEffectDescription;

	CreateEmptyEffect(*pDefaultEffect);

	//std::vector<IVDevice::BufferHandle>* bufferVector =  &meshTextured.GetAllBuffers();
	///TODO: FIXME!!
	/*std::vector<IVDevice::BufferHandle>::iterator iterHandle;
	iterHandle = meshTextured.GetAllBuffers().begin();

	for(; iterHandle != meshTextured.GetAllBuffers().end(); ++iterHandle)
	{
		m_BufferHandleList.push_back(*iterHandle);
	}
*/

	m_Bla = 0;


	// create lightmap buffer
	IVDevice::Buffer lightCoords(
		reinterpret_cast<vbyte*>(m_pLightmapCoordsSorted),
		sizeof(vfloat32)*m_iNumSortedLightmapElements*2);

	IVDevice::BufferHandle lightbuffer =  m_pDevice->CreateBuffer(
		IVDevice::VertexBuffer,
		&lightCoords,
		IVDevice::Buffer::CopyData);

	m_BufferHandleList.push_back(lightbuffer);

	m_MeshTextureTable = new IVDevice::MeshHandle[m_Level.GetFaceCount()];
	m_MeshLightTable = new IVDevice::MeshHandle[m_Level.GetFaceCount()];

	//build our index list thus we know how to render the faces
	for(int i = 0; i<m_Level.GetFaceCount(); i++)
	{
		vuint count = 0;
		utils::VQ3BSPImporter::BSPFace* face = &m_Level.GetFacePointer()[i];

		m_GeometryData.ResizeIndexBuffer(face->iNumVertices);

		/*std::string sTexName = m_Level.GetTexturePointer()[face->iTextureID].sTextureName;
		if(sTexName == "textures/radiant/notex")
			break;*/

		for(vint32 j = face->iVertexIndexStart;
			j < face->iNumVertices + face->iVertexIndexStart;
			j++
			)
		{
    		m_GeometryData.GetIndexBuffer()[count] = (vuint)j;
			count++;
		}

		//TODO: fix mem leak
		const vuint cnIndexBufferSize = face->iNumVertices * sizeof(vuint);
		VByteBuffer indexBuffer(new vbyte[cnIndexBufferSize], cnIndexBufferSize);
		
		memcpy(
			indexBuffer.GetDataAddress(),
			m_GeometryData.GetIndexBuffer().GetDataAddress(),
			cnIndexBufferSize
			);

		
		IVDevice::BufferHandle indexData = 
			m_pDevice->CreateBuffer(
				IVDevice::VertexBuffer,
				&indexBuffer,
				VByteBuffer::DropData
				);

		meshTextured.SetIndexData(
			indexData,
			VDataFormat(0, face->iNumVertices, 1)
			);

		m_BufferHandleList.push_back(indexData);

		meshTextured.SetGeometryType(m_GeometryData.GetGeometryType());

		VMeshDescription meshLight = meshTextured;

		meshLight.SetTexCoordData(
			0,
			lightbuffer,
			VDataFormat(0, face->iNumVertices, 2)
			);

		VEffectDescription* pEffectTexture = 0;
		pEffectTexture = new VEffectDescription();
		VEffectDescription* pEffectLight = 0;
		pEffectLight = new VEffectDescription();

	/*	if(face->iTextureID > (vint)m_TextureNameList.size())
		{
			vout << "no texture given" << vendl;
			break;
		}
	*///	else
		{
		

			if((face->iTextureID > -1) && (face->iTextureID <= m_Level.GetTextureCount()))
			{
				pEffectTexture = m_TexEffectList[face->iTextureID];
			}
			else 
				pEffectTexture = pDefaultEffect;
	        
			if(face->iLightmapID > -1)
			{
				pEffectLight   = m_LightEffectList[face->iLightmapID];
			}
			else
				pEffectLight = pDefaultEffect;
			
			IVDevice::MeshHandle meshHandleTexture = m_pDevice->CreateMesh(
				meshTextured,
				*pEffectTexture
				);

			IVDevice::MeshHandle meshHandleLight = m_pDevice->CreateMesh(
				meshLight,
				*pEffectLight
				);

	//		PrintEffectDescription(effect);

			//m_MeshList.push_back(meshHandleLight);
			//m_MeshList.push_back(meshHandleTexture);

			m_MeshTextureTable[m_Bla] = meshHandleTexture;
			m_MeshLightTable[m_Bla] =	meshHandleLight;
			m_Bla++;



		}
	}
}

//-----------------------------------------------------------------------------
void VBSPRenderer::CreateTextures()
{
	vout << "loading textures:" << vendl;

	for(int i = 0; i < m_Level.GetTextureCount(); i++)
	{
		std::string sBaseTextureName;
		std::string sTextureName(m_Level.GetTexturePointer()[i].sTextureName);
		//std::string sTextureName("/data/right.jpg");
		
		if(sTextureName =="textures/radiant/notex")
			vout << "warning: noshader found" << vendl;
		else
		{
			sTextureName.insert(0,"/data/");
			sBaseTextureName = sTextureName;

			try
			{
				sTextureName.append(".jpg");
				vout << "using texture: " << sTextureName << vendl;
				AddTextureEffect(sTextureName.c_str());
				m_TextureNameList.push_back(sTextureName);
			}
			
			catch(VException e)
			{
				try
				{
					sBaseTextureName.append(".tga");
					vout << "using texture: " << sBaseTextureName << vendl;
					AddTextureEffect(sBaseTextureName.c_str());
					m_TextureNameList.push_back(sTextureName);
				}
				catch(VException e2)
				{
					vout << "warning: skipping texture" << sTextureName << "/tga" << vendl;
				}
			}
		}
	}
	vout << "loading texture list done..." << vendl;
}

//-----------------------------------------------------------------------------
void VBSPRenderer::AddLightmapEffect()
{
	for(int i = 0; i<m_Level.GetLightmapCount(); i++)
	{
		//FIX: who deletes this?
		VBuffer<vbyte>* pLightmapBuffer = new VBuffer<vbyte>(
			m_Level.GetLightmapPointer()[i].LightmapData,
			49152);

		IVDevice::BufferHandle hTexBuffer = 
			m_pDevice->CreateBuffer(
				IVDevice::Texture,
				pLightmapBuffer,
				IVDevice::Buffer::DropData
				);
		
		//data copied. no longer needed
		//delete buffer;

		//store reference in list for final deleting
		m_BufferHandleList.push_back(hTexBuffer);


		VEffectDescription* pEffect = new VEffectDescription;
		
		VRenderPass& pass(pEffect->AddShaderPath().AddRenderPass());

		pass.AddState(DefaultColorState(VColor4f(1, 1, 1, 1)));
		pass.AddState(PolygonModeState(PMFilled, PMFilled));
		pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthReadOnly));
		pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
		pass.AddState(BlendingState(BlendDisabled, BlendDestColor, BlendSourceColor));

		VState textureState = TextureState(
			hTexBuffer,
			128, 128,
			FilterLinear, FilterLinear,
			TextureRepeat, TextureRepeat);

		pass.AddState(textureState);

		m_LightEffectList.push_back(pEffect);
	}
}
//-----------------------------------------------------------------------------

void VBSPRenderer::CreateLightmapCoords()
{
	vuint nCount = 0;

	utils::VQ3BSPImporter::BSPFace* face;

	// count how many coords we need
	for(int i = 0; i<m_Level.GetFaceCount(); i++)
	{
		face = &m_Level.GetFacePointer()[i];
		nCount += face->iNumVertices;
	}

	m_pLightmapCoordsSorted = new vfloat32[nCount*2];
	m_iNumSortedLightmapElements = nCount;

	nCount = 0;

	//traversal faces and sort Lightmapscoords
	for(vint32 i = 0; i<m_Level.GetFaceCount(); i++)
	{
		face = &m_Level.GetFacePointer()[i];

		for(vint32 j = face->iVertexIndexStart;
			j < face->iNumVertices + face->iVertexIndexStart;
			j++
			)
		{
			m_pLightmapCoordsSorted[nCount*2]   = m_pLightmapCoords[j*2];
			m_pLightmapCoordsSorted[nCount*2+1] = m_pLightmapCoords[j*2+1];
			nCount++;
		}
	}
}

//-----------------------------------------------------------------------------
void VBSPRenderer::AddTextureEffect(VStringParam in_sTextureName)
{
	VEffectDescription* texEffect = new VEffectDescription();

	VRenderPass& pass(texEffect->AddShaderPath().AddRenderPass());

	pass.AddState(DefaultColorState(VColor4f(1, 1, 1, 1)));
	pass.AddState(PolygonModeState(PMFilled, PMFilled));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthWrite));
	pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
	pass.AddState(BlendingState(BlendDisabled, BlendZero, BlendSourceColor));

	image::VImageServicePtr pImageService;
	image::IVImageFactory::ImagePtr image =
		pImageService->CreateImage(in_sTextureName);

	IVDevice::BufferHandle hTexBuffer = 
		m_pDevice->CreateBuffer(
		IVDevice::Texture,
		&image->GetData(),
		IVDevice::Buffer::DropData);

	VState textureState = TextureState(
		hTexBuffer,
		image->GetWidth(), image->GetHeight(),
		FilterLinear, FilterLinear,
		TextureRepeat, TextureRepeat);

	pass.AddState(textureState);

	m_TexEffectList.push_back(texEffect);
	m_BufferHandleList.push_back(hTexBuffer);
}

void VBSPRenderer::CreateEmptyEffect(VEffectDescription& in_rEffect)
{
	VRenderPass& pass(in_rEffect.AddShaderPath().AddRenderPass());

	pass.AddState(DefaultColorState(VColor4f(1, 1, 1, 1)));
	pass.AddState(PolygonModeState(PMFilled, PMFilled));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthWrite));
	pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
	pass.AddState(BlendingState(BlendEnabled, BlendZero, BlendSourceColor));

	image::VImageServicePtr pImageService;
	static image::IVImageFactory::ImagePtr image =
		pImageService->CreateImage("/data/right.jpg");

	static IVDevice::BufferHandle hTexBuffer = 
		m_pDevice->CreateBuffer(
		IVDevice::Texture,
		&image->GetData(),
		IVDevice::Buffer::DropData);

	VState textureState = TextureState(
		hTexBuffer,
		image->GetWidth(), image->GetHeight(),
		FilterLinear, FilterLinear,
		TextureRepeat, TextureRepeat);

	pass.AddState(textureState);

	m_TexEffectList.push_back(&in_rEffect);
	//m_BufferHandleList.push_back(hTexBuffer);
}

vint VBSPRenderer::FindLeaf(Vector in_Pos)
{
	vint iIndex = 0;

	while(iIndex >= 0)
	{
		VQ3BSPImporter::BSPNode*	pNode	=
			&m_Level.GetNodePointer()[iIndex];
		VQ3BSPImporter::BSPPlane*	pPlane	= 
			&m_Level.GetPlanePointer()[pNode->iPLane];

		VVector<float, 3> plane;
		plane.Set(0, pPlane->Normal.x);
		plane.Set(1, pPlane->Normal.y);
		plane.Set(2, pPlane->Normal.z);
		
		float fDistance = Dot(plane, in_Pos);
		fDistance = fDistance - pPlane->fDistance;
		
		if(fDistance >= 0)
			iIndex = pNode->iFront;
		else
			iIndex = pNode->iBack;
	}

	return ~iIndex; //(-(i-1))
}

vbool VBSPRenderer::IsClusterVisible(vint in_VisCluster, vint in_TestCluster)
{

	if ((m_Level.GetPVSData()->pCluster == 0) || (in_VisCluster < 0))
		return true;

	vint i = (in_VisCluster * m_Level.GetPVSData()->iClusterbytes) 
		+ (in_TestCluster >> 3);
	
	vuint8 visSet = m_Level.GetPVSData()->pCluster[i];

	return (visSet & (1 << (in_TestCluster & 7))) != 0;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------

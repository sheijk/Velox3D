#include <V3dLib/Graphics/Renderers/BSP/VBSPRenderer.h>
#include <V3dLib/Graphics/Geometry/VGeometryUtil.h>
#include <V3dLib/Graphics/Geometry/VGeometryData.h>
#include <v3dlib/Graphics/Misc/MiscUtils.h>
#include <V3d/Math/VMatrixOps.h>
#include <V3d/Math/TransformationOps.h>
#include <v3d/Core/VIOStream.h>
#include <v3d/Image/IVImageFactory.h>
#include <v3d/Vfs/VIOException.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VBSPRenderer::VBSPRenderer(IVDevice* in_pDevice, VMultipassDrawList& in_DrawList)
{
	m_iNumFaceElements = 0;
	m_pDevice = in_pDevice;   
	m_pDrawList = &in_DrawList;

	//TODO: FIX LEVEL LOADING
	m_Level.LoadQ3Level("/data/Level.bsp");
    GetFaceElements();
	CreateTextures();
	CreateLightmaps();
    

	BuildCell();
	BuildModelList();
	

	m_bModelAdded = false;
}

VBSPRenderer::~VBSPRenderer()
{
	std::vector<VMaterialDescription*>::iterator matListIter;

	matListIter = m_MaterialList.begin();

	for(matListIter; matListIter != m_MaterialList.end(); ++matListIter)
	{
		delete *(matListIter);
	}

	std::list<VModel*>::iterator modelListIter;

	modelListIter = m_pModelList.begin();

	for(modelListIter; modelListIter != m_pModelList.end(); ++modelListIter)
	{
		delete *(modelListIter);
	}


}

void VBSPRenderer::Cull(VCamera* in_pCamera, VMultipassDrawList& in_DrawList)
{
	m_pDrawList = &in_DrawList;

	//show this cell
	Show();

	//traversal list to set each connected cell to be  visible
	std::list<IVCell*>::iterator begin = m_CellList.begin();

	for(begin; begin != m_CellList.end(); ++begin)
	{
		(*begin)->Cull(in_pCamera, in_DrawList);
	}
}

void VBSPRenderer::Show()
{
	if(!m_bModelAdded)
	{
		std::list<VModel*>::iterator begin = m_pModelList.begin();

		for(begin; begin != m_pModelList.end(); ++begin)
		{
			m_pDrawList->Add(*(*begin));
		}

		m_bModelAdded = true;
	}

}

void VBSPRenderer::Hide(VMultipassDrawList& in_DrawList)
{
	if(m_bModelAdded)
	{
		//m_pDrawList->Remove(*m_pModel);
		m_bModelAdded = false;
	}
}

void VBSPRenderer::BuildCell()
{

	cell.ResizeVertexBuffer(m_Level.m_iNumVertices);
	cell.SetGeometryType(VMeshDescription::GeometryType::TriangleFan);

	for (int i=0; i < m_Level.m_iNumVertices; i++)
	{
		cell.GetVertexBuffer()[i].position.x = m_Level.m_pVertices[i].Vertex.x;
		cell.GetVertexBuffer()[i].position.y = m_Level.m_pVertices[i].Vertex.y;
		cell.GetVertexBuffer()[i].position.z = m_Level.m_pVertices[i].Vertex.z;
		//cell.GetVertexBuffer()[i].texCoords.u = m_Level.m_pVertices[i].TextureCoord.u;
		//cell.GetVertexBuffer()[i].texCoords.v = m_Level.m_pVertices[i].TextureCoord.v;
		cell.GetVertexBuffer()[i].texCoords.u  = m_Level.m_pVertices[i].LightmapCoord.u;
		cell.GetVertexBuffer()[i].texCoords.v  = m_Level.m_pVertices[i].LightmapCoord.v;
	}
}

void VBSPRenderer::BuildModelList()
{
	VMeshDescription meshD = 
		BuildMeshDescription<VTexturedVertex>(
		*m_pDevice,
		cell.GetVertexBuffer().GetDataAddress(),
		m_Level.m_iNumVertices
		);

	VMaterialDescription matDescs;

	MatrixPtr translate;

	translate.Assign(new VMatrix44f());
	Identity(*translate);

	math::SetTranslate(*translate, 0.0f,0.0f, 0.0f);



	for(int i = 0; i<m_Level.m_iNumFaces; i++)
	{
		vuint count = 0;
		utils::VQ3BspImporter::BSPFace* face = &m_Level.m_pFaces[i];

		cell.ResizeIndexBuffer(face->iNumVertices);
		
		for(vint32 j = face->iVertexIndexStart;
			j < face->iNumVertices + face->iVertexIndexStart;
			j++
			)
		{
			cell.GetIndexBuffer()[count] = (vuint)j;
			count++;
		}

		// assign our vertex buffer to this handle //TODO: fix, unclean
		VMeshDescription md = meshD;

		const vuint cnIndexBufferSize = face->iNumVertices * sizeof(vuint);
		VByteBuffer indexBuffer(new vbyte[cnIndexBufferSize], cnIndexBufferSize);
		memcpy(indexBuffer.GetDataAddress()
			, cell.GetIndexBuffer().GetDataAddress(),
			cnIndexBufferSize
			);

		// add indices
		md.triangleIndices = VMeshDescription::ByteDataRef
			(
				m_pDevice->CreateBuffer
				(
					IVDevice::VertexBuffer,
					&indexBuffer,
					VByteBuffer::DropData
				),
				0,
				face->iNumVertices,
				1
			);
		
			md.geometryType = cell.GetGeometryType();
            
			IVDevice::MeshHandle handle = m_pDevice->CreateMesh(
				md,
				*m_MaterialList[face->iTextureID]
				);


			VModel* model = new VModel(handle, translate);

			IVDevice::MeshHandle handle2 = m_pDevice->CreateMesh(
				md,
				*m_LightMaterialList[face->iLightmapID]
				);

			VModel* model2 = new VModel(handle2, translate);

			// first lightmaps
			m_pModelList.push_back(model2);

			// now the textures with blending
			m_pModelList.push_back(model);
			
	}
}

void VBSPRenderer::GetFaceElements()
{
	for(int i = 0; i < m_Level.m_iNumFaces; i++)
	{
		m_iNumFaceElements += m_Level.m_pFaces[i].iNumVertices;
	}
}

void VBSPRenderer::CreateTextures()
{
	vout << "loading textures:" << vendl;

	for(int i = 0; i < m_Level.m_iNumTextures; i++)
	{

		VMaterialDescription* mat = new VMaterialDescription;
		
		std::string sBaseTextureName;
		std::string sTextureName(m_Level.m_pTextures[i].sTextureName);
	
		if(sTextureName =="noshader")
		{
			vout << "warning: noshader found" << vendl;
			delete mat;
		
		}
		else
		{
			sTextureName.insert(0,"/data/");
			sBaseTextureName = sTextureName;

			vbool bIsAdded = false;

			try
			{
				sTextureName.append(".jpg");

				vout << "using texture: " << sTextureName << vendl;

				*mat = BuildTextureMaterial(
					m_pDevice, sTextureName.c_str());

				mat->destBlendFactor = VMaterialDescription::BlendSourceColor;
				mat->sourceBlendFactor = VMaterialDescription::BlendZero;
				mat->enableBlending = true;
			}
			
			catch(VException e)
			{
				try
				{
					sBaseTextureName.append(".tga");
					
					vout << "using texture: " << sBaseTextureName << vendl;

					*mat = BuildTextureMaterial(
					m_pDevice, sBaseTextureName.c_str());

					mat->destBlendFactor = VMaterialDescription::BlendSourceColor;
					mat->sourceBlendFactor = VMaterialDescription::BlendZero;
					mat->enableBlending = true;
				}
				catch(VException e2)
				{
					mat->destBlendFactor = VMaterialDescription::BlendSourceColor;
					mat->sourceBlendFactor = VMaterialDescription::BlendZero;
					mat->enableBlending = true;

					m_MaterialList.push_back(mat);
					bIsAdded = true;
					vout << "warning: skipping texture" << sTextureName << "/tga" << vendl;
				}

			}
			if(!bIsAdded)
			{
				mat->destBlendFactor = VMaterialDescription::BlendSourceColor;
				mat->sourceBlendFactor = VMaterialDescription::BlendZero;
				mat->enableBlending = true;

				m_MaterialList.push_back(mat);
			}
		}
	}

	vout << "loading texture list done..." << vendl;
}

void VBSPRenderer::CreateLightmaps()
{
	for(int i = 0; i<m_Level.m_iNumLightmaps; i++)
	{
	
		VMaterialDescription* mat = new VMaterialDescription();
		VMaterialDescription::TextureRef* texRef = new VMaterialDescription::TextureRef();
		
		//FIX: who deletes this?
		VBuffer<vbyte>* buffer = new VBuffer<vbyte>(m_Level.m_pLightmaps[i].LightmapData, 49152);

		IVDevice::BufferHandle hTextureBuffer = m_pDevice->CreateBuffer(
		IVDevice::Texture,
		buffer,
		IVDevice::Buffer::DropData
		);

		texRef->nWidth = 128;
		texRef->nHeight = 128;
		texRef->hData = hTextureBuffer;

		mat->AddTexture(texRef);
	
		mat->sourceBlendFactor = VMaterialDescription::BlendDestColor;
		mat->destBlendFactor =  VMaterialDescription::BlendSourceColor;

		mat->depthWriteMask = VMaterialDescription::DepthReadOnly;
		

		m_LightMaterialList.push_back(mat);
	}
}


//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------



#include <v3dLib/Graphics/Importer/3DS/VImported3DS.h>

#include <v3d/Core/VObjectRegistry.h>
#include <v3d/vfs/IVTempDataProvider.h>
#include <v3d/VFS/IVFileSystem.h>
#include <v3d/Resource.h>
#include <v3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <V3d/Graphics/IVDevice.h>
#include <sstream>
#include "lib3ds/mesh.h"
#include "lib3ds/material.h"

#include <V3dLib/Graphics/Importer/Base/VImportedBufferDescription.h>
#include <V3dLib/Graphics/Importer/Base/VImportedFaceDescription.h>

#include <V3d/Core/MemManager.h>

using namespace v3d::resource;
using namespace v3d::graphics;

#undef CreateFile //windows defines sucks..
//-----------------------------------------------------------------------------
namespace v3d{
namespace utils{
//-----------------------------------------------------------------------------
VImported3DS::VImported3DS()
{
	m_iNumFaces = 0;
	m_iNumMaterials = 0;
	m_iNumVertices = 0;
	m_nTexCoords = 0;
	m_sMeshResourceName = "";
}

VImported3DS::~VImported3DS()
{
	BufferDescriptionList::iterator i = m_BufferDescriptionList.begin();

	for(; i != m_BufferDescriptionList.end(); ++i)
	{
		delete (*i);
	}
}

vbool VImported3DS::LoadFile(VStringParam in_sFilename)
{
	CreateMeshResourceName(in_sFilename);
	
	/**
	 * create a tempory file on disk because we need to include
	 * the vfs to handle files
	 */

	vfs::IVFileSystem& fileSys = *QueryObject<vfs::IVFileSystem>("vfs.fs");

	// open file
	vfs::IVFileSystem::FileStreamPtr fileStream = 
		fileSys.OpenFile(in_sFilename, vfs::VReadAccess);
	
	vfs::IVTempDataProvider* pTempManager =
		QueryObject<vfs::IVTempDataProvider>("tempfile.service");

	VStringParam theFile = pTempManager->CreateFile(fileStream.Get());
		
	m_p3DSFile = lib3ds_file_load(theFile);

	if(!m_p3DSFile)
		return false;

	if(LoadModel())
	{
		lib3ds_file_free(m_p3DSFile);
		return true;
	}
	else
		return false;
}

vbool VImported3DS::LoadModel()
{
	Lib3dsNode* pNode = m_p3DSFile->nodes;

	for (; pNode != 0; pNode = pNode->next)
	{
		 if(LoadNode(pNode) == false)
			return false;
	}
	
	m_MaterialContainer.CreateResources();

	return true;
}

vbool VImported3DS::CopyBuffers(Lib3dsMesh* in_pMesh, ArrayBuffer* in_pArrayBuffer)
{
	if(!in_pArrayBuffer)
	{
		V3D_THROW(VException, "invalid arrayBuffer in method call");
		return false;
	}

	in_pArrayBuffer->pVertexBuffer = new vfloat32[in_pMesh->points * 3];
	in_pArrayBuffer->pIndexBuffer = new vuint[in_pMesh->faces * 3];
	in_pArrayBuffer->pTextureCoordBuffer = 0;
	
	if(in_pMesh->texels)
	{
		in_pArrayBuffer->pTextureCoordBuffer = new vfloat32[in_pMesh->texels *2];
		in_pArrayBuffer->nTexelCount = in_pMesh->texels;
	}

	//copy whole vertex buffer into our own
	for(vuint i = 0; i< in_pMesh->points; i++)
	{
		in_pArrayBuffer->pVertexBuffer[i*3]  = in_pMesh->pointL[i].pos[0];
		in_pArrayBuffer->pVertexBuffer[i*3+1] = in_pMesh->pointL[i].pos[1];
		in_pArrayBuffer->pVertexBuffer[i*3+2] = in_pMesh->pointL[i].pos[2];
	}

	in_pArrayBuffer->nVertexCount = in_pMesh->points;

	//copy texture uv coordinates into a buffer
	for(vuint i = 0; i < in_pMesh->texels; i++)
	{
		in_pArrayBuffer->pTextureCoordBuffer[i*2] = in_pMesh->texelL[i][0];
		in_pArrayBuffer->pTextureCoordBuffer[i*2+1] = in_pMesh->texelL[i][1];
	}

	return true;
}

vbool VImported3DS::LoadNode(Lib3dsNode* in_pNode)
{
	vuint nIndexCount = 0;

	//if we have an object node check if it's real data or just a dummy
	if (in_pNode->type == LIB3DS_OBJECT_NODE)
	{
		if (strcmp(in_pNode->name,"$$$DUMMY") == 0)
			return true;
	}

	if (!in_pNode->user.d)
	{
		Lib3dsMesh *mesh = lib3ds_file_mesh_by_name(m_p3DSFile, in_pNode->name);
		
		//if not found skip
		if (!mesh)
            return true;

		ArrayBuffer buffer;

		if(!CopyBuffers(mesh, &buffer))
			return false;

		for (vuint p = 0; p < mesh->faces; ++p)
		{
			Lib3dsFace* f = &mesh->faceL[p];
            Lib3dsMaterial* mat=0;

			m_iNumFaces++;

			if (f->material[0])
				mat=lib3ds_file_material_by_name(m_p3DSFile, f->material);
			
			if (mat)
			{
				std::string sMaterialName(mat->name);

				if(sMaterialName.length())
				{
					if(!m_MaterialContainer.FindMaterialByName(
						sMaterialName.c_str()))
					{
						VImportedMaterialDescription* pMat =
							new VImportedMaterialDescription(
							sMaterialName.c_str(),
							mat->texture1_map.name);

						pMat->SetColorAmbient(graphics::VColor4f(
							mat->ambient[0],
							mat->ambient[1],
							mat->ambient[2],
							mat->ambient[3]));

						pMat->SetColorDiffuse(graphics::VColor4f(
							mat->diffuse[0],
							mat->diffuse[1],
							mat->diffuse[2],
							mat->diffuse[3]
							));

						pMat->SetColorSpecular(graphics::VColor4f(
							mat->specular[0],
							mat->specular[1],
							mat->specular[2],
							mat->specular[3]
							));
						
						pMat->SetTransparency(mat->transparency);

						m_MaterialContainer.Add(pMat);
					}

					std::string name = m_sMeshResourceName;
					name.append("/");
					name.append(mesh->name);

					VImportedFaceDescription* pFace = new VImportedFaceDescription
						(
						name.c_str(),
						p,
						nIndexCount,
						m_MaterialContainer.GetMaterialByName(
						sMaterialName.c_str()));

					m_FaceContainer.Add(pFace);
				}
				m_iNumMaterials++;
			}

			else
			{
				std::string name = m_sMeshResourceName;
				name.append("/");
				name.append(mesh->name);

				VImportedFaceDescription* pFace = new VImportedFaceDescription
					(name.c_str(),
					p,
					nIndexCount,
					m_MaterialContainer.GetMaterialByName("default")//load the default material
					);
				m_FaceContainer.Add(pFace);
			}

			for (vint i = 0; i < 3; ++i)
			{
				//write indices to our buffer
				buffer.pIndexBuffer[nIndexCount] = f->points[i];
				nIndexCount++;
			}
		}

		VImportedBufferDescription* pBufferDescription = new VImportedBufferDescription
			(
			mesh->points,
			mesh->faces*3,
			mesh->texels);

		m_BufferDescriptionList.push_back(pBufferDescription);
		
		if(buffer.pVertexBuffer)
			pBufferDescription->SetVertexArray(buffer.pVertexBuffer);
		if(buffer.pTextureCoordBuffer)
			pBufferDescription->SetTexCoordArray1(buffer.pTextureCoordBuffer);
		if(buffer.pIndexBuffer)
			pBufferDescription->SetIndexArray(buffer.pIndexBuffer);

		std::string meshname = mesh->name;

		CreateMeshBufferResource(meshname.c_str(), pBufferDescription);
		m_FaceContainer.CreateFaceResources(pBufferDescription);
	}

	return true;
}

void VImported3DS::CreateMeshResourceName(VStringParam in_sName)
{
	//m_sMeshResourceName += "/models";
	m_sMeshResourceName += in_sName;
}

VStringRetVal VImported3DS::GetMeshResourceName()
{
	return m_sMeshResourceName.c_str();
}

void VImported3DS::CreateMeshBufferResource(VStringParam in_sMeshname,
											VImportedBufferDescription* in_BufferInfo)
{
	resource::VResourceManagerPtr pResourceManager;
	std::string meshName = CreateMeshPartName(in_sMeshname);
	
	resource::VResourceId resID = pResourceManager->CreateResource(meshName.c_str());

	in_BufferInfo->CreateBuffer();
	
	if(in_BufferInfo->GetVertexCount())
		resID->AddData(in_BufferInfo->GetVertexBuffer());
	
	if(in_BufferInfo->GetIndicesCount())
		resID->AddSubResource("indices")->
			AddData(in_BufferInfo->GetIndexBuffer());

	if(in_BufferInfo->GetTexCoordCount1())
		resID->AddSubResource("texcoords")->
		AddData(in_BufferInfo->GetTexCoordBuffer1());
}

VStringRetVal VImported3DS::CreateMeshPartName(VStringParam in_sMeshPartName)
{
	std::string meshName;
	meshName.append(m_sMeshResourceName);
	meshName.append("/");
	meshName.append(in_sMeshPartName);

	return meshName.c_str();
}

vbool VImported3DS::CreateModel(graphics::IVDevice* in_pDevice,
							   graphics::VModel* in_pModel,
							   VStringParam in_sFilename)
{
	if(LoadFile(in_sFilename))
	{
		m_FaceContainer.CreateMeshes(in_pDevice, in_pModel);
		return true;
	}
	
	else
		return false;
}

vbool VImported3DS::CreateModel(
							   graphics::VModel* in_pModel,
							   VStringParam in_sFilename)
{
	if(LoadFile((in_sFilename)))
	{
//		m_FaceContainer.CreateMeshes(in_pModel);
   		m_FaceContainer.CreateOptimizedMeshes(in_pModel, in_sFilename);
		return true;
	}

	else
		return false;
	
	

}

//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
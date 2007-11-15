/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Graphics/Importer/Base/VImportedFaceContainer.h>
#include <V3d/Graphics/Importer/Base/VImportedFaceDescription.h>
#include <V3d/Graphics/Importer/Base/VImportedMaterialDescription.h>
#include <V3d/Graphics/Importer/VImporterException.h>
#include <V3d/Graphics/Importer/Base/VImportedBufferDescription.h>
#include <V3d/Graphics/VMeshDescription.h>
#include <V3d/Graphics/VVertexBuffer.h>
#include <V3d/Graphics/Importer/Base/VMaterialMap.h>
//-----------------------------------------------------------------------------
#include <V3d/Graphics/VModel.h>
#include <V3d/Math/VMatrixOps.h>
#include <V3d/Math/TransformationOps.h>
#include <V3d/Math/VVectorOps.h>
#include <map>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace math;

VImportedFaceContainer::VImportedFaceContainer()
{
}

VImportedFaceContainer::~VImportedFaceContainer()
{
	std::vector<VImportedFaceDescription*>::iterator begin = m_FaceList.begin();

	for(; begin != m_FaceList.end(); begin++)
		delete (*begin);
}

vuint VImportedFaceContainer::GetFaceCount()
{
	return static_cast<vuint>(m_FaceList.size());
}

void VImportedFaceContainer::Add(VImportedFaceDescription* in_pFace)
{
	if(in_pFace)
		m_FaceList.push_back(in_pFace);
}

void VImportedFaceContainer::Remove(VImportedFaceDescription* in_pFace)
{
  //	m_FaceList.remove(in_pFace);
}

void VImportedFaceContainer::CreateFaceResources(
	VImportedBufferDescription* in_pBufferDescription)
{
	std::vector<VImportedFaceDescription*>::iterator begin = m_FaceList.begin();

	for(; begin != m_FaceList.end(); begin++)
		(*begin)->CreateResource(in_pBufferDescription);
}

vbool VImportedFaceContainer::IsInMaterialLoadedList(VStringParam in_sName)
{
	MaterialLoadedList::iterator begin = m_MaterialLoadedList.begin();

	for(; begin != m_MaterialLoadedList.end(); begin++)
	{
		std::string theName = (*begin);
		std::string queryName = in_sName;

		if(theName == queryName)
			return true;
	}

	//nothing found
	return false;
}

void VImportedFaceContainer::CreateMeshes(
	graphics::IVDevice* in_pDevice,
	graphics::VModel* in_pModel)
{
	resource::VResourceManagerPtr pResManager;

	graphics::IVDevice::MeshHandle mesh = 0;
	graphics::IVDevice::MaterialHandle material = 0;

	graphics::VModelMesh::MeshPtr meshResourcePtr;
	graphics::VModelMesh::MaterialPtr materialResourcePtr = 0;
	

	std::vector<VImportedFaceDescription*>::iterator begin = m_FaceList.begin();
	
	for(; begin != m_FaceList.end(); begin++)
	{
		mesh = in_pDevice->CreateMesh((*begin)->GetResourceName());

		resource::VResourceId meshId = pResManager->GetResourceByName((*begin)->
			GetResourceName());
		
		meshResourcePtr = meshId->GetData<graphics::IVMesh>();
		
		if((*begin)->GetMaterial())
		{
			VString name = (*begin)->GetMaterial()->GetResourceName();
			if(!IsInMaterialLoadedList(name.AsCString()))
			{
			
				material = in_pDevice->CreateMaterial(name.AsCString());
				//save some time cos its usual next face uses same material
				m_MaterialLoadedList.push_front(std::string(name.AsCString()));
			
				//resolve resource id
				resource::VResourceId matId = pResManager->GetResourceByName(
				(*begin)->GetMaterial()->GetResourceName());

				//cast to resource pointer
				materialResourcePtr = matId->GetData<graphics::IVMaterial>();
			}
		}

		//construct default matrix
		//TODO: take it from the 3ds file

		graphics::VModelMesh::MatrixPtr matrixPtr;
		//matrixPtr.Assign(&math::IdentityMatrix());
		//Identity(matrixPtr);
		
		graphics::VModelMesh model(meshResourcePtr,
			materialResourcePtr, matrixPtr);

		in_pModel->Add(model);
	}
}

void VImportedFaceContainer::CreateMeshes(graphics::VModel* in_pModel)
{
	resource::VResourceManagerPtr pResManager;
	graphics::VModelMesh::MeshPtr meshResourcePtr;
	graphics::VModelMesh::MaterialPtr materialResourcePtr = 0;
	

	std::vector<VImportedFaceDescription*>::iterator begin = m_FaceList.begin();
	
	for(; begin != m_FaceList.end(); begin++)
	{
		resource::VResourceId meshId = pResManager->GetResourceByName((*begin)->
			GetResourceName());
		
		meshResourcePtr = meshId->GetData<graphics::IVMesh>();
		
		if((*begin)->GetMaterial())
		{
			VString name = (*begin)->GetMaterial()->GetResourceName();
			if(!IsInMaterialLoadedList(name.AsCString()))
			{
			
				//save some time cos its usual next face uses same material
				m_MaterialLoadedList.push_front(name.AsCString());
			
				//resolve resource id
				resource::VResourceId matId = pResManager->GetResourceByName(
				(*begin)->GetMaterial()->GetResourceName());

				//cast to resource pointer
				materialResourcePtr = matId->GetData<graphics::IVMaterial>();
			}
		}

		//construct default matrix
		//TODO: take it from the 3ds file

		graphics::VModelMesh::MatrixPtr matrixPtr;
		//matrixPtr.Assign(&math::IdentityMatrix());
		//Identity(matrixPtr);
		
		graphics::VModelMesh model(meshResourcePtr,
			materialResourcePtr, matrixPtr);

		in_pModel->Add(model);
	}
}

void VImportedFaceContainer::CreateOptimizedMeshes(
	graphics::VModel* in_pModel, VStringParam in_strResource
	)
{
	VMaterialMap mymap;
	resource::VResourceManagerPtr pResManager;
	graphics::VModelMesh::MeshPtr meshResourcePtr;
	graphics::VModelMesh::MaterialPtr materialResourcePtr = 0;
	FaceList::const_iterator begin = m_FaceList.begin();
	FaceList::const_iterator itEnd = m_FaceList.end();

	for(; begin != itEnd; begin++)
	{
		if((*begin)->GetMaterial())
			mymap.AddMaterialFacePair((*begin)->GetMaterial(), (*begin)->GetFaceIndexStart());
	}

	VMaterialMap::MaterialList::iterator i = mymap.GetMaterialFaceMap().begin();
	int nFaceCount=0;

	V3D_ASSERT(m_FaceList.size() != 0);
	if(!m_FaceList.size())
		return;

	for(; i != mymap.GetMaterialFaceMap().end(); ++i)
	{
		//cast to resource pointer
		materialResourcePtr = pResManager->GetResourceByName((*i).key->GetResourceName())->GetData<graphics::IVMaterial>();

		VMaterialMap::FaceIDList::iterator begin = mymap.GetFaceList((*i).key)->begin();
		vuint32* indexBuffer = new vuint32[(*i).listForKey->size() * 3];
		vuint32 nCount = 0;
		VertexPool vertexPool;

		for(; begin != mymap.GetFaceList((*i).key)->end(); ++begin)
		{
			vuint index = m_FaceList[((*begin) / 3 )]->GetFaceIndexStart();
			vuint* indexArray = m_FaceList[((*begin) / 3 )]->GetBufferDescription()->GetIndexBufferArray();
			const vfloat32* vertexArray = reinterpret_cast<const vfloat32*>(m_FaceList[((*begin) / 3)]->GetBufferDescription()->GetVertexBuffer()->GetBufferAddress());
			
			vuint a = indexArray[index];
			vuint b = indexArray[index +1];
			vuint c = indexArray[index +2];

			/*if( a > m_FaceList.size() )
			  V3D_THROW(graphics::VImporterException, "index buffer invalid");
			if( b > m_FaceList.size() )
			  V3D_THROW(graphics::VImporterException, "index buffer invalid");
			if( c > m_FaceList.size() )
			  V3D_THROW(graphics::VImporterException, "index buffer invalid");*/

			VVector3f v1(vertexArray[a*3], vertexArray[a*3+1], vertexArray[a*3+2]);
			VVector3f v2(vertexArray[b*3], vertexArray[b*3+1], vertexArray[b*3+2]);
			VVector3f v3(vertexArray[c*3], vertexArray[c*3+1], vertexArray[c*3+2]);

			vuint newIndexA = vertexPool.GetIndex(v1);
			vuint newIndexB = vertexPool.GetIndex(v2);
			vuint newIndexC = vertexPool.GetIndex(v3);

			indexBuffer[nCount]   = newIndexA;
			indexBuffer[nCount+1] = newIndexB; 
			indexBuffer[nCount+2] = newIndexC;
			nCount +=3;
		}
		vfloat32* pVertexBuffer = vertexPool.CreateVertexBuffer();
		vfloat32* pNormalBuffer = vertexPool.CreateNormalBuffer(indexBuffer, nCount);
		//vfloat32* pNormalBuffer = vertexPool.CreateNormalBuffer(indexBuffer, vertexPool.GetVertexCount());

		std::stringstream ss;
		std::string name = in_strResource;
		name.append("/face");
        ss << nFaceCount;
		name.append(ss.str());
		nFaceCount++;
		std::string sIndicesName;
		sIndicesName.append(name);
		sIndicesName.append("/indices");
		std::string sNormalName;
		sNormalName.append(name);
		sNormalName.append("/normals");
		
		resource::VResourceId meshResource = pResManager->CreateResource(name.c_str());
		graphics::VMeshDescription* meshDescription = new graphics::VMeshDescription();

		graphics::VVertexFormat* pIndexBufferFormat = new graphics::VVertexFormat(
			graphics::VVertexFormat::Indices,
			0,
			nCount
			);

		pIndexBufferFormat->SetIndexFormat(
			graphics::VDataFormat(
			0,
			nCount,
			0));

		graphics::VVertexBuffer* indexBufferHandle = new graphics::VVertexBuffer(
			indexBuffer,
			nCount,
			*pIndexBufferFormat);

		graphics::VVertexFormat vertexBufferFormat(
		  graphics::VVertexFormat::Coordinates,
		  vertexPool.GetVertexCount(),
		  0);

		graphics::VVertexBuffer* pBuffer = new graphics::VVertexBuffer(
		  pVertexBuffer,
		  vertexPool.GetVertexCount() * 3,
		  vertexBufferFormat);
		
		graphics::VVertexFormat normalBufferFormat(
		  graphics::VVertexFormat::Normals,
		  vertexPool.GetVertexCount(),
		  0);

		graphics::VVertexBuffer* pNormalBufferHandle = new graphics::VVertexBuffer(
		  pNormalBuffer,
		  vertexPool.GetVertexCount() * 3,
		  normalBufferFormat);


		meshResource->AddSubResource("indices")->AddData(indexBufferHandle);
		meshResource->AddSubResource("normals")->AddData(pNormalBufferHandle);
		meshResource->AddData(pBuffer);
		meshDescription->SetGeometryType(graphics::VMeshDescription::Triangles);
		meshDescription->SetCoordinateResource(meshResource->GetQualifiedName());
		meshDescription->SetCoordinateFormat(graphics::VDataFormat(0, vertexPool.GetVertexCount(), 0));
		meshDescription->SetIndexResource(sIndicesName.c_str());
		meshDescription->SetIndexFormat(graphics::VDataFormat(0,nCount ,0));
		//meshDescription->SetTexCoordResource(0, m_FaceList.front()->GetMeshDescription()->GetTexCoordResource(0));
		//meshDescription->SetTexCoordFormat(0, m_FaceList.front()->GetMeshDescription()->GetTexCoordFormat(0));
		meshDescription->SetNormalResource(sNormalName.c_str());
		meshDescription->SetNormalFormat(graphics::VDataFormat(0, vertexPool.GetVertexCount() * 3, 0));
		meshResource->AddData(meshDescription);

		meshResourcePtr = meshResource->GetData<graphics::IVMesh>();

		graphics::VModelMesh::MatrixPtr matrixPtr;
		VMatrix44f* pMatrix = new VMatrix44f();
		Identity(*pMatrix);
		matrixPtr.Assign(pMatrix);
		graphics::VModelMesh model(meshResourcePtr,	materialResourcePtr, matrixPtr);

		in_pModel->Add(model);
	}
}

vint VImportedFaceContainer::VertexPool::GetIndex(const math::VVector3f &in_Vector)
{
  /*VertexPool::VertexList::const_iterator it = m_VertexPool.begin();
  VertexPool::VertexList::const_iterator itEnd = m_VertexPool.end();
  vuint index = 0;
  for( ; it != itEnd; ++it)
  {
	gmtl::Vec3f a;
	a.set((*it)[0], (*it)[1], (*it)[2]);
	gmtl::Vec3f b;
	b.set(in_Vector[0], in_Vector[1], in_Vector[2]);
	if ( gmtl::isEqual( a, b, 0.0001f ) )
	{
	  return index;
	}
	else
	{
	  index++;
	}
  }*/

  m_VertexPool.push_back(in_Vector);
  
  return (static_cast<vint>(m_VertexPool.size() ) - 1);
}

vfloat32* VImportedFaceContainer::VertexPool::CreateVertexBuffer()
{
  vfloat32* pBuffer = new vfloat32[m_VertexPool.size() * 3];

  for(vuint i = 0; i < m_VertexPool.size(); i++)
  {
	pBuffer[i*3] = m_VertexPool[i][0];
	pBuffer[i*3+1] = m_VertexPool[i][1];
	pBuffer[i*3+2] = m_VertexPool[i][2];
  }

  return pBuffer;
}

vuint VImportedFaceContainer::VertexPool::GetVertexCount()
{
  return static_cast<vuint>(m_VertexPool.size());
}

vfloat32* VImportedFaceContainer::VertexPool::CreateNormalBuffer(
  const vuint32* in_pIndexBuffer, const vuint in_IndexSize)
{
  vfloat32* pBuffer = new vfloat32[m_VertexPool.size() * 3];
  //set all normals to zero
  const vuint sizeVertexPool = static_cast<vuint>(m_VertexPool.size());
  for(vuint i = 0; i < sizeVertexPool * 3; i++)
	pBuffer[i] = 0;
  //calculate face normals and add to normal buffer
  for(vuint i = 0; i < in_IndexSize / 3; i++)
  {
	  math::VVector3f v1,v2,v3, normal;
	  vuint a = in_pIndexBuffer[i*3];
	  vuint b = in_pIndexBuffer[i*3+1];
	  vuint c = in_pIndexBuffer[i*3+2];

	  v1 = m_VertexPool[a];
	  v2 = m_VertexPool[b];
	  v3 = m_VertexPool[c];

	  math::VVector3f x = v3 - v1;
	  math::VVector3f y = v3 - v2;

	  normal = math::Cross(x,y);
	  math::Normalize(normal);		
	  pBuffer[a*3] += normal[0];
	  pBuffer[a*3+1] += normal[1];
	  pBuffer[a*3+2] += normal[2];

	  pBuffer[b*3] += normal[0];
	  pBuffer[b*3+1] += normal[1];
	  pBuffer[b*3+2] += normal[2];

	  pBuffer[c*3] += normal[0];
	  pBuffer[c*3+1] += normal[1];
	  pBuffer[c*3+2] += normal[2];
  }
  //normalize all average normals in buffer
  for(vuint i = 0; i < sizeVertexPool; i++)
  {
	math::VVector3f a;
	a[0] = pBuffer[i*3];
	a[1] = pBuffer[i*3+1];
	a[2] = pBuffer[i*3+2];
	math::Normalize(a);
    pBuffer[i*3] = a[0];
    pBuffer[i*3+1] = a[1];
    pBuffer[i*3+2] = a[2];
  }
  
  return pBuffer;
}
//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------


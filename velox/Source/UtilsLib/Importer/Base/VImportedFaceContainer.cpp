#include <v3dLib/Graphics/Importer/Base/VImportedFaceContainer.h>
#include <v3dLib/Graphics/Importer/Base/VImportedFaceDescription.h>
#include <v3dLib/Graphics/Importer/Base/VImportedMaterialDescription.h>
#include <V3dLib/Graphics/Importer/VImporterException.h>
#include <V3dLib/Graphics/Importer/Base/VImportedBufferDescription.h>

#include <V3d/Graphics/VMeshDescription.h>
#include <v3d/Graphics/VVertexBuffer.h>

#include <v3dLib/Graphics/Importer/Base/VMaterialMap.h>
//-----------------------------------------------------------------------------
#include <v3d/Graphics/VModel.h>
#include <V3d/Math/VMatrixOps.h>
#include <v3d/Math/TransformationOps.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;

VImportedFaceContainer::VImportedFaceContainer()
{
}

VImportedFaceContainer::~VImportedFaceContainer()
{
	std::list<VImportedFaceDescription*>::iterator begin = m_FaceList.begin();

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
	m_FaceList.remove(in_pFace);
}

void VImportedFaceContainer::CreateFaceResources(
	VImportedBufferDescription* in_pBufferDescription)
{
	std::list<VImportedFaceDescription*>::iterator begin = m_FaceList.begin();

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
	

	std::list<VImportedFaceDescription*>::iterator begin = m_FaceList.begin();
	
	for(; begin != m_FaceList.end(); begin++)
	{
		mesh = in_pDevice->CreateMesh((*begin)->GetResourceName());

		resource::VResourceId meshId = pResManager->GetResourceByName((*begin)->
			GetResourceName());
		
		meshResourcePtr = meshId->GetData<graphics::IVMesh>();
		
		if((*begin)->GetMaterial())
		{
			std::string name = (*begin)->GetMaterial()->GetResourceName();
			if(!IsInMaterialLoadedList(name.c_str()))
			{
			
				material = in_pDevice->CreateMaterial(name.c_str());
				//save some time cos its usual next face uses same material
				m_MaterialLoadedList.push_front(name);
			
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

	graphics::IVDevice::MeshHandle mesh = 0;
	graphics::IVDevice::MaterialHandle material = 0;

	graphics::VModelMesh::MeshPtr meshResourcePtr;
	graphics::VModelMesh::MaterialPtr materialResourcePtr = 0;
	

	std::list<VImportedFaceDescription*>::iterator begin = m_FaceList.begin();
	
	for(; begin != m_FaceList.end(); begin++)
	{
		resource::VResourceId meshId = pResManager->GetResourceByName((*begin)->
			GetResourceName());
		
		meshResourcePtr = meshId->GetData<graphics::IVMesh>();
		
		if((*begin)->GetMaterial())
		{
			std::string name = (*begin)->GetMaterial()->GetResourceName();
			if(!IsInMaterialLoadedList(name.c_str()))
			{
			
				//save some time cos its usual next face uses same material
				m_MaterialLoadedList.push_front(name);
			
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

void VImportedFaceContainer::CreateOptimizedMeshes(graphics::VModel* in_pModel)
{
	VMaterialMap mymap;

	resource::VResourceManagerPtr pResManager;
	graphics::VModelMesh::MeshPtr meshResourcePtr;
	graphics::VModelMesh::MaterialPtr materialResourcePtr = 0;

	std::list<VImportedFaceDescription*>::iterator begin = m_FaceList.begin();

	for(; begin != m_FaceList.end(); begin++)
	{
		if((*begin)->GetMaterial())
			mymap.AddMaterialFacePair((*begin)->GetMaterial(), (*begin)->GetFaceIndexStart());
	}

	VMaterialMap::MaterialList::iterator i = mymap.GetMaterialFaceMap().begin();
	int nFaceCount=0;

	V3D_ASSERT(m_FaceList.size());
	if(!m_FaceList.size())
		return;
    		
	vuint* indexArray = m_FaceList.front()->GetBufferDescription()->GetIndexBufferArray();
	
	for(; i != mymap.GetMaterialFaceMap().end(); ++i)
	{
		//cast to resource pointer
		materialResourcePtr = pResManager->GetResourceByName((*i).key->GetResourceName())->GetData<graphics::IVMaterial>();

		VMaterialMap::FaceIDList::iterator begin;
		begin = mymap.GetFaceList((*i).key)->begin();

		vuint n = m_FaceList.size();

		vuint32* indexBuffer = new vuint32[(*i).listForKey->size() * 3];
		vuint32 nCount = 0;

		for(; begin != mymap.GetFaceList((*i).key)->end(); ++begin)
		{
			if(indexArray[(*begin)] < 0)
			{
				std::stringstream ss;
				ss << "index: " <<(*begin) << " array value: "<< indexArray[(*begin)] << " with valid size of " << n*3;
				V3D_THROW(graphics::VImporterException, ss.str().c_str());
			}
				
			if(indexArray[(*begin)+1] < 0)
			{
				std::stringstream ss;
				ss << "index: " <<(*begin)+1 << " array value: "<< indexArray[(*begin)+1] << " with valid size of " << n*3;
				V3D_THROW(graphics::VImporterException, ss.str().c_str());
			}
				
			if(indexArray[(*begin)+2] < 0)
			{
				std::stringstream ss;
				ss << "index: " <<(*begin)+2 << " array value: "<< indexArray[(*begin)+2] << " with valid size of " << n*3;
				V3D_THROW(graphics::VImporterException, ss.str().c_str());
			}
			
			if(indexArray[(*begin)] > n*3-1)
			{
				std::stringstream ss;
				ss << "index: " <<(*begin) << " array value: "<< indexArray[(*begin)] << " with valid size of " << n*3;
				V3D_THROW(graphics::VImporterException, ss.str().c_str());
			}
			if(indexArray[(*begin)+1] > n*3-1)
			{
				std::stringstream ss;
				ss << "index: " <<(*begin)+1 << " array value: "<< indexArray[(*begin)+1] << " with valid size of " << n*3;
				V3D_THROW(graphics::VImporterException, ss.str().c_str());
			}
				
			if(indexArray[(*begin)+2] > n*3-1)
			{
				std::stringstream ss;
				ss << "index: " <<(*begin) << " array value: "<< indexArray[(*begin)] << " with valid size of " << n*3;
				V3D_THROW(graphics::VImporterException, ss.str().c_str());
			}
			
			indexBuffer[nCount] = indexArray[(*begin)];
			indexBuffer[nCount+1] = indexArray[(*begin)+1];
			indexBuffer[nCount+2] = indexArray[(*begin)+2];

			nCount +=3;
		}

		std::stringstream ss;
		std::string name;
		name.append("/testmodel");
        ss << nFaceCount;
		name.append(ss.str());
		nFaceCount++;
		std::string sIndicesName;
		sIndicesName.append(name);
		sIndicesName.append("/indices");

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

		meshResource->AddSubResource("indices")->AddData(indexBufferHandle);
		meshDescription->SetGeometryType(m_FaceList.front()->GetMeshDescription()->GetGeometryType());
		meshDescription->SetCoordinateResource(m_FaceList.front()->GetMeshDescription()->GetCoordinateResource());
		meshDescription->SetCoordinateFormat(m_FaceList.front()->GetMeshDescription()->GetCoordinateFormat());
		meshDescription->SetIndexResource(sIndicesName.c_str());
		meshDescription->SetIndexFormat(graphics::VDataFormat(0,nCount ,0));
		meshDescription->SetTexCoordResource(0, m_FaceList.front()->GetMeshDescription()->GetTexCoordResource(0));
		meshDescription->SetTexCoordFormat(0, m_FaceList.front()->GetMeshDescription()->GetTexCoordFormat(0));
		meshResource->AddData(meshDescription);

		meshResourcePtr = meshResource->GetData<graphics::IVMesh>();

		graphics::VModelMesh::MatrixPtr matrixPtr;
		graphics::VModelMesh model(meshResourcePtr,	materialResourcePtr, matrixPtr);

		in_pModel->Add(model);
	}
}
//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------

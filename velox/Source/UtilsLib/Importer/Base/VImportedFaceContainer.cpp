#include <v3dLib/Graphics/Importer/Base/VImportedFaceContainer.h>
#include <v3dLib/Graphics/Importer/Base/VImportedFaceDescription.h>
#include <v3dLib/Graphics/Importer/Base/VImportedMaterialDescription.h>
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
		//mesh = in_pDevice->CreateMesh((*begin)->GetResourceName());

		resource::VResourceId meshId = pResManager->GetResourceByName((*begin)->
			GetResourceName());
		
		meshResourcePtr = meshId->GetData<graphics::IVMesh>();
		
		if((*begin)->GetMaterial())
		{
			std::string name = (*begin)->GetMaterial()->GetResourceName();
			if(!IsInMaterialLoadedList(name.c_str()))
			{
			
				//material = in_pDevice->CreateMaterial(name.c_str());
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

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core.h>
#include <V3dLib/Physics/VPhysicUtils.h>
#include <V3d/Resource.h>
#include <V3dLib/Graphics/Generators.h>
#include <V3d/Scene.h>
#include <V3dLib/Graphics/Materials/EffectUtils.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
using namespace v3d::resource;
using namespace v3d::graphics;
using namespace v3d::entity;
using namespace v3d::scene;

//TODO: move away from here
void CreateSphereResource(VStringParam in_sName, vfloat32 in_fScale)
{
	VResourceManagerPtr pResManager;

	VPolarSphereMesh<VTexturedVertex> sphere(10,10);
	sphere.GenerateCoordinates();
	sphere.GenerateTexCoords();
	
	ForEachVertex(sphere.GetVertexBuffer(), 
		ScaleVertex<VTexturedVertex>(in_fScale, in_fScale, in_fScale));

	VResourceId sphereResourceId = pResManager->CreateResource(in_sName);
	VResourceId sphereRes = BuildResource(in_sName, sphere);
}

void CreateTextureEffect(VStringParam in_sTextureFileName,
							VStringParam in_sEffectResourceName,
							VStringParam in_sResourceName)
{
	resource::VResourceManagerPtr pResManager;

	try
	{
		VResourceId res = pResManager->GetResourceByName(in_sEffectResourceName);
	}

	catch(v3d::resource::VResourceNotFoundException)
	{
		VResourceId res = pResManager->CreateResource(in_sEffectResourceName);
		res->AddData(new VFileName(in_sTextureFileName));
	}

	VResourceId res = pResManager->GetResourceByName(in_sResourceName);

	res->AddData(new VEffectDescription(CreateTextureEffectDescription(in_sEffectResourceName)));
}

void CreatePlaneResource(VStringParam in_sResourceName,
										VVector3f in_Normal,
										vfloat32 in_fDistance,
										vfloat32 in_fVisFactor)
{
	VPlaneMesh<VTexturedVertex> plane(
		in_Normal[0],
		in_Normal[1],
		in_Normal[2],
		in_fDistance,
		in_fVisFactor
		);
	plane.GenerateCoordinates();
	plane.GenerateTexCoords();

	VResourceId res = BuildResource(in_sResourceName, plane);
}

void CreateBoxResource(VStringParam in_sResourceName, vfloat32 in_fWidth)
{
	CreateBoxResource(in_sResourceName, VVector3f(in_fWidth, in_fWidth, in_fWidth));
}

void CreateBoxResource(VStringParam in_sResourceName, VVector3f in_Expansion)
{
	VBoxMesh<VTexturedVertex> box(in_Expansion[0], in_Expansion[1], in_Expansion[2]);
	box.GenerateCoordinates();
	box.GenerateTexCoords();

	VResourceId res = BuildResource(in_sResourceName, box);
}

VSharedPtr<entity::VEntity> CreateBoxPhysicObject(
							vfloat32 in_fMasss,
							VVector3f in_Expansion,
							VPhysicManagerPart* in_pPhysicManager,
							VPhysicBody*& pReferencePointer,
							std::string in_sResourceName)
{
	VSharedPtr<VPhysicBoxMassState> pMassState(new VPhysicBoxMassState());
	VSharedPtr<VPhysicGeometryBox> pBoxGeometry(new VPhysicGeometryBox());
	
	pMassState->SetMass(in_fMasss);
	pBoxGeometry->SetLength(in_Expansion[0]);
	pBoxGeometry->SetWidth(in_Expansion[1]);
	pBoxGeometry->SetHeight(in_Expansion[2]);

	//hack!!!
	pBoxGeometry->CreateBox(in_pPhysicManager->GetPhysicWorld()->GetSpace());

	VSharedPtr<VPhysicBody> pPhysicBodyPart(
		in_pPhysicManager->GetPhysicWorld()->CreateBody());

	pReferencePointer = pPhysicBodyPart.Get();
	
	pPhysicBodyPart->AddState(pMassState.Get());
	pPhysicBodyPart->Create(in_pPhysicManager->GetPhysicWorld());
	pPhysicBodyPart->SetCollisionBody(pBoxGeometry.Get());

	VSharedPtr<VEntity> pObjectEntityBox(new entity::VEntity());
	//VRigidBodyPart* pBodyPartBox = new VRigidBodyPart;

	//pObjectEntityBox->AddPart(VRigidBodyPart::GetDefaultId(), SharedPtr(pBodyPartBox));
	pObjectEntityBox->AddPart(pPhysicBodyPart);

	resource::VResourceManagerPtr pResManager;

	VResourceId box = pResManager->GetResourceByName(in_sResourceName.c_str());

	graphics::VModelMesh::MeshPtr meshResourcePtr = 0;
	graphics::VModelMesh::MaterialPtr materialResourcePtr = 0;

	meshResourcePtr = box->GetData<graphics::IVMesh>();
	materialResourcePtr = box->GetData<graphics::IVMaterial>();

	VSharedPtr<scene::VModelPart> pSceneModel(new scene::VModelPart(VModel(VModelMesh(
		meshResourcePtr, materialResourcePtr))));

	pObjectEntityBox->AddPart(pSceneModel);

	return pObjectEntityBox;
}

VEffectDescription CreateTextureEffectDescription(VStringParam in_sResourceName)
{
	// create an effect description for the mesh
	VEffectDescription effect;
	VRenderPass& pass(effect.AddShaderPath().AddRenderPass());

	pass.AddState(DefaultColorState(VColor4f(1, 1, 1, 1)));
	pass.AddState(PolygonModeState(PMFilled, PMFilled));
	pass.AddState(DepthBufferState(DepthOnLess, DepthTestEnabled, DepthWrite));
	pass.AddState(ColorBufferWriteMaskState(true, true, true, true));
	pass.AddState(BlendingState(BlendDisabled, BlendSourceAlpha, BlendOneMinusSourceAlpha));

	// add resource info

	VState textureState = TextureState(in_sResourceName);

	pass.AddState(textureState);

	return effect;
}

VSharedPtr<entity::VEntity> CreateSpherePhysicObject(
	vfloat32 in_fMasss,
	vfloat32 in_fRadius,
	VPhysicManagerPart* in_pPhysicManager,
	VPhysicBody*& pReferencePointer,
	std::string in_sResourceName)
{
	//create a container entity
	VSharedPtr<entity::VEntity> pObjectEntitySphere(new entity::VEntity());
	//physic stuff
	VSharedPtr<VPhysicSphereMassState> pMassState(new VPhysicSphereMassState());
	VSharedPtr<VPhysicGeometrySphere> pSphereGeometry(new VPhysicGeometrySphere());
	//assign values
	pMassState->SetMass(in_fMasss);
	pSphereGeometry->SetSphereRadius(in_fRadius);
	pSphereGeometry->CreateSphere(in_pPhysicManager->GetPhysicWorld()->GetSpace());

	//create the physic part and tell our manager
	VSharedPtr<VPhysicBodyPart> pPhysicBodyPart(
		in_pPhysicManager->GetPhysicWorld()->CreateBody());
	
	//save back a pointer to our body. may be needed later
	pReferencePointer = pPhysicBodyPart.Get();

	pPhysicBodyPart->AddState(pMassState.Get());
	pPhysicBodyPart->Create(in_pPhysicManager->GetPhysicWorld());
	pPhysicBodyPart->SetCollisionBody(pSphereGeometry.Get());

	//VSharedPtr<VRigidBodyPart> pRidgidBodyPart(new VRigidBodyPart());
	
	//pObjectEntitySphere->AddPart(pRidgidBodyPart);
	pObjectEntitySphere->AddPart(pPhysicBodyPart);

	//pObjectEntitySphere->Activate();

	//create the resource and request it for building
	resource::VResourceManagerPtr pResManager;
	VResourceId sphere = pResManager->GetResourceByName(in_sResourceName.c_str());

	/*graphics::VModelMesh::MeshPtr meshResourcePtrSphere = 0;
	graphics::VModelMesh::MaterialPtr materialResourcePtrSphere = 0;
    
	meshResourcePtrSphere = sphere->GetData<graphics::IVMesh>();
	materialResourcePtrSphere = sphere->GetData<graphics::IVMaterial>();*/

	if(in_sResourceName != "")
	{
		VSharedPtr<scene::VModelPart> pSceneModelSphere(
			new scene::VModelPart(*sphere->GetData<VModel>()));
		pObjectEntitySphere->AddPart(pSceneModelSphere);
	}


	//in_pParentEntity->AddChild(pObjectEntitySphere);

	//pSceneModelSphere->Activate();

	return pObjectEntitySphere;
}

void CreatePlanePhysicObject(
	VVector3f in_Normal,
	vfloat32 in_fDistance,
	entity::VEntity* in_pParentEntity,
	VPhysicManagerPart* in_pPhysicManager,
	std::string in_sResourceName)
{
	resource::VResourceManagerPtr pResMan;
	entity::VEntity* pObjectEntity = new entity::VEntity();
	VRigidBodyPart* pBodyPart = new VRigidBodyPart;

	VPhysicGeometryPlane plane;
	plane.SetPlane(graphics::VVertex3f(in_Normal[0], in_Normal[1], in_Normal[2]),in_fDistance);
	plane.CreatePlane(in_pPhysicManager->GetPhysicWorld()->GetSpace());

	VResourceId planeRes = pResMan->GetResourceByName(in_sResourceName.c_str());

	graphics::VModelMesh::MeshPtr meshResourcePtr = 0;
	graphics::VModelMesh::MaterialPtr materialResourcePtr = 0;

	meshResourcePtr = planeRes->GetData<graphics::IVMesh>();
	materialResourcePtr = planeRes->GetData<graphics::IVMaterial>();

	scene::VModelPart* pSceneModel  = new scene::VModelPart(VModel(VModelMesh(
		meshResourcePtr, materialResourcePtr)));
	pObjectEntity->AddPart(scene::VModelPart::GetDefaultId(),SharedPtr(pSceneModel));
	pObjectEntity->AddPart(VRigidBodyPart::GetDefaultId(), SharedPtr(pBodyPart));
	in_pParentEntity->AddChild(SharedPtr(pObjectEntity));
	pSceneModel->Activate();
}

VSharedPtr<entity::VEntity> CreateSpherePhysicObject(
	vfloat32 in_fMasss,
	vfloat32 in_fRadius,
	VPhysicManagerPart* in_pPhysicManager,
	VPhysicBodyPart*& pReferencePointer,
	VPhysicSpace* in_pSpace,
	std::string in_sResourceName)
{
	//create a container entity
	VSharedPtr<entity::VEntity> pObjectEntitySphere(new entity::VEntity());
	//physic stuff
	VSharedPtr<VPhysicSphereMassState> pMassState(new VPhysicSphereMassState());

	//TODO: insert here new geom types
	VSharedPtr<VPhysicGeometrySphere> pSphereGeometry(new VPhysicGeometrySphere());
	//assign values
	pMassState->SetMass(in_fMasss);
	pSphereGeometry->SetSphereRadius(in_fRadius);
	pSphereGeometry->CreateSphere(in_pSpace);

	//create the physic part and tell our manager
	VSharedPtr<VPhysicBodyPart> pPhysicBodyPart(
		in_pPhysicManager->GetPhysicWorld()->CreateBody());

	//save back a pointer to our body. may be needed later
	pReferencePointer = pPhysicBodyPart.Get();

	pPhysicBodyPart->AddState(pMassState.Get());
	pPhysicBodyPart->Create(in_pPhysicManager->GetPhysicWorld());
	pPhysicBodyPart->SetCollisionBody(pSphereGeometry.Get());

	//pObjectEntitySphere->AddPart(pRidgidBodyPart);
	pObjectEntitySphere->AddPart(pPhysicBodyPart);

	//pObjectEntitySphere->Activate();

	//create the resource and request it for building
	resource::VResourceManagerPtr pResManager;
	VResourceId sphere = pResManager->GetResourceByName(in_sResourceName.c_str());

	if(in_sResourceName != "")
	{
		VSharedPtr<scene::VModelPart> pSceneModelSphere(
			new scene::VModelPart(*sphere->GetData<VModel>()));
		pObjectEntitySphere->AddPart(pSceneModelSphere);
	}

	return pObjectEntitySphere;
}

VSharedPtr<entity::VEntity> CreateBoxPhysicObject(
	vfloat32 in_fMasss,
	VVector3f in_Expansion,
	VPhysicManagerPart* in_pPhysicManager,
	VPhysicBody*& pReferencePointer,
	VPhysicSpace* in_pSpace,
	std::string in_sResourceName)
{
	VSharedPtr<VPhysicBoxMassState> pMassState(new VPhysicBoxMassState());
	VSharedPtr<VPhysicGeometryBox> pBoxGeometry(new VPhysicGeometryBox());

	pMassState->SetMass(in_fMasss);
	pBoxGeometry->SetLength(in_Expansion[0]);
	pBoxGeometry->SetWidth(in_Expansion[1]);
	pBoxGeometry->SetHeight(in_Expansion[2]);

	pBoxGeometry->CreateBox(in_pSpace);

	VSharedPtr<VPhysicBody> pPhysicBodyPart(
		in_pPhysicManager->GetPhysicWorld()->CreateBody());

	pReferencePointer = pPhysicBodyPart.Get();

	pPhysicBodyPart->AddState(pMassState.Get());
	pPhysicBodyPart->Create(in_pPhysicManager->GetPhysicWorld());
	pPhysicBodyPart->SetCollisionBody(pBoxGeometry.Get());

	VSharedPtr<VEntity> pObjectEntityBox(new entity::VEntity());
	
	pObjectEntityBox->AddPart(pPhysicBodyPart);

	resource::VResourceManagerPtr pResManager;

	VResourceId box = pResManager->GetResourceByName(in_sResourceName.c_str());

	graphics::VModelMesh::MeshPtr meshResourcePtr = 0;
	graphics::VModelMesh::MaterialPtr materialResourcePtr = 0;

	meshResourcePtr = box->GetData<graphics::IVMesh>();
	materialResourcePtr = box->GetData<graphics::IVMaterial>();

	VSharedPtr<scene::VModelPart> pSceneModel(new scene::VModelPart(VModel(VModelMesh(
		meshResourcePtr, materialResourcePtr))));

	pObjectEntityBox->AddPart(pSceneModel);

	return pObjectEntityBox;
}



//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------

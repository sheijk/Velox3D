/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */


#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Scene/Shapes/VPlaneMeshPart.h>

#include <V3d/Scene/Shapes/VArrowMeshPart.h>
#include <V3d/Scene/Shapes/VBoxMeshPart.h>
#include <V3d/Scene/Shapes/VCoordSysDisplayPart.h>
#include <V3d/Scene/Shapes/VPlaneMeshPart.h>
#include <V3d/Scene/Shapes/VSkyboxPart.h>
#include <V3d/Scene/Shapes/VSphereMeshPart.h>
#include <V3d/Scene/Shapes/VTerrainPart.h>
#include <V3d/Scene/Shapes/VTorusMeshPart.h>

#include <V3d/Physics/VBodyPart.h>
#include <V3d/Physics/VCollisionPart.h>
#include <V3d/Physics/VJointHinge2LinkAncestorBodyPart.h>
#include <V3d/Physics/VJointHinge2LinkPart.h>
#include <V3d/Physics/VJointHinge2ModifierPart.h>
#include <V3d/Physics/VJointHinge2Part.h>
#include <V3d/Physics/VPhysicManagerPart.h>

#include <V3d/Physics/Bounding/VBoundingBoxVolumePart.h>
#include <V3d/Physics/Bounding/VBoundingMeshVolumePart.h>
#include <V3d/Physics/Bounding/VBoundingPlaneVolumePart.h>
#include <V3d/Physics/Bounding/VBoundingSphereVolumePart.h>
#include <V3d/Physics/Bounding/VBoundingTerrainVolumePart.h>
#include <V3d/Physics/Bounding/VCollisionVisualizationPart.h>

#include <V3d/Entity/VRigidBodyPart.h>
#include <V3d/Entity/VUpdateablePart.h>
#include <V3d/Utils/VCameraPart.h>
#include <V3d/Utils/VCircleMoverPart.h>
#include <V3d/Utils/VFPSMoverPart.h>
#include <V3d/Utils/VInputPart.h>
#include <V3d/Utils/VTrackballPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
		extern void* AssureVPlaneMeshPartExist();
		extern void* AssureVArrowMeshPartExist();
		extern void* AssureVBoxMeshPartExist();
		extern void* AssureVCoordSysDisplayPartExist();
		extern void* AssureVDefaultRenderStepPartExist();
		extern void* AssureVLightPartExist();
		extern void* AssureVMeshPartExist();
		extern void* AssureVNaiveLightManagerExist();
		extern void* AssureVMirrorShootingExist();
		extern void* AssureVModelPartExist();
		extern void* AssureVNaiveSceneManagerPartExist();
		extern void* AssureVOffscreenShootingExist();
		extern void* AssureVOrientationGridPartExist();
		extern void* AssureVPlaneMeshPartExist();
		extern void* AssureVPostProcesssingRenderStepPartExist();
		extern void* AssureVPostProcesssingRenderStepPart2Exist();
		extern void* AssureVPostProcesssingRenderStepPart3Exist();
		extern void* AssureVPostProcesssingRenderStepPart4Exist();
		extern void* AssureVProjectTextureRenderStepPartExist();
		extern void* AssureVShadowMapRenderStepPartExist();
		extern void* AssureVSimpleShootingExist();
		extern void* AssureVSkyboxPartExist();
		extern void* AssureVSphereMeshPartExist();
		extern void* AssureVTerrainPartExist();
		extern void* AssureVTorusMeshPartExist();
}}

namespace v3d { namespace physics {
		extern void* AssureVBodyPartExist();
		extern void* AssureVCollisionPartExist();
		extern void* AssureVJointHinge2LinkAncestorBodyPartExist();
		extern void* AssureVJointHinge2LinkPartExist();
		extern void* AssureVJointHinge2ModifierPartExist();
		extern void* AssureVJointHinge2PartExist();
		extern void* AssureVPhysicManagerPartExist();
		extern void* AssureVBoundingBoxVolumePartExist();
		extern void* AssureVBoundingMeshVolumePartExist();
		extern void* AssureVBoundingPlaneVolumePartExist();
		extern void* AssureVBoundingSphereVolumePartExist();
		extern void* AssureVBoundingTerrainVolumePartExist();
		extern void* AssureVCollisionVisualizationPartExist();
}}

namespace v3d { namespace entity {
		//extern void* AssureVUpdateablePartExist();
		extern void* AssureVUpdateManagerPartExist();
		extern void* AssureVRigidBodyPartExist();
}}
namespace v3d { namespace utils {
		extern void* AssureVCameraPartExist();
		extern void* AssureVCircleMoverPartExist();
		extern void* AssureVFPSMoverPartExist();
		extern void* AssureVInputPartExist();
		extern void* AssureVTrackballPartExist();
}}

namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::entity;
using namespace v3d::scene;
using namespace v3d::graphics;

namespace {
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor

void foo()
{
	v3d::scene::AssureVArrowMeshPartExist();
	v3d::scene::AssureVBoxMeshPartExist();
	v3d::scene::AssureVCoordSysDisplayPartExist();
	v3d::scene::AssureVDefaultRenderStepPartExist();
	v3d::scene::AssureVLightPartExist();
	v3d::scene::AssureVMeshPartExist();
	v3d::scene::AssureVNaiveLightManagerExist();
	v3d::scene::AssureVMirrorShootingExist();
	v3d::scene::AssureVModelPartExist();
	v3d::scene::AssureVNaiveSceneManagerPartExist();
	v3d::scene::AssureVOffscreenShootingExist();
	v3d::scene::AssureVOrientationGridPartExist();
	v3d::scene::AssureVPlaneMeshPartExist();
	v3d::scene::AssureVPostProcesssingRenderStepPartExist();
	v3d::scene::AssureVPostProcesssingRenderStepPart2Exist();
	v3d::scene::AssureVPostProcesssingRenderStepPart3Exist();
	v3d::scene::AssureVPostProcesssingRenderStepPart4Exist();
	v3d::scene::AssureVProjectTextureRenderStepPartExist();
	//v3d::scene::AssureVShadowMapRenderStepPartExist();
	v3d::scene::AssureVSimpleShootingExist();
	v3d::scene::AssureVSkyboxPartExist();
	v3d::scene::AssureVSphereMeshPartExist();
	v3d::scene::AssureVTerrainPartExist();
	v3d::scene::AssureVTorusMeshPartExist();

	v3d::physics::AssureVBodyPartExist();
	v3d::physics::AssureVBoundingBoxVolumePartExist();
	v3d::physics::AssureVBoundingMeshVolumePartExist();
	v3d::physics::AssureVBoundingPlaneVolumePartExist();
	v3d::physics::AssureVBoundingSphereVolumePartExist();
	v3d::physics::AssureVBoundingTerrainVolumePartExist();
	v3d::physics::AssureVCollisionPartExist();
	v3d::physics::AssureVJointHinge2LinkAncestorBodyPartExist();
	v3d::physics::AssureVJointHinge2LinkPartExist();
	v3d::physics::AssureVJointHinge2ModifierPartExist();
	v3d::physics::AssureVJointHinge2PartExist();
	v3d::physics::AssureVPhysicManagerPartExist();
	v3d::physics::AssureVCollisionVisualizationPartExist();

	v3d::entity::AssureVRigidBodyPartExist();
	//v3d::entity::AssureVUpdateablePartExist();
	v3d::entity::AssureVUpdateManagerPartExist();

	v3d::utils::AssureVCameraPartExist();
	v3d::utils::AssureVCircleMoverPartExist();
	v3d::utils::AssureVFPSMoverPartExist();
	v3d::utils::AssureVInputPartExist();
	v3d::utils::AssureVTrackballPartExist();

}

//-----------------------------------------------------------------------------


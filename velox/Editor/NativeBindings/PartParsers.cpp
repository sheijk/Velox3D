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
		extern void* AssureVPlaneMeshPartExists();
		extern void* AssureVArrowMeshPartExists();
		extern void* AssureVBoxMeshPartExists();
		extern void* AssureVCoordSysDisplayPartExists();
		extern void* AssureVFrustumVisPartExists();
		extern void* AssureVDefaultRenderStepPartExists();
		extern void* AssureVLightPartExists();
		extern void* AssureVMeshPartExists();
		extern void* AssureVNaiveLightManagerExists();
		extern void* AssureVMirrorShootingExists();
		extern void* AssureVModelPartExists();
		extern void* AssureVNaiveSceneManagerPartExists();
		extern void* AssureVOffscreenShootingExists();
		extern void* AssureVShadowMapShootingExists();
		extern void* AssureVOrientationGridPartExists();
		extern void* AssureVPlaneMeshPartExists();
		extern void* AssureVPostProcesssingRenderStepPartExists();
		extern void* AssureVPostProcesssingRenderStepPart2Exists();
		extern void* AssureVPostProcesssingRenderStepPart3Exists();
		extern void* AssureVPostProcesssingRenderStepPart4Exists();
		extern void* AssureVProjectTextureRenderStepPartExists();
		extern void* AssureVShadowMapRenderStepPartExists();
		extern void* AssureVSimpleShootingExists();
		extern void* AssureVSkyboxPartExists();
		extern void* AssureVSphereMeshPartExists();
		extern void* AssureVTerrainPartExists();
		extern void* AssureVTorusMeshPartExists();
		extern void* AssureVCylinderMeshPartExists();
}}

namespace v3d { namespace physics {
		extern void* AssureVBodyPartExists();
		extern void* AssureVCollisionPartExists();
		extern void* AssureVJointHinge2ModifierPartExists();
		extern void* AssureVJointHinge2PartExists();
		extern void* AssureVPhysicManagerPartExists();
		extern void* AssureVBoundingBoxVolumePartExists();
		extern void* AssureVBoundingMeshVolumePartExists();
		extern void* AssureVBoundingCCylinderVolumePartExists();
		extern void* AssureVBoundingPlaneVolumePartExists();
		extern void* AssureVBoundingSphereVolumePartExists();
		extern void* AssureVBoundingTerrainVolumePartExists();
		extern void* AssureVCollisionVisualizationPartExists();
}}

namespace v3d { namespace entity {
		//extern void* AssureVUpdateablePartExists();
		extern void* AssureVUpdateManagerPartExists();
		extern void* AssureVRigidBodyPartExists();
}}
namespace v3d { namespace utils {
		extern void* AssureVCameraPartExists();
		extern void* AssureVCircleMoverPartExists();
		extern void* AssureVFPSMoverPartExists();
		extern void* AssureVInputPartExists();
		extern void* AssureVTrackballPartExists();
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
	v3d::scene::AssureVArrowMeshPartExists();
	v3d::scene::AssureVBoxMeshPartExists();
	v3d::scene::AssureVCoordSysDisplayPartExists();
	v3d::scene::AssureVFrustumVisPartExists();
	v3d::scene::AssureVDefaultRenderStepPartExists();
	v3d::scene::AssureVLightPartExists();
	v3d::scene::AssureVMeshPartExists();
	v3d::scene::AssureVNaiveLightManagerExists();
	v3d::scene::AssureVMirrorShootingExists();
	v3d::scene::AssureVModelPartExists();
	v3d::scene::AssureVNaiveSceneManagerPartExists();
	v3d::scene::AssureVOffscreenShootingExists();
	v3d::scene::AssureVShadowMapShootingExists();
	v3d::scene::AssureVOrientationGridPartExists();
	v3d::scene::AssureVPlaneMeshPartExists();
	v3d::scene::AssureVPostProcesssingRenderStepPartExists();
	v3d::scene::AssureVPostProcesssingRenderStepPart2Exists();
	v3d::scene::AssureVPostProcesssingRenderStepPart3Exists();
	v3d::scene::AssureVPostProcesssingRenderStepPart4Exists();
	v3d::scene::AssureVProjectTextureRenderStepPartExists();
	v3d::scene::AssureVSimpleShootingExists();
	v3d::scene::AssureVSkyboxPartExists();
	v3d::scene::AssureVSphereMeshPartExists();
	v3d::scene::AssureVTerrainPartExists();
	v3d::scene::AssureVTorusMeshPartExists();
	v3d::scene::AssureVCylinderMeshPartExists();

	v3d::physics::AssureVBodyPartExists();
	v3d::physics::AssureVBoundingBoxVolumePartExists();
	v3d::physics::AssureVBoundingMeshVolumePartExists();
	v3d::physics::AssureVBoundingPlaneVolumePartExists();
	v3d::physics::AssureVBoundingSphereVolumePartExists();
	v3d::physics::AssureVBoundingTerrainVolumePartExists();
	v3d::physics::AssureVBoundingCCylinderVolumePartExists();
	v3d::physics::AssureVCollisionPartExists();
	v3d::physics::AssureVJointHinge2ModifierPartExists();
	v3d::physics::AssureVJointHinge2PartExists();
	v3d::physics::AssureVPhysicManagerPartExists();
	v3d::physics::AssureVCollisionVisualizationPartExists();

	v3d::entity::AssureVRigidBodyPartExists();
	//v3d::entity::AssureVUpdateablePartExists();
	v3d::entity::AssureVUpdateManagerPartExists();

	v3d::utils::AssureVCameraPartExists();
	v3d::utils::AssureVCircleMoverPartExists();
	v3d::utils::AssureVFPSMoverPartExists();
	v3d::utils::AssureVInputPartExists();
	v3d::utils::AssureVTrackballPartExists();

}

//-----------------------------------------------------------------------------


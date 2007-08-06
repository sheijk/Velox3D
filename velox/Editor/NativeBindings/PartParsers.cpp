/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
		extern void* AssureVLightPartExists();
		extern void* AssureVNaiveLightManagerExists();

		extern void* AssureVNaiveSceneManagerPartExists();

		extern void* AssureVPostProcesssingRenderStepPartExists();
		extern void* AssureVPostProcesssingRenderStepPart2Exists();
		extern void* AssureVPostProcesssingRenderStepPart3Exists();
		extern void* AssureVPostProcesssingRenderStepPart4Exists();

		extern void* AssureVProjectTextureRenderStepPartExists();
		extern void* AssureVShadowMapRenderStepPartExists();
		extern void* AssureVDefaultRenderStepPartExists();

		extern void* AssureVSimpleShootingExists();
		extern void* AssureVMirrorShootingExists();
		extern void* AssureVOffscreenShootingExists();
		extern void* AssureVShadowMapShootingExists();
		extern void* AssureVCubemapShootingExists();

		extern void* AssureVSkyboxPartExists();
		extern void* AssureVTerrainPartExists();

		extern void* AssureVCoordSysDisplayPartExists();
		extern void* AssureVOrientationGridPartExists();
		extern void* AssureVFrustumVisPartExists();

		extern void* AssureVShowSelectionPartExists();

		extern void* AssureVSphereMeshPartExists();
		extern void* AssureVTorusMeshPartExists();
		extern void* AssureVCylinderMeshPartExists();
		extern void* AssureVPlaneMeshPartExists();
		extern void* AssureVArrowMeshPartExists();
		extern void* AssureVBoxMeshPartExists();

		extern void* AssureVMeshPartExists();
		extern void* AssureVModelPartExists();

		extern void* AssureVGCMTerrainPartExists();
		extern void* AssureVGCMDummyHeightmapPartExists();
		extern void* AssureVGCMRawHeightmapPartExists();
		extern void* AssureVGCMStretchedHeightmapPartExists();
		extern void* AssureVSkyPartExists();
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
		extern void* AssureVEntityExists();
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
using namespace v3d;
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
	v3d::scene::AssureVGCMTerrainPartExists();
	v3d::scene::AssureVGCMDummyHeightmapPartExists();
	v3d::scene::AssureVGCMRawHeightmapPartExists();
	v3d::scene::AssureVGCMStretchedHeightmapPartExists();
	v3d::scene::AssureVCubemapShootingExists();
	v3d::scene::AssureVShowSelectionPartExists();
	v3d::scene::AssureVSkyPartExists();

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
	v3d::entity::AssureVEntityExists();

	v3d::utils::AssureVCameraPartExists();
	v3d::utils::AssureVCircleMoverPartExists();
	v3d::utils::AssureVFPSMoverPartExists();
	v3d::utils::AssureVInputPartExists();
	v3d::utils::AssureVTrackballPartExists();
}
//-----------------------------------------------------------------------------

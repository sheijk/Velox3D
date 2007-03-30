/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VOPOCODESYSTEM_09_10_04_H
#define V3D_VOPOCODESYSTEM_09_10_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/Geometry/VVertex3f.h>
#include "VContactReport.h"
#include "VCollisionException.h"
#include "VCollisionObject.h"
#include <V3d/Collision/VOpcode.h>


//-----------------------------------------------------------------------------
namespace v3d {
namespace collision {
//-----------------------------------------------------------------------------

/**
 * OpcodeSystem provides easy to manage collision queries
 * Wrapps most opcode features by Pierre Terdiman (thx mate, nice lib :) )
 *
 * @author:		ins
 * @version:	1.0
 * @note:		uses opcode 1.3
 *
 */

class VOpcodeSystem
{

public:

	enum Mode
	{
		Ray,
		AABBox,
		Sphere,
		//Plane,
		Mesh,
		//OBBox
	};

	/**
	 * Properties for each collider
	 * Some entries may not be used for specail collider
	 * This settings will then be irgnored
	 */

	struct ColliderProperties
	{
		ColliderProperties()

		{
			bFirstContact		= true;
			bTemporalCoherence	= false;
			bClosestHit			= true;
			bCulling			= true;
			bFullBoxTest		= true;
			bFullPrimTest		= false;
			fMaxDistance		= 1000.0f;
		}
		
		
		vbool		 bFirstContact;
		vbool		 bTemporalCoherence;
		vbool		 bClosestHit;
		vbool		 bCulling;
		vbool		 bFullBoxTest;
		vbool		 bFullPrimTest;
		vfloat32	 fMaxDistance;
	};


	VOpcodeSystem();
	~VOpcodeSystem();

	/**
	 * Set collider properties for your need of information
	 */

	void SetColliderProperties(
		enum Mode in_Type,
		ColliderProperties in_Properties
		);

	/**
	 * Checks collision of a ray with a model
	 * Returns true if ray hits the model false otherwise
	 * To check in fast mode just set the ray properties
	 * to bFirstContact true. ContactReport holds more
	 * information of the intersection after the call
	 * Pass 0 pointer if no ContactReport should be calculated
	 */

	//TODO: optimize ContactReport to not allocate mem each frame
	
	vbool CollideRay(
		graphics::VVertex3f in_Direction,
		graphics::VVertex3f in_Origin,
		VCollisionObject* in_pObject,
		VContactReport* out_pReport
		);

	/**
	 * Checks  collison of a sphere and a model
	 * Returns true if overlap occurs false otherwise
	 * @param: in_pWorldMatrix: world matrix of the
	 *		   sphere to test against
	 * @note:  matrix MUST not contain scale. 
	 *		   only rotation and translation
	 *		   is supported by opcode
	 */

	vbool CollideSphere(
		graphics::VVertex3f in_Origin,
		vfloat32 in_fRadius,
		math::VMatrix44f* in_pWorldMatrix,
		VCollisionObject* in_pObject,
		VContactReport* out_pReport
		);

	/**
	 * Checks collision of 2 objects given by param
	 * Returns true on contact false otherwise
	 * Pass 0 for out_pReportObject1/2 if fast mode
	 * is enough for your needs
	 */

	vbool CollideObject(
		VCollisionObject* in_pObject1,
		VCollisionObject* in_pObject2,
		VContactReport* out_pReportObject1,
		VContactReport* out_pReportObject2
		);

	/**
	 * Checks collision of an AABox with the model
	 * Returns true on collision false otherwise
	 * Pass 0 pointer as out_pReport if no exact
	 * collision data is needed
	 * @param: in_MinPoint defines the minimum point
	 *		   of the box
	 * @param: in_MaxPoint deinfines the maximum point
	 *		   of the box
	 * @note:  Box must be provided in worldspace!
	 */


	vbool CollideAABB(
		graphics::VVertex3f in_MinPoint,
		graphics::VVertex3f in_MaxPoint,
		VCollisionObject* in_pObject,
		VContactReport* out_pReort
		);


private:

	/**
	 * The Opcode collider classes. can be reused each frame
	 */

	Opcode::RayCollider			m_RayCollider;
	Opcode::AABBCollider		m_AABBCollider;
	Opcode::AABBTreeCollider	m_AABBTreeCollider;
	Opcode::SphereCollider		m_SphereCollider;
    //Opcode::OBBCollider			m_OBBCOllider;
	//Opcode::PlanesCollider		m_PlanesCollider;

	/**
	 * The Opcode caches for collider. can be reused each frame
	 */

	Opcode::SphereCache		m_SphereCache;
	Opcode::AABBCache		m_AABBCache;
	Opcode::BVTCache		m_BVTCache;
	Opcode::CollisionFaces  m_CollisionFaces;
	//Opcode::OBBCache		m_OBBCache;
	//Opcode::PlanesCache	m_PlanesCache;

	/**
	 * Collider properties for each collider
	 */

	ColliderProperties m_RayColliderProperties;
	ColliderProperties m_SphereColliderProperties;
	ColliderProperties m_AABBColliderProperties;
	ColliderProperties m_AABBTreeColliderProperties;
	//ColliderProperties m_PlaneColliderProperties;
	//ColliderProperties m_OBBColliderProperties;

};

//-----------------------------------------------------------------------------
} // namespace collision
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VOPOCODESYSTEM_09_10_04_H


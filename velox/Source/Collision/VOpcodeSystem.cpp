#include <v3dLib/Collision/VOpcodeSystem.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace collision {
//-----------------------------------------------------------------------------
VOpcodeSystem::VOpcodeSystem()
{
}

VOpcodeSystem::~VOpcodeSystem()
{
}

vbool VOpcodeSystem::CollideRay(
								graphics::VVertex3f in_Direction,
								graphics::VVertex3f in_Origin,
								VCollisionObject* in_pObject,
								VContactReport* out_pReport
								)
{
	if(in_pObject == 0)
		V3D_THROW(CollisionException, "object is 0!");

	m_RayCollider.SetFirstContact(m_RayColliderProperties.bFirstContact);
	m_RayCollider.SetTemporalCoherence(
		m_RayColliderProperties.bTemporalCoherence
		);
	
	m_RayCollider.SetClosestHit(m_RayColliderProperties.bClosestHit);
	m_RayCollider.SetCulling(m_RayColliderProperties.bCulling);
	m_RayCollider.SetMaxDist(m_RayColliderProperties.fMaxDistance);

	//create the ray out of given params
	::Ray opRay;

	opRay.mOrig.x	= in_Origin.x;
	opRay.mOrig.y	= in_Origin.y;
	opRay.mOrig.z	= in_Origin.z;
	opRay.mDir.x	= in_Direction.x;
	opRay.mDir.y	= in_Direction.y;
	opRay.mDir.z	= in_Direction.z;;

	m_RayCollider.SetDestination(&m_CollisionFaces);

	if(in_pObject->GetWorldMatrix() == 0)
	{
		m_RayCollider.Collide(opRay, in_pObject->GetOpcodeModel());
	}
	//use world matrix
	else
	{
		//we need to convert our matrix format to the one used by opcode
		//TODO: evil cast. check if its working...
		Matrix4x4* mat = (Matrix4x4*) &(in_pObject->GetWorldMatrix()->m_Mat.mData);
		
		m_RayCollider.Collide(
			opRay,
			in_pObject->GetOpcodeModel(),
			mat
			);
	}

    if(m_CollisionFaces.GetNbFaces())
	{

		if(out_pReport != 0) //do we want extra information?
		{
			//avoid memleaks where we can :)
			if(out_pReport->GetTriangleIndices() != 0)
				out_pReport->Delete();

			
			//we just want to know the first closest hit and so one index
			vfloat32 fLastDistance =  m_CollisionFaces.GetFaces()[0].mDistance;
			int iLastSmallestIndex = 0;

			if(m_RayColliderProperties.bClosestHit)
			{
				for(vuint i = 0; i < m_CollisionFaces.GetNbFaces(); i++)
				{
					if(m_CollisionFaces.GetFaces()[i].mDistance < fLastDistance)
					{
						fLastDistance = m_CollisionFaces.GetFaces()[i].mDistance;
						iLastSmallestIndex = i;
					}
				}

				out_pReport->SetContactCount(1);
				vuint32* pIndex =  out_pReport->GetTriangleIndices();
				pIndex = new vuint32[1];

				pIndex[0] = iLastSmallestIndex;
			}

			else
			{
				out_pReport->SetContactCount(m_CollisionFaces.GetNbFaces());

				vuint32* pIndex = out_pReport->GetTriangleIndices();
				pIndex = new vuint32[out_pReport->GetContactCount()];

				for(vuint i = 0; i < m_CollisionFaces.GetNbFaces(); i++)
				{
					pIndex[i] = m_CollisionFaces.GetFaces()[i].mFaceID;
				}

			}
		}        

		return true;
	}

	return false;
}

vbool VOpcodeSystem::CollideSphere(
								   graphics::VVertex3f in_Origin,
								   vfloat32 in_fRadius,
								   VMatrix44f* in_pWorldMatrix,
								   VCollisionObject* in_pObject,
								   VContactReport* out_pReport)
{
	if(in_pObject == 0)
		V3D_THROW(CollisionException, "object is 0!");

	m_SphereCollider.SetFirstContact(m_SphereColliderProperties.bFirstContact);
	m_SphereCollider.SetTemporalCoherence(
		m_SphereColliderProperties.bTemporalCoherence
		);

	::Sphere sphere(Point(in_Origin.x, in_Origin.y, in_Origin.z), in_fRadius);

	if(in_pWorldMatrix != 0 && in_pObject->GetWorldMatrix() != 0)
	{
	
		//we need to convert our matrix format to the one used by opcode
		//TODO: evil cast. check if its working...
		Matrix4x4* spheremat = (Matrix4x4*) &(in_pWorldMatrix->m_Mat.mData);
		Matrix4x4* meshmat = (Matrix4x4*) &(in_pObject->GetWorldMatrix()->m_Mat.mData);

		m_SphereCollider.Collide(
			m_SphereCache,
			sphere,
			in_pObject->GetOpcodeModel(),
			spheremat, meshmat);
	}

	// all matrices are identities so use optimze opcode path
	else
	{
		m_SphereCollider.Collide(m_SphereCache, sphere, in_pObject->GetOpcodeModel());
	}

	// do we have a collision?
	if(m_SphereCollider.GetContactStatus())
	{
		//generate a contact report
		if(out_pReport != 0)
		{
			//avoid memleaks where we can :)
			if(out_pReport->GetTriangleIndices() != 0)
				out_pReport->Delete();
			
			out_pReport->SetContactCount(m_SphereCollider.GetNbTouchedPrimitives());

			vuint32* pIndex = out_pReport->GetTriangleIndices();

			pIndex = new vuint32[out_pReport->GetContactCount()];

			// our list of touched indices
			const vuint* pIndexList = m_SphereCollider.GetTouchedPrimitives();

			//copy them to our report
			for(vuint i = 0; i < out_pReport->GetContactCount(); i++)
			{
				pIndex[i] = pIndexList[i];
			}
		}

		return true;
	}
	return false;
}

vbool VOpcodeSystem::CollideObject(
			  VCollisionObject* in_pObject1,
			  VCollisionObject* in_pObject2,
			  VContactReport* out_pReportObject1,
			  VContactReport* out_pReportObject2
			  )
{

	//perform error check
	if(in_pObject1 == 0 || in_pObject2 == 0)
        V3D_THROW(CollisionException, "objects are 0!");

	m_AABBTreeCollider.SetFirstContact(m_AABBTreeColliderProperties.bFirstContact);
	m_AABBTreeCollider.SetFullBoxBoxTest(m_AABBTreeColliderProperties.bFullBoxTest);
	m_AABBTreeCollider.SetFullPrimBoxTest(m_AABBTreeColliderProperties.bFullPrimTest);
	m_AABBTreeCollider.SetTemporalCoherence(
		m_AABBTreeColliderProperties.bTemporalCoherence
		);

	m_BVTCache.Model0 = &in_pObject1->GetOpcodeModel();
	m_BVTCache.Model1 = &in_pObject2->GetOpcodeModel();


	// make sure valid matrix is given otherwise paste opcode 0 as identity
	Matrix4x4* mat1 = 0;
	Matrix4x4* mat2 = 0;

	//make ugly cast
	if(in_pObject1->GetWorldMatrix() != 0)
	{
        mat1 = (Matrix4x4*)in_pObject1->GetWorldMatrix()->m_Mat.mData;
	}

	if(in_pObject2->GetWorldMatrix() != 0)
	{
		mat2 = (Matrix4x4*)in_pObject2->GetWorldMatrix()->m_Mat.mData;
	}
	
	//check collision
	m_AABBTreeCollider.Collide(
		m_BVTCache,
		mat1,
		mat2
		);

	// do we have one?
	if(m_AABBTreeCollider.GetContactStatus())
	{
		//need extra information?
		if(out_pReportObject1 != 0 && out_pReportObject2 != 0)
		{
            vuint iNumContacts = m_AABBTreeCollider.GetNbPairs();
			const Pair* collidingPairs = m_AABBTreeCollider.GetPairs();

			// avoid mem leaks
			if(out_pReportObject1->GetTriangleIndices() != 0)
				out_pReportObject1->Delete();

			if(out_pReportObject2->GetTriangleIndices() != 0)
				out_pReportObject2->Delete();

			//reserve memory
			out_pReportObject1->SetContactCount(iNumContacts);
			out_pReportObject2->SetContactCount(iNumContacts);

			vuint32* pIndex1 = out_pReportObject1->GetTriangleIndices();
			vuint32* pIndex2 = out_pReportObject2->GetTriangleIndices();

			pIndex1 = new vuint[iNumContacts];
			pIndex2 = new vuint[iNumContacts];

			//store the face id's collided
			for(vuint i = 0; i < iNumContacts; i++)
			{
				pIndex1[i] = collidingPairs[i].id0;
				pIndex2[i] = collidingPairs[i].id1;
			}
		}
		return true;
	}

	return false;
}

vbool VOpcodeSystem::CollideAABB(
							 graphics::VVertex3f in_MinPoint,
							 graphics::VVertex3f in_MaxPoint,
							 VCollisionObject* in_pObject,
							 VContactReport* out_pReport
							 )
{
	//perform error check
	if(in_pObject == 0)
		V3D_THROW(CollisionException, "object is 0!");
	
	m_AABBCollider.SetFirstContact(m_AABBColliderProperties.bFirstContact);
	m_AABBCollider.SetTemporalCoherence(
		m_AABBColliderProperties.bTemporalCoherence);

	AABB box;
	box.SetMinMax(
		Point(in_MinPoint.x, in_MinPoint.y, in_MinPoint.z),
		Point(in_MaxPoint.x, in_MaxPoint.y, in_MaxPoint.z));

	m_AABBCollider.Collide(m_AABBCache, box, in_pObject->GetOpcodeModel());

	//do we have a collision?
	if(m_AABBCollider.GetContactStatus())
	{
		//check if extra infos are needed
		if(out_pReport != 0)
		{
			const vuint  iNumFacesTouched 
				= m_AABBCollider.GetNbTouchedPrimitives();
			const vuint* faceIndex		
				= m_AABBCollider.GetTouchedPrimitives();

			//avoid mem leak
			if(out_pReport->GetTriangleIndices() != 0)
				out_pReport->Delete();

			out_pReport->SetContactCount(iNumFacesTouched);

			vuint32* pIndex = out_pReport->GetTriangleIndices();

			pIndex = new vuint[iNumFacesTouched];

			//copy face id's
			for(vuint i = 0; i < iNumFacesTouched; i++)
			{
				pIndex[i] = faceIndex[i];
			}
		}

		return true;
	}
	return false;
}

void VOpcodeSystem::SetColliderProperties(enum Mode in_Type,
										  ColliderProperties in_Properties)
{

	switch(in_Type)
	{
	case Mode::Ray:
		{	
			m_RayColliderProperties		= in_Properties;
			break;
		}

	case Mode::Sphere:
		{
            m_SphereColliderProperties	= in_Properties;
			break;
		}
	case Mode::AABBox:
		{
			m_AABBColliderProperties	= in_Properties;
			break;
		}

	/*case Mode::OBBox:
		{
			m_OBBColliderProperties		= in_Properties;
			break;
		}

	case Mode::Plane:
		{
			m_PlaneColliderProperties	= in_Properties;
			break;
		}*/

	case Mode::Mesh:
		{
			m_AABBTreeColliderProperties = in_Properties;
		}
	default:
		{
			V3D_THROW(CollisionException, "invalid mode for collider properties!");
			break;
		}
	}
}

//-----------------------------------------------------------------------------
} // namespace collision
} // namespace v3d
//-----------------------------------------------------------------------------
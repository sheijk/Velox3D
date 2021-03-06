/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/VStateOrientation.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace  physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

/**
 * standard c'tor
 */
VStateOrientation::VStateOrientation(VState::Parent in_pParent) : VState(in_pParent)
{

}

/**
 * d'tor
 */
VStateOrientation::~VStateOrientation()
{
}

void VStateOrientation::Apply()
{
	dQuaternion q;

	q[1]=m_Quaternion[0];
	q[2]=m_Quaternion[1];
	q[3]=m_Quaternion[2];
	q[0]=m_Quaternion[3];

	VState::Parent pParent = GetParent();
    dBodySetQuaternion(pParent->GetBodyID(), q);
}

VQuatf& VStateOrientation::GetQuat()
{
	return m_Quaternion;
}

VVector4f VStateOrientation::GetAsVector()
{
	VVector4f quat;
	
	for(vuint i=0; i < 4; i++)
	{
		quat.Set(i, m_Quaternion[i]);
	}
	return quat;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::
//-----------------------------------------------------------------------------


#include <V3d/Physics/VStateOrientation.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace  physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

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

	VState::Parent pParent = static_cast<VState::Parent>(GetParent());
    dBodySetQuaternion(*pParent->GetBodyID(), q);
}

VQuatf& VStateOrientation::GetQuat()
{
	return m_Quaternion;
}


//-----------------------------------------------------------------------------
}} // namespace v3d::
//-----------------------------------------------------------------------------

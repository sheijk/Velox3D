#include <V3d/Entity/VUnconnectedPart.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

vbool VUnconnectedPart::IsReady() const
{
	return true;
}

vuint VUnconnectedPart::DependencyCount() const
{
	return 0;
}

IVPart::Dependency VUnconnectedPart::GetDependencyInfo(vuint in_nIndex) const
{
	V3D_THROWMSG(VException, "Error when querying dependecies ("
		<< in_nIndex << ") out of bounds");
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------

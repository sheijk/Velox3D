#ifndef V3D_VUNCONNECTEDPART_2005_08_01_H
#define V3D_VUNCONNECTEDPART_2005_08_01_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
* Base class for parts which don't need any connections to other parts
*
* @author sheijk
*/
template<typename Parent>
class VUnconnectedPartAdapter : public Parent
{
public:
	virtual vbool IsReady() const { return true; }
	virtual vuint DependencyCount() const { return 0; }
	virtual VPartDependency GetDependencyInfo(vuint in_nIndex) const
	{
		V3D_THROWMSG(VException, "Error when querying dependecies ("
			<< in_nIndex << ") out of bounds");
	}
};

typedef VUnconnectedPartAdapter<IVPart> VUnconnectedPart;

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VUNCONNECTEDPART_2005_08_01_H

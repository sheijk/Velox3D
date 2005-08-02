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
class VUnconnectedPart : public IVPart
{
public:
	virtual vbool IsReady() const;
	virtual vuint DependencyCount() const;
	virtual Dependency GetDependencyInfo(vuint in_nIndex) const;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VUNCONNECTEDPART_2005_08_01_H

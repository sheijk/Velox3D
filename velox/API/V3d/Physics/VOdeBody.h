#ifndef V3D_VODEBODY_2006_02_13_H
#define V3D_VODEBODY_2006_02_13_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <ode/ode.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; 

/**
 * Ode body implementation
 */

class VWorld;
class VOdeBody
{
public:

	VOdeBody();
	virtual ~VOdeBody();

	dBodyID* GetBodyID();
	void Create(VWorld* in_pWorld);
	void Destroy();
	vbool IsAlive();

private:

	vbool m_bIsAlive;
	dBodyID m_Body;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::
//-----------------------------------------------------------------------------
#endif // V3D_VODEBODY_2006_02_13_H

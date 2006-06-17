#ifndef V3D_VSHADOWMAPSHOOTING_2006_06_02_H
#define V3D_VSHADOWMAPSHOOTING_2006_06_02_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/Shootings/VShootingBase.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VShadowMapShooting : public VShootingBase
{
public:
	VShadowMapShooting();
	virtual ~VShadowMapShooting();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VSHADOWMAPSHOOTING_2006_06_02_H

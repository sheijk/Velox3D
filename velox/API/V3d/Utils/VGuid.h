#ifndef V3D_VGUID_H
#define V3D_VGUID_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
* Generate ID for Objects
*
* @author lars
*/
class VGuid
{
public:

	VGuid();
	virtual ~VGuid();

	vbool operator==(const VGuid& in_other) const;
	vbool operator!=(const VGuid& in_other) const;
	
	/** Generate a ID */
	VGuid Generate();

private:

	vint m_iID;
};

//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGUID_H
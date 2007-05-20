#ifndef V3D_VBASEPARTUSER_2005_10_23_H
#define V3D_VBASEPARTUSER_2005_10_23_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "VBasePart.h"

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VBasePartUser : public entity::VPart
{
public:
	VBasePartUser() :
		m_pBasePart(RegisterTo())
	{
	}

	static std::string GetDefaultId() { return "basepartuser"; }
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	entity::VNodeConnection<VBasePart> m_pBasePart;

};

//-----------------------------------------------------------------------------
} // namespace v3d

V3D_TYPEINFO_WITHPARENT(v3d::VBasePartUser, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VBASEPARTUSER_2005_10_23_H

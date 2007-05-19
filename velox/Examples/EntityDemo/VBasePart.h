#ifndef V3D_VBASEPART_2005_10_23_H
#define V3D_VBASEPART_2005_10_23_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/VUnconnectedPart.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VBasePart : public entity::VUnconnectedPart
{
public:
	virtual void SayHello() 
	{
		vout << "VBasePart::SayHello" << vendl;
	}

	static std::string GetDefaultId()
	{
		return std::string("basepart");
	}

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
};

//-----------------------------------------------------------------------------
} // namespace v3d

V3D_TYPEINFO_WITHPARENT(v3d::VBasePart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VBASEPART_2005_10_23_H

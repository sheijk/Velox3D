#ifndef V3D_VDERIVEDPART_2005_10_23_H
#define V3D_VDERIVEDPART_2005_10_23_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include "VBasePart.h"
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VDerivedPart : public VBasePart
{
public:
	virtual void SayHello() 
	{
		vout << "VDerivedPart::SayHello" << vendl;
	}

	static std::string GetDefaultId()
	{
		return std::string("derivedpart");
	}

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
};

//-----------------------------------------------------------------------------
} // namespace v3d

V3D_TYPEINFO_WITHPARENT(v3d::VDerivedPart, v3d::VBasePart);
//-----------------------------------------------------------------------------
#endif // V3D_VDERIVEDPART_2005_10_23_H

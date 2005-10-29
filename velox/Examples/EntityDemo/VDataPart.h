#ifndef V3D_VDATAPART_2004_10_10_H
#define V3D_VDATAPART_2004_10_10_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VIOStream.h>

#include <V3d/Entity/VUnconnectedPart.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VDataPart : public entity::VUnconnectedPart
{
	vint data;
public:
	VDataPart(vint d) { data = d; }

	void Activate()
	{
		vout << "activating VDataPart, " << data << vendl;
	}

	void Deactivate()
	{
		vout << "deactivating VDataPart, " << data << vendl;
	}

	vint GetData() { return data; }
	void SetData(int d) { data = d; }

	static std::string GetDefaultId()
	{
		return std::string("data");
	}

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
};

//-----------------------------------------------------------------------------
} // namespace v3d

V3D_TYPEINFO_WITHPARENT(v3d::VDataPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VDATAPART_2004_10_10_H

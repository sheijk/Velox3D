#ifndef V3D_VDATAPART_2004_10_10_H
#define V3D_VDATAPART_2004_10_10_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VDataPart : public entity::IVPart
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
		vout << "deactivating VDataPart" << vendl;
	}

	vint GetData() { return data; }
	void SetData(int d) { data = d; }
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDATAPART_2004_10_10_H

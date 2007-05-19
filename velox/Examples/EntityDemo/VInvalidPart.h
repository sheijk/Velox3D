#ifndef V3D_VINVALIDPART_2005_08_01_H
#define V3D_VINVALIDPART_2005_08_01_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VIOStream.h>

#include <V3d/Entity/VUnconnectedPart.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VInvalidPart : public entity::VUnconnectedPart
{
public:
	virtual vbool IsReady() const
	{
		return false;
	}

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	virtual void OnActivate()
	{
		vout << "Error: invalid part activated" << vendl;
	}

	virtual void OnDeactivate()
	{
		vout << "Error: invalid part deactivated" << vendl;
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d

V3D_TYPEINFO_WITHPARENT(v3d::VInvalidPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VINVALIDPART_2005_08_01_H

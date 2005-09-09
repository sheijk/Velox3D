//TODO: add file creation date to file guard
#ifndef V3D_IVSHOOTING_2005_05_20_H
#define V3D_IVSHOOTING_2005_05_20_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVShooting : public entity::IVPart
{
public:
	virtual ~IVShooting() {}

	virtual void Cull() = 0;
	virtual void Render() = 0;

	static std::string GetDefaultId() { return "shooting"; }

	virtual vbool IsActive() const = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_IVSHOOTING_2005_05_20_H

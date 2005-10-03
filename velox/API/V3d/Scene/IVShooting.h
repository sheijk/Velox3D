//TODO: add file creation date to file guard
#ifndef V3D_IVSHOOTING_2005_05_20_H
#define V3D_IVSHOOTING_2005_05_20_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPart.h>
#include <V3dLib/Graphics/Misc/IVCamera.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVShooting : public entity::IVPart
{
public:
	virtual ~IVShooting() {}

	virtual void UpdateAndCull() = 0;
	virtual void Render() = 0;

	virtual vbool IsActive() const = 0;

	static std::string GetDefaultId() { return "shooting"; }
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_IVSHOOTING_2005_05_20_H

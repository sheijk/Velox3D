#ifndef V3D_IVSECTOR_H
#define V3D_IVSECTOR_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Utils/Graphics/VCamera.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
/**
 * IVSector interface. Derive each geometry implementation of this class
 */

class IVSector
{
public:

	virtual void Render(const VCamera& in_Camera) = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVSECTOR_H

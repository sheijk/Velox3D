#ifndef V3D_IVCELL_H
#define V3D_IVCELL_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3dLib/Graphics/Misc/VCamera.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
/**
 * IVCell interface. Derive each geometry implementation of this class
 */

class IVCell
{
public:

	virtual void Cull(graphics::VCamera* in_pCamera) = 0;
	virtual void Hide() = 0;
	virtual void Show() = 0;

};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVCELL_H

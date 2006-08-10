#ifndef V3D_IVCELL_H
#define V3D_IVCELL_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3dLib/Graphics/Misc/VCamera.h>
#include <V3dLib/Graphics/Misc/VMultipassDrawList.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * IVCell interface. Derive each geometry implementation of this class
 *
 * @author ins, sheijk
 */
class IVCell
{
public:

	virtual void Cull(
		VCamera* in_pCamera,
		VMultipassDrawList& in_DrawList
		) = 0;

	virtual void Hide(VMultipassDrawList& in_DrawList) = 0;
	//virtual void Show(VMultipassDrawList& in_DrawList) = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVCELL_H
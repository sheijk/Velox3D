#include <v3d/Utils/Graphics/VVertexDataLayout.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics{
//-----------------------------------------------------------------------------
vbool VVertexDataLayout::IsValidOffset(Offset offs)
{
	return offs >= 0;
}
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------

//TODO: add file creation date to file guard
#ifndef V3D_VBUFFERRESTYPE_H
#define V3D_VBUFFERRESTYPE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Loads graphic device buffers for a resource
 *
 * @author sheijk
 */
class VBufferResType
{
public:
	VBufferResType();
	virtual ~VBufferResType();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VBUFFERRESTYPE_H

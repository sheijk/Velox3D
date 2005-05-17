#ifndef V3D_IVRENDERCONTEXT_H
#define V3D_IVRENDERCONTEXT_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVRenderContext
{
public:

	IVRenderContext() {};
	virtual ~IVRenderContext() {};

	virtual void MakeCurrent() = 0;
	virtual void Use();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

#endif //V3D_IVRENDERCONTEXT_H
#ifndef V3D_IVOPENGLRENDERSTATE_H
#define V3D_IVOPENGLRENDERSTATE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/IVRenderState.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VOpenGLDevice;

class IVOpenGLRenderState : public IVRenderState
{
public:
	virtual void Apply(const VOpenGLDevice* in_pDevice) const
	{
		Apply();
	}

protected:
	virtual void Apply() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVOPENGLRENDERSTATE_H

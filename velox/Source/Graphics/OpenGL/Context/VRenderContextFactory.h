#ifndef V3D_VRENDERCONTEXTFACTORY_H
#define V3D_VRENDERCONTEXTFACTORY_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>
#include <v3d/Core/VIOStream.h>
#include <v3d/Core/SmartPtr/VSharedPtr.h>
#include <v3d/Graphics/IVRenderContext.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

template <class T>
class VRenderContextFactory
{
public:

	VRenderContextFactory(T* in_pinstance = 0);
	virtual ~VRenderContextFactory();

	VSharedPtr<graphics::IVRenderContext> GetInstance();
	void DeleteInstance();

private:

	T* m_pinstance;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

#endif //V3D_VRENDERCONTEXTFACTORY_H
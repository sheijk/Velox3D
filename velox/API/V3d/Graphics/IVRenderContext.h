#ifndef V3D_IVRENDERCONTEXT_H
#define V3D_IVRENDERCONTEXT_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A rendering context. Used internally by the graphics device to enable
 * it's associated opengl context. Abstracts platform specific ways to switch
 * the rendering context (multiple windows, pbuffers, etc.)
 *
 * @author lars
 */
class IVRenderContext
{
public:

	IVRenderContext() {};
	virtual ~IVRenderContext() {};

	/**
	 * Make the rendering Context active
	*/
	virtual void MakeCurrent() = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

#endif //V3D_IVRENDERCONTEXT_H
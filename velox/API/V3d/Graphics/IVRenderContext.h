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

	//TODO: bitte alle methoden im javadoc stil beschreiben, so dass jemand
	// der keine ahnung hat wofuer das ganze gut ist die klasse/methode
	// benutzen kann --sheijk
	virtual void MakeCurrent() = 0;
	//TODO: use kann weg, oder?
	virtual void Use();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

#endif //V3D_IVRENDERCONTEXT_H
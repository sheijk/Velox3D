#ifndef V3D_IVSHADER_2005_11_28_H
#define V3D_IVSHADER_2005_11_28_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/SmartPtr/VSharedPtr.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVParameter;

/**
 * Base class for shaders. A shader is the combination of a vertex and a
 * fragment program
 *
 * @author sheijk
 */
class IVShader
{
public:
	virtual ~IVShader() {}

	/**
	 * Enable shader. All geometry sent to the graphics card between Bind() and
	 * Unbind() will be processed by the shader
	 */
	virtual void Bind() = 0;

	/** Disable shader */
	virtual void Unbind() = 0;

	/** Find a named parameter. See @Parameters */
	virtual VSharedPtr<IVParameter> GetParameter(VStringParam in_strName) = 0;

	/** 
	 * Get a list of changeable parameters for the shader. Parameter values
	 * need to be applied after each Bind() (their persistence after Unbind()
	 * has been called is not guaranteed and the desired values will probably
	 * be different for different meshes
	 */
	virtual VRangeIterator<IVParameter> Parameters() = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_IVSHADER_2005_11_28_H

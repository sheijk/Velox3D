#ifndef V3D_OPENGLUTILS_2005_12_11_H
#define V3D_OPENGLUTILS_2005_12_11_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/GraphicsExceptions.h>
#include <V3d/OpenGL.h>
#include <V3d/Math/VMatrix.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/** 
 * Gets the current OpenGL matrix defined by in_Matrix and writes it ot
 * out_pMatrix
 * @parameter in_Matrix GL_MODELVIEW_MATRIX, GL_PROJECTION_MATRIX, GL_TEXTURE_MATRIX
 */
void GetGLMatrix(GLenum in_Matrix, math::VMatrix44f* out_pMatrix);

void ThrowOnGLError(VStringParam in_strFileName, vuint in_nLine, VStringParam in_strOperation);

#define V3D_GLCHECK(x) (x); if( glGetError() != GL_NO_ERROR ) ThrowOnGLError(__FILE__, __LINE__, #x);

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_OPENGLUTILS_2005_12_11_H

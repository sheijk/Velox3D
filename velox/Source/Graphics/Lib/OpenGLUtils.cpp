#include <V3d/Graphics/OpenGLUtils.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>
#include <V3d/Math/VMatrix.h>

#include <string>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

void GetGLMatrix(GLenum in_Matrix, VMatrix44f* out_pMatrix)
{
	vfloat32 matrix[16];
	glGetFloatv(in_Matrix, matrix);

	vuint index = 0;
	for(vuint column = 0; column < 4; ++column)
		for(vuint row = 0; row < 4; ++row)
		{
			out_pMatrix->Set(row, column, matrix[index]);
			++index;
		}
}

void ThrowOnGLError(VStringParam in_strFileName, vuint in_nLine, VStringParam in_strOperation)
{
	GLenum errorNo = GL_NO_ERROR;
	std::string errorLog;
	std::string lastError;

	while( (errorNo = glGetError()) != GL_NO_ERROR )
	{
		lastError = (char*) gluErrorString(errorNo);
		errorLog += lastError + "\n";
	}

	if( errorLog.size() > 0 )
	{
		vout << "(V3d) GL Errors occured: " << errorLog << vendl;
		V3D_THROWMSG(VOpenGLException, "OpenGL Error: " << lastError);
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

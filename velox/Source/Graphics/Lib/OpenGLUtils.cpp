/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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


GLint GetGeometryMode(VMeshDescription::GeometryType in_eType)
{
	switch(in_eType)
	{
	case VMeshDescription::Triangles:
		return GL_TRIANGLES;
	case VMeshDescription::TriangleFan:
		return GL_TRIANGLE_FAN;
	case VMeshDescription::TriangleStrip:
		return GL_TRIANGLE_STRIP;
	case VMeshDescription::Quads:
		return GL_QUADS;
	case VMeshDescription::QuadStrip:
		return GL_QUAD_STRIP;
	case VMeshDescription::Lines:
		return GL_LINES;
	case VMeshDescription::LineStrip:
		return GL_LINE_STRIP;
	case VMeshDescription::Points:
		return GL_POINTS;
	default:
		V3D_THROW(VException, "invalid geometry mode");
	}
}

void MakeGLMatrix(const math::VMatrix44f& mat, vfloat32* out_pGLMat)
{
	int index = 0;
	for(int col = 0; col < 4; ++col)
		for(int row = 0; row < 4; ++row)
		{
			out_pGLMat[index] = mat.Get(row, col);
			++index;            
		}
}

void SetGLMatrix(int mode, const math::VMatrix44f& mat)
{
	vfloat32 glmat[16];
	MakeGLMatrix(mat, glmat);

	glMatrixMode(mode);
	glLoadMatrixf(glmat);	
}

void MultGLMatrix(const math::VMatrix44f& mat)
{
	vfloat32 glmat[16];

	MakeGLMatrix(mat, glmat);

	glMultMatrixf(glmat);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------


#include "VOpenGLUtils.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VException.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------

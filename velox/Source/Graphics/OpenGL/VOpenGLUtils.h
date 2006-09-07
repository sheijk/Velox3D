/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VOPENGLUTILS_H
#define V3D_VOPENGLUTILS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VMeshDescription.h>

#include <v3d/Math/VMatrix.h>

#include <V3d/OpenGL.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

GLint GetGeometryMode(VMeshDescription::GeometryType in_eType);

void SetGLMatrix(int mode, const math::VMatrix44f& mat);

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VOPENGLUTILS_H


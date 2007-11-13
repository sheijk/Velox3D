/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_OPENGL_2005_02_03_H
#define V3D_OPENGL_2005_02_03_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VBuild.h>
#ifdef V3D_WIN32
#include <windows.h>
#include <glew/glew.h>
#include <glew/wglew.h>
#include <GL/gl.h>
#include <GL/GLU.h>
#else
#ifdef V3D_LX
#include <GL/glew.h>
#include <GL/glxew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#endif
//-----------------------------------------------------------------------------
#endif // V3D_OPENGL_2005_02_03_H


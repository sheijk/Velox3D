#ifndef GEOMCLIPTERRAIN_OPENGL_H_INCLUDED
#define GEOMCLIPTERRAIN_OPENGL_H_INCLUDED


/**
 * Common header to include OpenGL. Handles correct
 * sequence of includes (glew.h first) and differences
 * between platforms
 */

#ifdef __APPLE__

#include <GL/glew.h>
#include <GL/glfw.h>
#include <OpenGL/glu.h>

#else

#include <windows.h>
#include <glew/glew.h>
#include <glew/wglew.h>
#include <GL/glfw.h>
#include <GL/gl.h>
#include <GL/GLU.h>
#include <GL/glut.h>

#endif

#include <iostream>

inline void messageGLError(GLenum error) {
    std::cout << "OpenGL error(" << error << "): "
              << gluErrorString(error) << std::endl;
}

inline void printGLErrors() {
    GLenum err;
    while( (err = glGetError()) != GL_NO_ERROR ) {
        messageGLError( err );
    }
}

inline void checkGLError(const char* operation) {
    GLenum error = glGetError();

    if( error != GL_NO_ERROR )
        messageGLError( error );
}

#define GEOMCLIP_GL(x) x; checkGLError(#x);

#endif

#include "Application.h"

#include <iostream>
#include <cmath>
#include <set>

#include "OpenGL.h"

namespace {
	typedef std::set< Application* > ApplicationSet;
	ApplicationSet applications_g;
}

void Application::keyCallback(int key, int action) {
	for(ApplicationSet::iterator app = applications_g.begin();
		app != applications_g.end();
		++app)
	{
		(*app)->onKey( key, action );
	}
}

Application::Application() {
    std::cout << "Created app" << std::endl;
	applications_g.insert( this );
}

Application::~Application() {
	applications_g.erase( this );
}

extern int lookupCount;

int Application::run() {
    std::cout << "Hello, terrain" << std::endl;

    uint frameCount = 1;

    glfwInit();

    int glmajor = 0;
    int glminor = 0;
    int glrev = 0;
    
    glfwGetVersion(&glmajor, &glminor, &glrev);
    std::cout << "Glfw version: "
              << glmajor << "." << glminor
              << "." << glrev << std::endl;

	//glfwOpenWindow( 1600, 1200, 8, 8, 8, 8, 16, 8, GLFW_FULLSCREEN );
	glfwOpenWindow( 800, 600, 8, 8, 8, 8, 16, 8, GLFW_WINDOW );

    glewInit();
//     if( glewInit() != GL_TRUE ) {
//         GEOMCLIP_ERROR("Could not intialize glew");
//     }

    const GLubyte* glVersionString = glGetString(GL_VERSION);
    std::cout << "OpenGL version: " << glVersionString << std::endl;
    
    if( ! GLEW_ARB_shader_objects &&
        GLEW_ARB_vertex_shader &&
        GLEW_ARB_fragment_shader &&
        GLEW_ARB_shading_language_100 )
    {
        GEOMCLIP_ERROR("No support for GLSL");
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    double lastTime = glfwGetTime();
    double totalDuration = 0.0;
    const double minFrameDuration = 0.01;

    onInit();

	glfwSetKeyCallback( Application::keyCallback );

    const double startTime = glfwGetTime();
    
    while( ! shallExit() ) {
        double currentTime;
        do {
            currentTime = glfwGetTime();
        } while( currentTime < lastTime + minFrameDuration );
        double frameDuration = lastTime - currentTime;
        totalDuration += frameDuration;
        lastTime = currentTime;
        
        glfwPollEvents();

        update(frameDuration);
        paint();
        
        glfwSwapBuffers();
        ++frameCount;
    }

    const double endTime = glfwGetTime();

    onExit();

    const double fps = double(frameCount) / (endTime - startTime);

	std::stringstream str;
	str << "Average FPS = " << fps << std::endl;
	std::string msg = str.str();
	GCT_LOG( msg.c_str() );
	GCT_LOG( "Total lookups: " << lookupCount << ", per second: " << int(lookupCount / (endTime-startTime)) << "\n" );
    //std::cout << "Average FPS = " << fps << std::endl;

    return 0;
}

bool Application::shallExit() {
    return glfwGetKey(GLFW_KEY_ESC) == GL_TRUE;
}

void Application::paint() {
    onPaint();
}

void Application::update(float frameSeconds) {
    onUpdate(frameSeconds);
}

#include "Utils.h"
#include "OpenGL.h"
#include <fstream>
#include <algorithm>

namespace geomclip {
    template<typename T, typename STLContainer>
    bool contains(const STLContainer& container, const T& t) {
        return std::find(container.begin(), container.end(), t)
            != container.end();
    }
    
    std::string loadFile(const std::string& fileName) {
        std::ifstream file( fileName.c_str() );

        if( ! file.is_open() && ! contains(fileName, '/') ) {
            std::string resolvedFileName = "../src/" + fileName;
            file.open( resolvedFileName.c_str() );
        }

        if( file.is_open() ) {
            std::string fileContent;
        
            while( file.good() && ! file.eof() ) {
                std::string line;
                getline(file, line);
                fileContent += line + "\n";
            }

            return fileContent;
        }
        else {
            GEOMCLIP_ERROR("file '" << fileName << "' could not be opened");
        }
    }

	namespace {
		const uint colorCount = 4;
		float colors[colorCount * 4] = {
			/*
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			/*/
			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.5f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f
			/**/
		};
	}

	uint powi(uint b, uint e) {
		uint result = 1;
		while( e > 0 ) {
			result *= b;
			--e;
		}

		return result;
	}

	int nextPowerOf( int n, int start ) {
		int s = 1;

		while( s < start ) {
			s *= n;
		}

		return s;
	}

	void glColorForDetailLevel(uint level) {
		glColor3fv( colors + (4 * (level % colorCount)) );
	}

    void sendParallelLineVertices(int min, int max, float distance)
    {
        glBegin(GL_LINES);
        for(int i = min; i < max; ++i) {
            glVertex2f(-1.0f, i * distance);
            glVertex2f(1.0f, i * distance);
        }
        glEnd();
    }
    
	int mymod(int value, int mod) {
		int t1 = value / mod;
		int t2 = value - (t1 * mod);
		if( t2 >= 0 )
			return t2;
		else
			return t2 + mod;
	}

    void sendOrientationGrid() {
        const int stripeCount = 10;
        const float stripeLength = 100.0f;
        const float stripeDistance = .1f;

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glPushAttrib(GL_LINE_WIDTH);
        glLineWidth(.2f);

        glScalef(stripeLength, stripeLength, stripeLength);

        // show z = 0 plane
        glColor3f(.0f, .0f, 1.0f);
        sendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);
        glRotatef(90.0f, .0f, .0f, 1.0f);
        sendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);

        // show y = 0 plane
        glColor3f(.0f, 1.0f, .0f);
        glRotatef(90, 0, 1, 0);
        sendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);
        glRotatef(90.0f, .0f, .0f, 1.0f);
        sendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);

        // show x = 0 plane
        glColor3f(1.0f, .0f, .0f);
        glRotatef(90, 0, 1, 0);
        sendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);
        glRotatef(90.0f, .0f, .0f, 1.0f);
        sendParallelLineVertices(-stripeCount, stripeCount, stripeDistance);

        glPushAttrib(GL_POINT_SIZE);
        glPointSize(3.0f);

        glBegin(GL_POINTS);
        for(int i = -stripeCount; i < stripeCount; ++i) {
            glColor3f(0, 1, 1);
            glVertex3f(i * stripeDistance, 0, 0);

            glColor3f(1, 0, 1);
            glVertex3f(0, i * stripeDistance, 0);

            glColor3f(1, 1, 0);
            glVertex3f(0, 0, i * stripeDistance);
        }
        glColor3f(0, 0, 0);
        glVertex3f(0, 0, 0);
        glEnd();

        glPopAttrib();

        glPopAttrib();
        glPopMatrix();
    }

}

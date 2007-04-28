#include "OpenGL.h"

#include "Terrain.h"
#include "RawHeightmapSource.h"
#include "StretchedHeightmapSource.h"
#include "Application.h"
#include "Utils.h"
#include "DummyLodObjects.h"

#include <iostream>
#include <cmath>
#include <list>
#include <set>
#include <limits>

using namespace std;
using namespace geomclip;

class Controller {
public:
    virtual uint axisCount() const = 0;
    virtual float axisMovement(uint axisNum) = 0;
};

class Axis {
public:
    virtual float axisMovement() = 0;
};

// class AggregatedController : public Controller {
// public:
//     virtual uint axisCount() const {
//         return axes_.size();
//     }
    
//     virtual float axisMovement(uint axisNum) {
//         if( axisNum < axisCount() )
//             return axes_[axisNum]->axisMovement();
//         else
//             return 0.f;
//     }
    
//     AggregatedController() {
//     }
    
// private:
//     typedef std::vector<Axis*> AxisContainer;
//     AxisContainer axes_;
// };

class GlfwMouseAxis : public Axis {
public:
    enum WhichAxis { X_AXIS, Y_AXIS, WHEEL_AXIS };

    GlfwMouseAxis(WhichAxis axis) {
        axis_ = axis;
        lastPos_ = 0.f;
        movement_ = 0.f;

        instances_.insert(this);
    }

    ~GlfwMouseAxis() {
        instances_.erase(this);
    }

    /**
     * This shall be a comment..
     */
    virtual float axisMovement() {
        return movement_;
    }

    /**
     * This be documentation
     */
    void update() {
        int x = 0;
        int y = 0;

        glfwGetMousePos(&x, &y);

        int pos = 0;

        if( axis_ == X_AXIS )
            pos = x;
        else if( axis_ == Y_AXIS )
            pos = y;
        else if( axis_ == WHEEL_AXIS )
            pos = glfwGetMouseWheel();

        float fpos = pos;
        movement_ = lastPos_ - fpos;
        lastPos_ = fpos;
    }

    static void updateAll() {
        for(AxisSet::iterator it = instances_.begin();
            it != instances_.end();
            ++it)
        {
            (*it)->update();
        }
    }

private:
    typedef std::set<GlfwMouseAxis*> AxisSet;
    static AxisSet instances_;
    
    WhichAxis axis_;
    float lastPos_;
    float movement_;
};

std::set<GlfwMouseAxis*> GlfwMouseAxis::instances_;

class GlfwKeyAxis : public Axis {
public:
    GlfwKeyAxis(int incKey, int decKey) {
        increaseKey_ = incKey;
        decreaseKey_ = decKey;
        speed_ = 10.0f;
    }
    
    virtual float axisMovement() {
        float value = 0.0f;
        if( glfwGetKey(increaseKey_) == GL_TRUE )
            value += speed_;
        else if ( glfwGetKey(decreaseKey_) == GL_TRUE )
            value -= speed_;

        return value;
    }

private:
    float speed_;
    int increaseKey_;
    int decreaseKey_;
};

class DummyAxis : public Axis {
public:
    virtual float axisMovement() {
        return 0.0f;
    }
};

#define GEOMCLIP_EVERY_SECONDS_DO(MS, X)        \
    {                                           \
        static double nextTime = 0.0;           \
        if( glfwGetTime() > nextTime ) {        \
            nextTime += MS;                     \
            X;                                  \
        }                                       \
    }

#define GEOMCLIP_EVERY_SECONDS_ONCHANGE_DO(MS, X, TYPE, VAL)    \
    GEOMCLIP_EVERY_SECONDS_DO(MS,                               \
                              static TYPE lastVal = VAL;        \
                              if( VAL != lastVal ) {            \
                                  X;                            \
                                  lastVal = VAL;                \
                              })

class Button {
public:
	virtual bool isDown() const = 0;
};

class GlfwKeyButton : public Button {
	int keyId_;
public:
	GlfwKeyButton( int keyId ) {
		keyId_ = keyId;
	}

	virtual bool isDown() const {
		return glfwGetKey( keyId_ ) == GLFW_PRESS;
	}
};

class TrackballController {
public:
    TrackballController() {
        rotationDegrees_ = 0.f;
        tiltDegrees_ = 0.f;
        rotationSpeed_ = 1.0f;
        tiltSpeed_ = 1.0f;
        distance_ = 1.0f;
        zoomSpeed_ = 10.0f;
    }
    
    void setAxes(std::auto_ptr<Axis> rotAxis,
                 std::auto_ptr<Axis> tiltAxis,
                 std::auto_ptr<Axis> zoomAxis)
    {
        rotationAxis_ = rotAxis;
        tiltAxis_ = tiltAxis;
        zoomAxis_ = zoomAxis;
    }
    
    void update(float seconds) {
        if( rotationAxis_.get() != 0 )
            rotationDegrees_ += seconds * rotationSpeed_ * rotationAxis_->axisMovement();
        
        if( tiltAxis_.get() != 0 )
            tiltDegrees_ += seconds * tiltSpeed_ * tiltAxis_->axisMovement();

        if( zoomAxis_.get() != 0 )
            distance_ += seconds * zoomSpeed_ * zoomAxis_->axisMovement();

        rotationDegrees_ = fmodf(rotationDegrees_, 360.0f);
        tiltDegrees_ = std::min(90.0f, std::max(-90.0f, tiltDegrees_));
        distance_ = std::max(0.0f, distance_);

        GEOMCLIP_EVERY_SECONDS_ONCHANGE_DO(1.0f,
                                           std::cout << "distance = "
                                           << distance_ << std::endl,
                                           float, distance_)
    }

    void applyGL() {
        glTranslatef(0.f, 0.f, - pow(2.0f, distance_));
        
        glRotatef(tiltDegrees_, 1.0f, 0.0f, 0.0f);
        glRotatef(rotationDegrees_, 0.f, 1.f, 0.f);
    }

    void setSpeed(float speed) {
        rotationSpeed_ = speed;
        tiltSpeed_ = speed;
    }

    float getRotationDegrees() const { return rotationDegrees_; }
    void setRotationDegrees(float newval) { rotationDegrees_ = newval; }

    float getTiltDegrees() const { return tiltDegrees_; }
    void setTiltDegrees(float newval) { tiltDegrees_ = newval; }

    Orientation getOrientation() const {
        const float rotRads = rotationDegrees_ * M_PI / 180.0f;
        const float tiltRads = tiltDegrees_ * M_PI / 180.0f;
        const float dist = pow(2.0f, distance_);
        
        float x = sin( rotRads ) * cos( tiltRads ) * dist;
        float z = cos( rotRads ) * cos( tiltRads ) * dist;
        float y = sin( tiltRads ) * dist;

        return Orientation(x, y, z,
                           0.f, 0.f, 0.f,
                           0.f, 1.f, 0.f);
    }
    
private:
    float rotationDegrees_;
    float rotationSpeed_;
    float tiltDegrees_;
    float tiltSpeed_;
    float distance_;
    float zoomSpeed_;
    
    std::auto_ptr<Axis> rotationAxis_;
    std::auto_ptr<Axis> tiltAxis_;
    std::auto_ptr<Axis> zoomAxis_;
};

class FPSController {
public:
    FPSController() {
        moveSpeed_ = 10.0f;
        rotationSpeed_ = 4.0f;
        
        orientation_.pos = Vector3f( 0.f, 0.f, 0.f );
        orientation_.viewDir = Vector3f( 0.f, 0.f, 1.f );
        orientation_.upDir = Vector3f( 0.f, 1.f, 0.f );
        
        xrot_ = 0.0f;
        yrot_ = 0.0f;
        zrot_ = 0.0f;
    }
    
    void setAxes(std::auto_ptr<Axis> forwardAxis,
                 std::auto_ptr<Axis> sideAxis,
                 std::auto_ptr<Axis> upAxis,
                 std::auto_ptr<Axis> xRotAxis,
                 std::auto_ptr<Axis> yRotAxis,
                 std::auto_ptr<Axis> zRotAxis)
    {
        forwardAxis_ = forwardAxis;
        sideAxis_ = sideAxis;
        upAxis_ = upAxis;
        yRotAxis_ = yRotAxis;
        xRotAxis_ = xRotAxis;
        zRotAxis_ = zRotAxis;
    }

    void update(float seconds) {
        Vector3f right;
        cross( &right, orientation_.upDir, orientation_.viewDir );
        
        Vector3f movement(0.f, 0.f, 0.f);

        if( sideAxis_.get() != 0 )
            movement.x = sideAxis_->axisMovement() * moveSpeed_ * seconds;
        if( upAxis_.get() != 0 )
            movement.y = upAxis_->axisMovement() * moveSpeed_ * seconds;
        if( forwardAxis_.get() != 0 )
            movement.z = forwardAxis_->axisMovement() * moveSpeed_ * seconds;

        orientation_.pos += right * movement.x;
        orientation_.pos += orientation_.upDir * movement.y;
        orientation_.pos += orientation_.viewDir * movement.z;

        float drx = 0.f;
        float dry = 0.f;
        float drz = 0.f;
        
        if( xRotAxis_.get() != 0 )
            drx = xRotAxis_->axisMovement() * rotationSpeed_ * seconds;
        if( yRotAxis_.get() != 0 )
            dry = yRotAxis_->axisMovement() * rotationSpeed_ * seconds;
        if( zRotAxis_.get() != 0 )
            drz = zRotAxis_->axisMovement() * rotationSpeed_ * seconds;

        xrot_ += drx;
        yrot_ += dry;
        zrot_ += drz;

        rotate( &orientation_, -drx, right );
        rotate( &orientation_, -dry, orientation_.upDir );
        rotate( &orientation_, -drz, orientation_.viewDir );
        orientation_.normalize();
    }

    void applyGL() const {
        Vector3f p = orientation_.pos;
        Vector3f l = p + orientation_.viewDir;
        Vector3f u = orientation_.upDir;
        
        gluLookAt(p.x, p.y, p.z,
                  l.x, l.y, l.z,
                  u.x, u.y, u.z);
                  
//         glRotatef(xrot_, 1.0f, 0.0f, 0.0f);
//         glRotatef(yrot_, 0.0f, 1.0f, 0.0f);
//         glTranslatef(orientation_.pos.x, orientation_.pos.y, orientation_.pos.z);
    }

    Orientation getOrientation() const { return orientation_; }
    
	void setPosition(const geomclip::Vector3f& newPos) {
		orientation_.pos = newPos;
	}

	void scaleSpeed( float factor ) {
		moveSpeed_ *= factor;
	}
private:
    Orientation orientation_;
    float xrot_;
    float yrot_;
    float zrot_;
    float moveSpeed_;
    float rotationSpeed_;
    
    std::auto_ptr<Axis> forwardAxis_;
    std::auto_ptr<Axis> sideAxis_;
    std::auto_ptr<Axis> upAxis_;
    
    std::auto_ptr<Axis> yRotAxis_;
    std::auto_ptr<Axis> xRotAxis_;
    std::auto_ptr<Axis> zRotAxis_;
};

void glVertex(const Vector3f& vec) {
    glVertex3f( vec.x, vec.y, vec.z );
}

class TerrainApp : public Application {
private:
    float totalDuration_;
	Terrain terrain_;
    TrackballController controller_;
    FPSController fpsController_;
	bool tellCameraPosition_;

public:
    TerrainApp() {
        totalDuration_ = .0f;
        controller_.setAxes(
            std::auto_ptr<Axis>(new GlfwMouseAxis(GlfwMouseAxis::X_AXIS)),
            std::auto_ptr<Axis>(new GlfwMouseAxis(GlfwMouseAxis::Y_AXIS)),
            std::auto_ptr<Axis>(new GlfwMouseAxis(GlfwMouseAxis::WHEEL_AXIS)));

        fpsController_.setAxes(
            std::auto_ptr<Axis>(new GlfwKeyAxis('S', 'W')),
            std::auto_ptr<Axis>(new GlfwKeyAxis('D', 'A')),
            std::auto_ptr<Axis>(new GlfwKeyAxis('F', 'R')),
            
            std::auto_ptr<Axis>(new GlfwKeyAxis(GLFW_KEY_UP, GLFW_KEY_DOWN)),
            std::auto_ptr<Axis>(new GlfwKeyAxis(GLFW_KEY_LEFT, GLFW_KEY_RIGHT)),
            std::auto_ptr<Axis>(new GlfwKeyAxis('E', 'Q')));

		tellCameraPosition_ = true;
    }

private:
	geomclip::HoleFillers holeFillers_;

	void sendLine(float xr, float yg, float zb) {
        glColor3f(xr, yg, zb);
        glVertex3f(.0f, .0f, .0f);
        glVertex3f(xr, yg, zb);
    }

    void paintAxes() {
        glPushMatrix();
        glScalef(10.0f, 10.0f, 10.0f);
        glPushAttrib(GL_LIGHTING);
        glDisable(GL_LIGHTING);
        
        glBegin(GL_LINES);
        sendLine(1.0f, .0f, .0f);
        sendLine(.0f, 1.0f, .0f);
        sendLine(.0f, .0f, 1.0f);
        glEnd();

        glPopAttrib();
        glPopMatrix();
    }

	void sendPlaneXZ(float size) {
		glBegin( GL_QUADS );
		glColor3f( 1.f, 1.f, 1.f );
		glNormal3f( 0.f, 1.f, 0.f );
		glVertex3f( -size, 0.f, -size );
		glVertex3f( -size, 0.f, size );
		glVertex3f( size, 0.f, size );
		glVertex3f( size, 0.f, -size );
		glEnd();
	}

    virtual void onPaint() {
        //double brightness = 0.0;
        //glClearColor(brightness, brightness, brightness, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

//         controller_.applyGL();
        fpsController_.applyGL();

		//glEnable( GL_LIGHTING );
		//glEnable( GL_LIGHT0 );
		//GLfloat lightPos[] = { sin(totalDuration_), 1.0f, 0.0f, 0.0f };
		GLfloat lightPos[] = { 50.0f, 100.0f, 50.0f, 0.0f };
		GLfloat lightAmbient[] = { .2f, .2f, .2f, 1.0f };
		GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightfv( GL_LIGHT0, GL_POSITION, lightPos );
		glLightfv( GL_LIGHT0, GL_AMBIENT, lightAmbient );
		glLightfv( GL_LIGHT0, GL_DIFFUSE, lightDiffuse );

		holeFillers_.render( &terrain_ );

        terrain_.render();

		glPushMatrix();
		glTranslatef( 100.0f, 20.0f, 100.0f );
		glutSolidSphere( 20.0f, 20, 20 );
		glPopMatrix();

		sendOrientationGrid();
		paintAxes();

        printGLErrors();
    }

    virtual void onUpdate(float frameSeconds) {
        totalDuration_ += frameSeconds;
        GlfwMouseAxis::updateAll();
        controller_.update( frameSeconds );

        fpsController_.update( frameSeconds );

		if( tellCameraPosition_ ) {
			terrain_.tellCamera( fpsController_.getOrientation() );
		}
        terrain_.update( frameSeconds );
    }

    virtual void onInit() {
		GCT_PRINT( 
			"\nKeyboard shortcuts:\n" <<
			"--------------------\n"
			<< "a,s,d,w,f,r - move around\n"
			<< "Cursor keys - rotate\n"
			<< "1,2,3 - Filled / Wireframes / Points\n"
			<< "4,5 - White / colors\n"
			<< "Tab - freeze lod region's positions\n");
			
		glClearColor( 0.2f, 0.3f, .8f, 1.0f );

		glEnable( GL_NORMALIZE );

        glfwDisable(GLFW_MOUSE_CURSOR);
        controller_.setSpeed(10.0f);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, 1.0f, 1.0f, 50000.0f);

		HeightmapSource* heightmapSource =
			//new StretchedHeightmapSource( 100.0f,
			//	"../nepal_6000_16.raw", 6000, 16, 150000.0f,
			//	RawHeightmapSource::BigEndian );
			new StretchedHeightmapSource( 10.0f,
					"../volcanic_1025_16.raw", 1025, 16, 1500.0f, 
					RawHeightmapSource::LittleEndian );

		//std::auto_ptr<HeightmapSource> heightmapSource;
        terrain_.init( heightmapSource );

		std::vector< Rect<int> > holes;
		holes.push_back( Rect<int>(100, 100, 120, 120) );
		holes.push_back( Rect<int>(150, 150, 170, 450) );

		const uint holesSize = holes.size();
		for( uint holeNum = 0; holeNum < holesSize; ++holeNum ) {
			terrain_.addHole( holes[holeNum] );
			holeFillers_.addLodRegion( heightmapSource, holes[holeNum] );
		}

        controller_.setRotationDegrees( 135.0f );

		fpsController_.setPosition(vector3f(0.f, 50.f, 0.f));
    }

	virtual void onKey(int keyId, int action) {
		if( action == GLFW_RELEASE ) {
			if( keyId == GLFW_KEY_TAB ) {
				tellCameraPosition_ = ! tellCameraPosition_;
			}
			else if( keyId == GLFW_KEY_F11 ) {
				std::cout << "Reloading height data" << std::endl;

				terrain_.invalidate();
			}
			else if( keyId == GLFW_KEY_LCTRL ) {
				fpsController_.scaleSpeed( 0.5f );
			}
			else if( keyId == GLFW_KEY_LSHIFT ) {
				fpsController_.scaleSpeed( 2.0f );
			}
		}
	}
};

int main() {
    TerrainApp app;
    return app.run();
}

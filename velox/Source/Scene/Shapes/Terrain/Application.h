#ifndef APPLICATION_H_033820_INCLUDED
#define APPLICATION_H_033820_INCLUDED

#include "Types.h"

/**
 * Base class for applications. Derive subclass and put
 * MyApp app;
 * app.run();
 * into a .cpp file in your program
 */
class Application {
public:
    
    /**
     * Run this application until this->isExitCalled()
     * returns true
     */
    int run();
    
    /**
     * @see Application::onPaint
     */
    void paint();
    
    /**
     * @see onUpdate
     */
    void update(float frameSeconds);

 private:
    /**
     * Application should paint itself
     */
    virtual void onPaint() = 0;

	/**
	 * @param keId a constant like GLFW_KEY_SPACE or 'A'
	 * @param action GLFW_PRESS or GLFW_RELEASED
	 */
	virtual void onKey(int keyId, int action) {}
    
    /**
     * Update app logic
     * @param frameSeconds Seconds since last update call
     */
    virtual void onUpdate(float frameSeconds) = 0;

    /**
     * Will be called once in run() before the main loop is entered
     */
    virtual void onInit() {}

    /**
     * Will be called once in run() after the main loop exited
     */
    virtual void onExit() {}

    /**
     * Override if you don't want to quit on Escape key press
     */
    virtual bool shallExit();

	static void keyCallback(int keyId, int action);
protected:
    Application();
    virtual ~Application();
};

#endif

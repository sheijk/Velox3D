#ifndef V3D_EXAMPLEAPP_H
#define V3D_EXAMPLEAPP_H
//-----------------------------------------------------------------------------
#include "kernel\IVApplication.h"
#include "kernel\objreg\VNamedObject.h"
//-----------------------------------------------------------------------------

/**
 * An example application. Uses the example service
 */
class VExampleApp : public IVApplication, public VNamedObject
{
public:
	VExampleApp();
	virtual ~VExampleApp();

public:
	virtual int Main();
};

//-----------------------------------------------------------------------------
#endif // V3D_EXAMPLEAPP_H
#ifndef V3D_VEXAMPLESERVICE_H
#define V3D_VEXAMPLESERVICE_H
//-----------------------------------------------------------------------------
#include "kernel\objreg\VNamedObject.h"
#include "IVExampleService.h"

/**
 * A service which implements the example interface
 */
class VExampleService : public IVExampleService
{
public:
	VExampleService();
	virtual ~VExampleService();

public:
	virtual vint GiveMeFive();
};

//-----------------------------------------------------------------------------
#endif // V3D_VEXAMPLESERVICE_H

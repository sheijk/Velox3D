#ifndef V3D_VEXAMPLESERVICE_H
#define V3D_VEXAMPLESERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VNamedObject.h>
#include <v3d/ExampleService/IVExampleService.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace example {
//-----------------------------------------------------------------------------

/**
 * A service which implements the example interface
 */
class VExampleService : public IVExampleService
{
public:
	VExampleService(VStringParam in_strName);
	virtual ~VExampleService();
public:
	virtual vint GiveMeFive();
	
};

//-----------------------------------------------------------------------------
} // example 
} // v3d
//-----------------------------------------------------------------------------
#endif // V3D_VEXAMPLESERVICE_H

#ifndef V3D_EXAMPLEAPP_H
#define V3D_EXAMPLEAPP_H
//-----------------------------------------------------------------------------
#include <v3d/Core/IVApplication.h>
#include <v3d/Core/VNamedObject.h>
#include <V3d/Console/IVConsoleService.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace example {
//-----------------------------------------------------------------------------

/**
 * An example application. Uses the example service
 */
class VExampleApp : public IVApplication, public VNamedObject
{
public:
	VExampleApp(VStringParam in_strName);
	virtual ~VExampleApp();

	virtual int Main();

private:

	console::IVConsoleSerivce* m_Console;
	
};

//-----------------------------------------------------------------------------
} // namespace example
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_EXAMPLEAPP_H
#ifndef V3D_EXAMPLEAPP_H
#define V3D_EXAMPLEAPP_H
//-----------------------------------------------------------------------------
#include <v3d/Core/IVApplication.h>
#include <v3d/Core/VNamedObject.h>
#include <V3d/Console/IVConsoleService.h>

#include <v3d/Graphics/VCamera.h>
#include <v3d/Graphics/IVDevice.h>
#include <v3d/Input/IVInputManager.h>
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
	void QueryButtons(input::IVInputManager* in_pInputManager);

	void MoveCamera(graphics::VCamera* in_pCamera);

	graphics::IVDevice* m_pDevice;

	console::IVConsoleSerivce* m_Console;

	input::IVButton* m_pEscapeButton;
	input::IVButton* m_pUpButton;
	input::IVButton* m_pDownButton;
	input::IVButton* m_pLeftButton;
	input::IVButton* m_pRightButton;

	input::IVButton* m_pLeftMouseButton;
	input::IVButton* m_pRightMouseButton;
};

//-----------------------------------------------------------------------------
} // namespace example
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_EXAMPLEAPP_H
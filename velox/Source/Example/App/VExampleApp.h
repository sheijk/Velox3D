#ifndef V3D_EXAMPLEAPP_H
#define V3D_EXAMPLEAPP_H
//-----------------------------------------------------------------------------
#include <v3d/Core/IVApplication.h>
#include <v3d/Core/VNamedObject.h>
#include <V3d/Console/IVConsoleService.h>

#include <V3dLib/Graphics/Misc/VCamera.h>
#include <v3d/Graphics/IVDevice.h>
#include <v3d/Input/IVInputManager.h>

#include <V3dLib/BoostSignals.h>

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

	void MoveCamera(v3d::graphics::VCamera* in_pCamera);

	graphics::IVDevice* m_pDevice;
	updater::IVUpdateManager* m_pUpdateManager;

	console::IVConsoleService* m_Console;
	input::IVKeyboardDevice* m_pKeyboardDevice;
	input::IVMouseDevice* m_pMouseDevice;

	input::IVButton* m_pEscapeButton;
	input::IVButton* m_pUpButton;
	input::IVButton* m_pDownButton;
	input::IVButton* m_pLeftButton;
	input::IVButton* m_pRightButton;

	input::IVButton* m_pLeftMouseButton;
	input::IVButton* m_pRightMouseButton;
	input::IVRelativeAxis* m_pMouseXAxis;
	input::IVRelativeAxis* m_pMouseYAxis;
};

//-----------------------------------------------------------------------------
} // namespace example
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_EXAMPLEAPP_H
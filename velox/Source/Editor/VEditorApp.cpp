#include "VEditorApp.h"
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>

#include <v3d/Core/SmartPtr/VGuards.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>

#include <V3d/System.h>
#include <V3d/Updater.h>
#include <V3d/Core/Wrappers/VSTLDerefIteratorPol.h>

#include <v3d/Graphics.h>
#include <V3dLib/Graphics.h>
#include <v3d/Window.h>
#include <V3dLib/Math.h>

#include <V3dLib/Graphics/Renderers/Terrain/VTerrainRenderer.h>

#include <wx/wx.h>
#include <wx/minifram.h>
#include <wx/listbox.h>

#include "Utils/VPrintAction.h"
#include "Controls/VRenderFrame.h"

#include <V3dLib/Graphics/Geometry.h>
#include <V3dLib/Graphics/Misc/VSimpleDrawList.h>
#include <V3dLib/Math.h>

#include "TerrainTex/VTerrainTexDocClass.h"
#include "TerrainTex/VTextureStageSetupFrame.h"

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/splash.h>
//-----------------------------------------------------------------------------
#include "../../Workspace/blub.h"
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

wxWindow* GetRootWindow(wxWindow* in_pWin)
{
	wxWindow* parent = in_pWin->GetParent();
	if( parent == 0 )
	{
		return in_pWin;
	}
	else
	{
		return GetRootWindow(parent);
	}
}

VEditorApp::VEditorApp() : VNamedObject("main", 0)
{
	m_bAllowNewPlugins = true;
}

void* GetDesktopHandle();

vint VEditorApp::Main()
{
	using namespace graphics;
	using namespace math;

	VCamera cam;

	vout << "Velox3D proudly presents: the editor!" << vendl;

	// no plugin registering at runtime
	m_bAllowNewPlugins = false;

	// create the main window
	VEditorFrame* pFrame = new VEditorFrame(m_Plugins);

	VTerrainTexDocClass texgenDocClass;
	pFrame->RegisterDocumentClass(texgenDocClass);

	VServicePtr<system::IVSystemManager> pSystem;
	VServicePtr<v3d::updater::IVUpdateManager> pUpdater;

	//using v3d::window::IVWindowManager;

	//VServicePtr<v3d::window::IVWindowManager> pWindowManager;

	//void* pDesktop;

	//v3d::graphics::VDisplaySettings settings;
	//settings.m_iWidth = 400;
	//settings.m_iHeight = 300;

	//{
	//	wxFrame* splash = new wxFrame(
	//		0,
	//		-1,
	//		"invisible splash screen",
	//		wxPoint(0,0),
	//		wxSize(settings.m_iWidth, settings.m_iHeight),
	//		wxSTAY_ON_TOP | wxFRAME_NO_TASKBAR
	//		);

	//	splash->Show(true);
	//	splash->CenterOnScreen();

	//	//pDesktop = GetDesktopHandle();
	//	pDesktop = (void*)splash->GetHandle();
	//}

	//V3D_ASSERT(pDesktop != 0);

	//IVWindowManager::GraphicsDevicePtr pDevice =
	//	pWindowManager->CreateGraphicsDevice(
	//		settings, 
	//		pDesktop
	//		//(void*)pDesktop->GetHandle()
	//		);

	//cam.RotateZ(-45);
	//cam.RotateX(-45);
	////cam.RotateX(90);
	//cam.MoveForward(-20);
	//pDevice->SetMatrix(IVDevice::ViewMatrix, cam.TransformMatrix());

	//VVeloxCubeMesh cube;
	//IVDevice::MeshHandle hMesh = BuildMesh(
	//	*pDevice, cube, cube.MaterialDescription());

	//math::VMatrix44f matrix;
	//math::SetScale(matrix, 5);

	pUpdater->Start();
	pSystem->SetStatus(true);
	while(pSystem->GetStatus())
	{
		//pDevice->BeginScene();

		//pDevice->SetMatrix(IVDevice::ModelMatrix, matrix);
		//ApplyMaterial(*pDevice, & hMesh->GetMaterial());
		//pDevice->RenderMesh(hMesh);

		//pDevice->EndScene();

		pUpdater->StartNextFrame();
	}
	pUpdater->Stop();

	//pDevice.DropOwnership();

//	pFrame->Destroy();

	return 666;
}

void VEditorApp::RegisterTool(IVTool& in_Tool)
{
	if( m_bAllowNewPlugins )
	{
		m_Plugins.push_back(&in_Tool);
	}
	else
	{
		vout << "tool \"" << in_Tool.GetName() << "\" registered late" << vendl;
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------

#include <windows.h>

namespace v3d { namespace editor {
void* GetDesktopHandle()
{
	return GetDesktopWindow();
}
}}

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

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/splash.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//wxWindow* GetRootWindow(wxWindow* in_pWin)
//{
//	wxWindow* parent = in_pWin->GetParent();
//	if( parent == 0 )
//	{
//		return in_pWin;
//	}
//	else
//	{
//		return GetRootWindow(parent);
//	}
//}

VEditorApp::VEditorApp() : VNamedObject("main", 0)
{
	m_bAllowNewPlugins = true;
}

//void* GetDesktopHandle();

using namespace v3d;
using namespace v3d::graphics;
using namespace v3d::window;
using namespace v3d::system;
using namespace v3d::updater;
using namespace v3d::image;

/*
vint VEditorApp::Main()
{
	vout << "lalelu" << vendl;

	VServicePtr<IVSystemManager> pSystem;
	VServicePtr<IVWindowManager> pWindowManager;
	VServicePtr<IVUpdateManager> pUpdater;
	VServicePtr<IVImageFactory> pImageFactory;

	IVWindowManager::IVWindowPtr pWindow(pWindowManager->QueryWindow("."));
	IVDevice& device(pWindow->QueryGraphicsDevice());

	VQuadMesh<graphics::VColoredTextureVertex> quad;
	quad.GenerateCoordinates();
	quad.GenerateTexCoords();

	quad.GetVertexBuffer()[0].color = VColor4f(1, 0, 0, 1);
	quad.GetVertexBuffer()[1].color = VColor4f(0, 1, 0, 1);
	quad.GetVertexBuffer()[2].color = VColor4f(0, 0, 1, 1);
	quad.GetVertexBuffer()[3].color = VColor4f(1, 1, 1, 1);

	IVImageFactory::ImagePtr pImage = pImageFactory->CreateImage(
		"/data/worldmap.jpg");

	VImage& image(*pImage);

	VMaterialDescription mat;
	mat.AddTexture(graphics::CreateTextureRef(device, *pImage));

	IVDevice::MeshHandle hMesh = BuildMesh(device, quad, mat);

	VCamera cam;

	cam.MoveForward(-2);
	device.SetMatrix(IVDevice::ViewMatrix, cam.TransformMatrix());

	pUpdater->Start();
	pSystem->SetStatus(true);
	while(pSystem->GetStatus())
	{
		device.BeginScene();

		ApplyMaterial(device, & hMesh->GetMaterial());
		device.RenderMesh(hMesh);

		device.EndScene();

		pUpdater->StartNextFrame();
	}
	pUpdater->Stop();

	return 1;
}

/*/

//vint VEditorApp::Main()
//{
//	vout << "Velox3D proudly presents: the editor!" << vendl;
//
//	VServicePtr<system::IVSystemManager> pSystem;
//	VServicePtr<v3d::updater::IVUpdateManager> pUpdater;
//	VServicePtr<v3d::window::IVWindowManager> pWindowManager;
//
//	window::IVWindowManager::IVWindowPtr pWindow = pWindowManager->QueryWindow("blub");
//	graphics::IVDevice* pDevice = & pWindow->QueryGraphicsDevice();
//
//	graphics::VQuadMesh<graphics::VSimpleVertex> quad;
//	quad.GenerateCoordinates();
//
//	graphics::VMaterialDescription mat;
//	mat = graphics::BuildTextureMaterial(pDevice, "/data/moon.jpg");
//
//	graphics::IVDevice::MeshHandle hMesh = graphics::BuildMesh(
//		*pDevice, quad, mat);
//
//	pUpdater->Start();
//	pSystem->SetStatus(true);
//	while(pSystem->GetStatus())
//	{
//		pDevice->BeginScene();
//
//		//pDevice->SetMatrix(IVDevice::ModelMatrix, matrix);
//		graphics::ApplyMaterial(*pDevice, & hMesh->GetMaterial());
//		pDevice->RenderMesh(hMesh);
//
//		pDevice->EndScene();
//
//		pUpdater->StartNextFrame();
//	}
//	pUpdater->Stop();
//
//	//pDevice.DropOwnership();
//
////	pFrame->Destroy();
//
//	return 666;
//}

vint VEditorApp::Main()
{
	using namespace graphics;
	using namespace math;

	//VCamera cam;

	vout << "Velox3D proudly presents: the editor!" << vendl;

	// no plugin registering at runtime
	m_bAllowNewPlugins = false;

	// create the main window
	VEditorFrame* pFrame = new VEditorFrame(m_Plugins);

	VTerrainTexDocClass texgenDocClass;

	//VTerrainTexDocClass texgenDocClass;
	pFrame->RegisterDocumentClass(texgenDocClass);

	VServicePtr<system::IVSystemManager> pSystem;
	VServicePtr<v3d::updater::IVUpdateManager> pUpdater;
	//VServicePtr<v3d::window::IVWindowManager> pWindowManager;

	//v3d::graphics::VDisplaySettings settings;
	//settings.m_iWidth = 400;
	//settings.m_iHeight = 300;

	//window::IVWindowManager::IVWindowPtr pWindow =
	//	pWindowManager->QueryWindow("blub");

	//graphics::IVDevice* pDevice = & pWindow->QueryGraphicsDevice();

	//graphics::VQuadMesh<graphics::VSimpleVertex> quad;
	//quad.GenerateCoordinates();

	//graphics::VMaterialDescription mat;
	//mat = graphics::BuildTextureMaterial(pDevice, "/data/moon.jpg");

	//graphics::IVDevice::MeshHandle hMesh = graphics::BuildMesh(
	//	*pDevice, quad, mat);

	pUpdater->Start();
	pSystem->SetStatus(true);
	while(pSystem->GetStatus())
	{
		pUpdater->StartNextFrame();
	}
	pUpdater->Stop();

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

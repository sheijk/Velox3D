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
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

VEditorApp::VEditorApp() : VNamedObject("main", 0)
{
	m_bAllowNewPlugins = true;
}

vint VEditorApp::Main()
{
	using namespace graphics;
	using namespace math;

	VCamera cam;

	//VTestPlugin testPlugin;
	//RegisterTool(testPlugin);

	//VTerrainTexGenEditor terrTexEdit;
	//RegisterEditor(terrTexEdit);
	//m_pActiveEditor = &terrTexEdit;

	//VCameraTool cameraPlugin(cam);
	//RegisterTool(cameraPlugin);

	VTerrainTexDocClass texgenDocClass;

	vout << "Velox3D proudly presents: the editor!" << vendl;

	// no plugin registering at runtime
	m_bAllowNewPlugins = false;

	// create the main window
	VEditorFrame* pFrame = new VEditorFrame(m_Plugins);
	pFrame->RegisterDocumentClass(texgenDocClass);
	VTextureStageSetupFrame* pTexStageFrame = 
		new VTextureStageSetupFrame(pFrame);
	pFrame->RegisterTool(*pTexStageFrame);

	VServicePtr<system::IVSystemManager> pSystem;
	VServicePtr<v3d::updater::IVUpdateManager> pUpdater;

	//graphics::IVDevice& device(testPlugin.GetDevice());

	//VSimpleDrawList drawList(device);

	//vout << vendl << "Loading terrain...";
	//VTerrainRenderer::TerrainRendererPtr pTerrain = 
	//	VTerrainRenderer::CreateFromRawFile(
	//		"/data/hills.raw", device);
	//pTerrain->CreateMeshes();
	//vout << "done" << vendl;

	//cam.MoveForward(-15);
	//cam.RotateZ(-45);
	//cam.RotateX(-55);
	//cam.MoveForward(5);
	//device.SetMatrix(IVDevice::ViewMatrix, cam.TransformMatrix());

	pUpdater->Start();
	pSystem->SetStatus(true);
	while(pSystem->GetStatus())
	{
		//device.BeginScene();
		//device.SetMatrix(IVDevice::ViewMatrix, cam.TransformMatrix());

		//drawList.Render();
		//pTerrain->Update(cam);
		//pTerrain->Render();

		//device.EndScene();

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

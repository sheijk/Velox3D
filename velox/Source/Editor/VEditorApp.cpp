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

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d;

class VPrintAction : public IVAction
{
public:
	VPrintAction(VStringParam in_strMessage)
	{
		m_Message = in_strMessage;
	}

	virtual VStringRetVal GetName()
	{
		return "print test";
	}
	
	virtual void Execute()
	{
		vout << m_Message.AsCString();
	}

private:
	VString m_Message;
};

class VRenderToolWindow : public wxMiniFrame
{
public:
	VRenderToolWindow(wxWindow* in_pParent) : 
	  wxMiniFrame(
		  in_pParent,
		  -1, 
		  "demo plugin",
          wxPoint(0, 0),
		  wxSize(640, 480),
		  wxTINY_CAPTION_HORIZ | wxFRAME_FLOAT_ON_PARENT | wxFRAME_NO_TASKBAR
		  )
	{
		CenterOnParent();

		VServicePtr<window::IVWindowManager> pWinManager;

		graphics::VDisplaySettings settings;
		settings.m_bFullscreen = false;
		settings.m_sAPIType = "OpenGL";
		settings.m_iWidth = GetSize().GetWidth();
		settings.m_iHeight = GetSize().GetHeight();

		m_pDevice = pWinManager->CreateGraphicsDevice(settings, (void*)GetHandle());
	}

	graphics::IVDevice& QueryDevice()
	{
		return *m_pDevice;
	}

private:
	window::IVWindowManager::GraphicsDevicePtr m_pDevice;
};

class VTestPlugin : public IVPlugin
{
	typedef VPointer<IVAction>::SharedPtr ActionPtr;
	typedef std::vector<ActionPtr> ActionList;
	typedef VSTLDerefIteratorPol<ActionList::iterator, IVAction> ActionIterPol;

public:
	VTestPlugin()
		:
		m_pWindow(0)
	{
		ActionPtr pAction(new VPrintAction("this is the test action\n"));
		m_Actions.push_back(pAction);
	}

	ActionIterator ActionsBegin() 
	{
		return ActionIterator(new ActionIterPol(m_Actions.begin()));
	}

	ActionIterator ActionsEnd() 
	{
		return ActionIterator(new ActionIterPol(m_Actions.end()));
	}

	VStringRetVal GetName()
	{
		return "Test";
	}

	virtual void Enable(wxWindow* in_pParent)
	{
		if(! m_pWindow)
		{
			m_pWindow = new VRenderToolWindow(in_pParent);
			m_pWindow->Show(true);
		}
	}

	graphics::IVDevice& GetDevice()
	{
		return m_pWindow->QueryDevice();
	}

private:
	ActionList m_Actions;
	VRenderToolWindow* m_pWindow;
};

VEditorApp::VEditorApp() : VNamedObject("main", 0)
{
	m_bAllowNewPlugins = true;
}

vint VEditorApp::Main()
{
	using namespace graphics;
	using namespace math;

	VTestPlugin testPlugin;

	RegisterPlugin(testPlugin);

	vout << "Velox3D proudly presents: the editor!" << vendl;

	// no plugin registering at runtime
	m_bAllowNewPlugins = false;

	// create the main window
	VEditorFrame* pFrame = new VEditorFrame(m_Plugins);

	VServicePtr<system::IVSystemManager> pSystem;
	VServicePtr<v3d::updater::IVUpdateManager> pUpdater;

	graphics::IVDevice& device(testPlugin.GetDevice());

	VPolarSphereMesh<VSimpleVertex> sphere(10, 10);
	sphere.GenerateCoordinates();

	VMaterialDescription mat;
	mat.frontPolyMode = VMaterialDescription::Line;
	mat.backPolyMode = VMaterialDescription::Line;
	mat.defaultColor = VColor4f(0.0f, 1.0f, 0.2f, 1.0f);

	IVDevice::MeshHandle hMesh = BuildMesh(device, sphere, mat);

	VSimpleDrawList drawList(device);

	drawList.Add(VModel(hMesh, IdentityPtr()));

	vout << vendl << "Loading terrain...";
	VTerrainRenderer::TerrainRendererPtr pTerrain = 
		VTerrainRenderer::CreateFromRawFile(
			"/data/hills.raw", device);
	pTerrain->CreateMeshes();
	vout << "done" << vendl;

	VCamera cam;
	cam.MoveForward(-15);
	cam.RotateZ(-45);
	cam.RotateX(-55);
	cam.MoveForward(5);
	device.SetMatrix(IVDevice::ViewMatrix, cam.TransformMatrix());

	pUpdater->Start();
	pSystem->SetStatus(true);
	while(pSystem->GetStatus())
	{
		device.BeginScene();

		drawList.Render();
		pTerrain->Update(cam);
		pTerrain->Render();

		device.EndScene();

		pUpdater->StartNextFrame();
	}
	pUpdater->Stop();

//	pFrame->Destroy();

	return 666;
}

void VEditorApp::RegisterPlugin(IVPlugin& in_Plugin)
{
	if( m_bAllowNewPlugins )
	{
		m_Plugins.push_back(&in_Plugin);
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------

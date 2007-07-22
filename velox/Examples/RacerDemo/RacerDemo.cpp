#include <V3d/Core.h>
#include <V3d/Updater.h>
#include <V3d/System.h>
#include <V3d/Graphics.h>
#include <V3d/Window.h>
#include <V3d/Math.h>
#include <V3d/Input.h>
#include <V3d/Resource.h>
#include <V3d/Scene.h>
#include <V3d/Entity.h>
#include <V3d/Property.h>
#include <V3d/Utils/VCameraPart.h>
#include <V3d/Utils/VTrackballPart.h>
#include <V3d/Utils/VFPSMoverPart.h>
#include <V3d/Utils/VCircleMoverPart.h>
#include <V3d/Vfs.h>
#include <V3d/Xml.h>
#include <V3d/Physics/VPhysics.h>
#include <V3d/Utils/VFrameCounter.h>

#include <sstream>
#include <string>

#include <windows.h>
#include <glew/glew.h>
#include <glew/wglew.h>
#include <GL/gl.h>
#include <GL/glfw.h>

#pragma comment(lib, "glfw.lib")

using namespace v3d;
using namespace v3d::updater;
using namespace v3d::system;
using namespace v3d::graphics;
using namespace v3d::window;
using namespace v3d::math;
using namespace v3d::input;
using namespace v3d::resource;
using namespace v3d::scene;
using namespace v3d::entity;
using namespace v3d::utils;
using namespace v3d::xml;
using namespace v3d::physics;

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d;
//-----------------------------------------------------------------------------

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 1024;
const std::string APP_NAME = "RacerDemo";

const VColor4f fogColor(.6f, .4f, .4f, 1.0f);
//-----------------------------------------------------------------------------
class TimeTest
{
public:

  TimeTest()
  {
	lastTime = 0;
	deltaTime = 0;
  }

  void UpdateTime()
  {
	 vfloat32 curTime = glfwGetTime();
	 deltaTime = curTime - lastTime;
	 lastTime = curTime;
  }
  vfloat32 GetTimeDelta() { return deltaTime; }
  void LimitFps(vuint FPS)
  {
	vfloat32 waitFactor = 1.0f / FPS;
	vfloat32 deltaTime = GetTimeDelta();

	while (deltaTime < waitFactor)
	{
	  ;//idle
	}
	
  }
  vfloat32 deltaTime;
  vfloat32 lastTime;
};
class RacerDemo : public VVeloxApp
{
public:
	RacerDemo();

	virtual vint Main(std::vector<std::string> args);

private:
	IVWindowManager::IVWindowPtr m_pWindow;
	IVDevice* m_pDevice;
	IVButton* m_pEscapeKey;
	IVButton* m_pCamToggleKey;
	IVButton* m_pF1Key;
	IVButton* m_pF2Key;
	IVButton* m_pSpace;
	VServicePtr<updater::IVUpdateManager> m_pUpdater;
	VServicePtr<system::IVSystemManager> m_pSystem;

//	VSharedPtr<VSimpleShooting> m_pRootShooting;
	VSimpleShooting* m_pRootShooting;
	VSharedPtr<IVLightManager> m_pLightManager;
	VUpdateManagerPart* m_pUpdateManager;
	VSharedPtr<v3d::utils::VFrameCounter> m_pFrameCounter;

	IVDevice& Device();

	void Init();
	void Cleanup();
	void CreateResources();
};

VSharedPtr<VEntity> LoadScene(const std::string& in_strFileName);
//-----------------------------------------------------------------------------

V3D_DECLARE_EXCEPTION(VCommandLineOptionsException, VException);

class VCommandLineOptions
{
	typedef std::map<std::string, std::string> OptionMap;
	OptionMap m_Options;

public:
	VCommandLineOptions(const std::vector<std::string>& args)
	{
		Parse(args);
	}

	void Parse(const std::vector<std::string>& args)
	{
		if( args.size() > 1 )
		for(vuint argNum = 0; argNum < args.size() - 1; ++argNum)
		{
			const std::string currentArg = args[argNum];
			const std::string nextArg = args[argNum+1];

			if( currentArg.length() > 0 && currentArg[0] == '-' )
			{
				Set(std::string(currentArg.begin()+1, currentArg.end()), nextArg);
				++argNum;
			}
		}
	}

	void Set(const std::string& keyName, const std::string& value)
	{
		m_Options[keyName] = value;
	}

	vbool Contains(const std::string& keyName)
	{
		return m_Options.find(keyName) != m_Options.end();
	}

	std::string Get(const std::string& keyName)
	{
		if( Contains(keyName) )
		{
			return m_Options[keyName];
		}
		else
		{
			V3D_THROWMSG(VCommandLineOptionsException, 
				"Could not find option " << keyName);
		}
	}
};

/**
 * @author sheijk
 */
vint RacerDemo::Main(std::vector<std::string> args)
{
	Init();
	CreateResources();

	TimeTest time;

	std::string sceneFileName = "/edit/racer.v3dscene";

	VCommandLineOptions commandLineOptions(args);
	if( commandLineOptions.Contains("scene") )
	{
		sceneFileName = commandLineOptions.Get("scene");
	}

	VSharedPtr<VEntity> pRoot = LoadScene(sceneFileName);
	m_pUpdateManager = pRoot->GetFirst<VUpdateManagerPart>();

	m_pRootShooting = pRoot->GetFirst<VSimpleShooting>();
	V3D_ASSERT( m_pRootShooting != 0 );
	m_pRootShooting->SetRenderTarget(m_pDevice);
	if( m_pRootShooting == 0 )
		V3D_THROW(VException, "could not find a shooting in the root node");
	VInputPart* pInputPart = pRoot->GetFirst<VInputPart>();
	pInputPart->SetInputManager(&m_pWindow->QueryInputManager());

	const VNode::ActivationResult activationResult = pRoot->Activate();
	//pRoot->DumpInfo();

	//TODO: support im device oder so
	glEnable(GL_FOG);
	vfloat32 fogColor2[4] = { fogColor.red, fogColor.green, fogColor.blue, 1.0f };
	glFogfv(GL_FOG_COLOR, fogColor2);
	glFogf(GL_FOG_DENSITY, 1.0f);
	glFogf(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 300.f);
	glFogf(GL_FOG_END, 400.0f);

	/*VMatrix44f test = math::ScaleMatrix(10.0f);
	vout << test << vendl;*/

	//pRoot->Add( SharedPtr(new VEntity()) );

	m_pUpdater->Start();
	glfwInit();

	vfloat32 startTime = glfwGetTime();
	long frameCounter = 0;
	vfloat32 lastTime = 0;

	//while( m_pSystem->GetStatus() )
	//{
	//	Device().BeginScene();

	//	m_pRootShooting->UpdateAndCull();
 //		m_pRootShooting->Render();

	//	Device().EndScene();

	//	++frameCounter;
	//	m_pUpdater->StartNextFrame();
	//	m_pFrameCounter->LogLastFrameDuration();

	//	if( m_pEscapeKey->IsDown() )
	//		m_pSystem->SetStatus( false );
	//}

	while(m_pSystem->GetStatus())
	{
	  
	  //time.UpdateTime();
	  /*vout << "time: " << time.GetTimeDelta() << "fps: " << 1.0f /time.GetTimeDelta() << vendl;*/
	   //time.LimitFps(10);
	   vfloat32 curTime = glfwGetTime();
	   vfloat32 deltaTime = curTime - lastTime;
	   lastTime = curTime;

	  // vfloat32 waitFactor = 1.0f / 60;

	  // while (deltaTime < waitFactor)
	  // {
		 //vfloat32 curTime = glfwGetTime();
		 //deltaTime = curTime -lastTime;
	  // }
		Device().BeginScene();
		const vfloat32 frameDuration = vfloat32(m_pUpdater->GetFrameDuration());

		// use space to pause scene
		if( ! m_pSpace->IsDown() )
			m_pUpdateManager->Update(frameDuration);
		
		m_pRootShooting->UpdateAndCull();
		m_pRootShooting->Render();

		
		Device().EndScene();
		frameCounter++;
		m_pUpdater->StartNextFrame();
		m_pFrameCounter->LogLastFrameDuration();

		static vfloat32 timeTillNextToggle = .0f;
		timeTillNextToggle -= frameDuration;

		if( m_pCamToggleKey->IsDown() && timeTillNextToggle <= .0f )
		{
			static vuint camNum = 0;
			camNum = (camNum + 1) % m_pRootShooting->CameraCount();

			m_pRootShooting->SetActiveCamera(camNum);

			m_pCamToggleKey->SetDown(false);
			timeTillNextToggle = .1f;
		}

		if( m_pF1Key->IsDown() )
		{
			pRoot->DumpInfo("#");
			VResourceId("/")->DumpInfo("");
		}

		if( m_pEscapeKey->IsDown() )
			m_pSystem->SetStatus(false);
	}

	vout << "Average frames: " << m_pFrameCounter->GetAverageFPS() << vendl;
	m_pUpdater->Stop();
	vfloat32 dieTime = glfwGetTime();
	vfloat32 deltaTime = dieTime - startTime;
	vout << "fps / time: " << 1.0f / (deltaTime / frameCounter) << vendl;

	pRoot->Deactivate();
	
	Cleanup();

	return 0;
}

//-----------------------------------------------------------------------------

RacerDemo::RacerDemo()
{
	m_pWindow.Assign(0);
	m_pDevice = 0;
	m_pEscapeKey = 0;
	m_pCamToggleKey = 0;
}

void RacerDemo::Init()
{
	// create window
	VServicePtr<window::IVWindowManager> pWindowManager;

	VDisplaySettings displaySettings;
	displaySettings.SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	m_pWindow =	pWindowManager->QueryWindow(
		APP_NAME.c_str(), &displaySettings);

	m_pDevice = &m_pWindow->QueryGraphicsDevice();

	// get the escape key
	m_pEscapeKey = &m_pWindow->QueryInputManager().GetStandardKey(KeyEscape);
	m_pCamToggleKey = &m_pWindow->QueryInputManager().GetStandardKey(KeyTab);
	m_pF1Key = &m_pWindow->QueryInputManager().GetStandardKey(KeyF1);
	m_pF2Key = &m_pWindow->QueryInputManager().GetStandardKey(KeyF2);
	m_pSpace = &m_pWindow->QueryInputManager().GetStandardKey(KeySpace);

	// init system and updater service
	m_pSystem->SetStatus(true);
	m_pFrameCounter.Assign(new v3d::utils::VFrameCounter( 50 ));

	//m_pCamera.Assign(new VKeyboardCamera(m_pWindow->QueryInputManager()));
}

void RacerDemo::Cleanup()
{
	m_pDevice = 0;
	m_pWindow.Release();
	m_pEscapeKey = 0;
}

void RacerDemo::CreateResources()
{
}

IVDevice& RacerDemo::Device()
{
	V3D_ASSERT(m_pDevice != 0);

	return *m_pDevice;
}

VSharedPtr<VEntity> LoadScene(const std::string& in_strFileName)
{
	VSharedPtr<vfs::IVStream> pFileStream = vfs::VFileSystemPtr()->OpenFile(
		in_strFileName.c_str(), vfs::VReadAccess);
	VSharedPtr<IVXMLElement> pXMLDocument = VXMLServicePtr()->GetRootElement(pFileStream.Get());
	VSharedPtr<VEntity> pScene = VEntitySerializationServicePtr()->ParseScene(*pXMLDocument);

	return pScene;
}

//-----------------------------------------------------------------------------
namespace {
	RacerDemo g_theApp;
}

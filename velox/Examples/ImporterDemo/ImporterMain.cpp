#include <V3d/Core.h>
#include <V3d/Vfs.h>
#include <v3d/Window.h>
#include <V3d/Updater.h>
#include <V3d/System.h>
#include <V3d/Graphics.h>
#include <V3d/Math.h>
#include <V3d/Input.h>
#include <V3d/Image.h>
#include <v3d/Resource.h>
#include <vector>

using namespace v3d;
using namespace window;
using namespace updater;
using namespace system;
using namespace graphics;
using namespace math;
using namespace input;
using namespace vfs;
using namespace image;
using namespace utils;
using namespace std;

/**
 * Demonstrates the usage of the 3ds importer
 * @author: ins
 */

class VImporterDemo : public VVeloxApp
{
public:
	VImporterDemo();
	virtual ~VImporterDemo();

	virtual vint Main(vector<string> args);
	void LoadModel();

private:
	
	IVDevice& GetDevice() { return *m_pDevice; }
		
	IVDevice* m_pDevice;
	VSystemManagerPtr m_pSystem;
	VUpdateManagerPtr m_pUpdater;
};

//-----------------------------------------------------------------------------
VImporterDemo::VImporterDemo()
{
}

VImporterDemo::~VImporterDemo()
{
}
/**
 * loads a simple model
 */
void VImporterDemo::LoadModel()
{
	resource::VResourceId modelResourceId =
		resource::VResourceManagerPtr()->CreateResource("/model3ds");

	modelResourceId->AddData(new resource::VFileName("/data/afighter.3ds"));
}

vint VImporterDemo::Main(vector<string> args)
{
	// create window
	VWindowManagerPtr pWindowManager;
	IVWindowManager::WindowPtr pWindow = pWindowManager->QueryWindow(
		"ImporterDemo",
		&VDisplaySettings(VSize(800, 600), VPosition(750, 50))
		);

	IVDevice& device(pWindow->QueryGraphicsDevice());
	m_pDevice = &device;
	IVInputManager& input(pWindow->QueryInputManager());

 	// setup camera
	VKeyboardCamera cam(input);
	cam.SetMovementSpeed(4);
	cam.GetCamera().Move(0, 0, 0.0f);
	cam.GetCamera().RotateY(90);
	cam.GetCamera().RotateZ(90);
	cam.GetCamera().Move(0, 0, -10.0f);

	input::IVButton* pEscapeButton;
	pEscapeButton	= &input.GetStandardKey(KeyEscape);
	m_pSystem->SetStatus(true);

	LoadModel();

    
	while(m_pSystem->GetStatus())
	{
		if(pEscapeButton->IsDown() == true)
		{
			m_pSystem->SetStatus(false);
		}
		
		VMatrix44f trans;
		trans.SetTransform(0,0,-2);
		device.SetMatrix(IVDevice::ModelMatrix, trans);
		device.SetViewTransform( cam.GetCamera().GetTransform() );
		//device.SetMatrix(IVDevice::ViewMatrix, cam.GetTransform());

		device.BeginScene();

		resource::VResourceId pModelResourceId = resource::VResourceManagerPtr()->GetResourceByName("/model3ds");
		
		
	
		for(vuint i = 0; i < pModelResourceId->GetData<VModel>()->GetPartCount(); i++)
		{
			for(vuint matid = 0; matid < pModelResourceId->GetData<VModel>()->GetPart(i).GetMaterial()->PassCount(); ++matid)
			{
				const IVPass* pPass = & pModelResourceId->GetData<VModel>()->GetPart(i).GetMaterial()->GetPass(matid);

				ApplyMaterial(device, pPass);
				device.RenderMesh(&(*(pModelResourceId->GetData<VModel>()->GetPart(i).GetMesh())));
			}
		}

		static bool x = true;
		while(x)
		{
			pModelResourceId->DumpInfo("/model3ds");
						
			
			x = false;
			resource::VResourceManagerPtr()->DumpResourceInfo();
		}

	
		device.EndScene();

		m_pUpdater->StartNextFrame();
		cam.Move(vfloat32(m_pUpdater->GetFrameDuration()) * 10);

	}

	m_pUpdater->Stop();

	return 0;
}

namespace {
	VImporterDemo g_ImporterApp;
}
/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VView.h"
//-----------------------------------------------------------------------------
#include <V3d/Graphics.h>
#include <V3d/Graphics.h>
#include <V3d/Math.h>
#include <V3d/Resource.h>
#include <V3d/Core/VException.h>
#include "../../Source/Graphics/OpenGL/VOpenGLDevice.h"
#include "../../Source/Graphics/OpenGL/glsl/VGLSLShader.h"
#include "../../Source/Graphics/OpenGL/Context/VFrameBufferObjectContext.h"

#include <iostream>
#include <functional>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d::graphics;
using namespace v3d::resource;
using namespace v3d::math;
using namespace v3d::scene;
using namespace v3d::entity;
using namespace std;

VSharedPtr<VView> VView::s_pInstance;
VSharedPtr<graphics::VWin32WindowContext> VView::m_pMainContext;

VView::VView()
{
	m_bInitCalled = false;
	m_bIsRunning = true;
	m_Thread = 0;
	
	vout << "Creating view for hwnd... " << vendl;

	// start rendering
	try {		
		m_Thread = glfwCreateThread(VView::FrameUpdateLoop, this);

		if( m_Thread < 0 )
		{
			V3D_THROW(VException, "Could not create c++ thread");
		}

		m_SyncMutex = glfwCreateMutex();
		m_SyncDoneCondition = glfwCreateCond();

		vout << "done. ThreadId = " << m_Thread << vendl;
	} catch(VException& e) {
		vout << vendl
			<< "Error: "
			<< e.GetErrorString() << vendl
			<< e.GetErrorFile() << ":" << e.GetErrorLine() << vendl;
	} catch(...) {
		vout << "Unknown exception occured" << vendl;
	}
}

VView::~VView()
{
	glfwDestroyCond(m_SyncDoneCondition);
	glfwDestroyMutex(m_SyncMutex);
	glfwDestroyThread(m_Thread);
}

void VView::FrameUpdateLoop(void* arg)
{
	VView* pView = reinterpret_cast<VView*>(arg);
	
	pView->FrameUpdateLoop();
}

bool fu = false;

void VView::FrameUpdateLoop()
{
	fu = true;
	vout << "Started update loop (thread " << glfwGetThreadID() << ")" << vendl;

	using std::for_each;
	using std::mem_fun;
	
	vfloat32 delay = 1.0f;
	
	// initialize
	for_each(m_FrameActions.begin(), m_FrameActions.end(),
		mem_fun<void, IVFrameAction>(&IVFrameAction::Init));

	VServicePtr<updater::IVUpdateManager> pUpdater;
	pUpdater->Start();

	while( IsRunning() )
	{
		try
		{
			const vfloat32 frameDuration = vfloat32(pUpdater->GetFrameDuration());

			// add all new actions
			for(FrameActions::iterator newAction = m_NewFrameActions.begin();
				newAction != m_NewFrameActions.end(); ++newAction)
			{
				(*newAction)->Init();

				m_FrameActions.push_back(*newAction);
			}
			m_NewFrameActions.clear();

			// remove all old actions
			for(FrameActions::iterator oldAction = m_OldFrameActions.begin();
				oldAction != m_OldFrameActions.end(); ++oldAction)
			{
				(*oldAction)->Shutdown();
				FrameActions::iterator newEnd = std::remove(
					m_FrameActions.begin(), m_FrameActions.end(), *oldAction);
				m_FrameActions.erase(newEnd, m_FrameActions.end());
			}
			m_OldFrameActions.clear();

			m_bInitCalled = true;

			if( m_pMainContext != 0 )
			{
				//m_pMainContext->MakeCurrent();
			}

			// tell all frame actions to execute
			for(FrameActions::iterator action = m_FrameActions.begin();
				action != m_FrameActions.end(); ++action)
			{
				(*action)->UpdateFrame(frameDuration);
			}
			//for_each(
			//	m_FrameActions.begin(), 
			//	m_FrameActions.end(), bind1st(mem_fun<void, IVFrameAction>(&IVFrameAction::UpdateFrame), frameDuration));

			try
			{
				delay = 1.0f / property::GetProperty<vfloat32>("editor.fps");
			}
			catch(VException&) 
			{
				property::SetProperty<vfloat32>("editor.fps", 60.0f);
				delay = 1.0f / 60.0f;
			}

			glfwLockMutex(m_SyncMutex);
			if( m_SyncActions.size() > 0 )
			{
				vout << "[VView] executing " << m_SyncActions.size()
					<< " synchronized actions" << vendl;
			}

			for(SyncActions::iterator syncAction = m_SyncActions.begin(); syncAction != m_SyncActions.end(); ++syncAction)
			{
				(*syncAction)->Run();
			}
			//for_each(m_SyncActions.begin(), m_SyncActions.end(),
				//mem_fun<void, IVSynchronizedAction>(&IVSynchronizedAction::Run));
			m_SyncActions.clear();
			glfwUnlockMutex(m_SyncMutex);
			glfwBroadcastCond(m_SyncDoneCondition);

			if( m_pMainContext != 0 )
			{
				//m_pMainContext->SwapBuffers();
			}

			// sleep for n seconds
			glfwSleep(delay);
			pUpdater->StartNextFrame();
		}
		catch(v3d::VException& e)
		{
			vout << "Catched exception in C++ loop: " << e.ToString() << vendl;
		}
	}

	pUpdater->Stop();
	
	// tell actions that the main loop ended
	for_each(m_FrameActions.begin(), m_FrameActions.end(), 
		mem_fun<void, IVFrameAction>(&IVFrameAction::Shutdown));
	
	cout << "Finished rendering" << endl;	
}

graphics::VWin32WindowContext* VView::GetMainContext()
{
	return m_pMainContext.Get();
}

void VView::Init(VNativeWindowHandle windowHandle)
{
	HWND toplevelHandle = GetAncestor( (HWND)windowHandle, GA_ROOT );

	VDisplaySettings settings;
	settings.SetWidth(200);
	settings.SetHeight(200);
	settings.SetPosition(0, 0);

	cout << "\tCreating context" << endl;
	VWin32WindowContext* pContext = new VWin32WindowContext(toplevelHandle, &settings);
	m_pMainContext.Assign( pContext );
}

void VView::Shutdown()
{
	m_pMainContext.Release();
}

void VView::ExecSynchronized(IVSynchronizedAction* in_pAction)
{
	vout << "[VView] ExecSynchronized ";

	if( ! IsRunning() )
	{
		vout << "failed: not running" << vendl;
		V3D_THROW(VException, "Cannot run action synchronized because VView"
			" is not running. (Internal error?)");
	}

	glfwLockMutex(m_SyncMutex);
	m_SyncActions.push_back(in_pAction);
	const double timeoutSeconds = 2;
	glfwWaitCond(m_SyncDoneCondition, m_SyncMutex, timeoutSeconds);
	vout << " done" << vendl;
	glfwUnlockMutex(m_SyncMutex);
}

void VView::Start()
{
	m_bIsRunning = true;
}

void VView::Stop()
{
	m_bIsRunning = false;
}

VView* VView::GetInstance()
{
	if( s_pInstance.Get() == 0 )
	{
		s_pInstance.Assign(new VView());
	}
	
	return s_pInstance.Get();
}

void VView::Add(IVFrameAction* in_pTestAction)
{
	//if( ! fu )
	//	V3D_THROW(VException, "no fu!");

	vout << "Registered frame action " << in_pTestAction << "\n";

	// will only be accessed if m_bInitCalled == false
	m_NewFrameActions.push_back(in_pTestAction);
	
	m_bInitCalled = false;

	vfloat32 secondsWaiting = .0f;

	if( m_bIsRunning )
	{
		while( ! m_bInitCalled )
			glfwSleep(.01f);
	}
	else
	{
		V3D_THROW(VException, "Velox C++ render loop is not running!");
	}
}

void VView::Remove(IVFrameAction* in_pAction)
{
	vout << "Unregistered frame action " << in_pAction << "\n";

	m_OldFrameActions.push_back(in_pAction);
}

template<typename Container, typename T>
bool contains(const Container& container, T t)
{
	return std::find(container.begin(), container.end(), t) != container.end();
}

bool VView::Contains(IVFrameAction* in_pAction)
{
	return contains(m_FrameActions, in_pAction) || contains(m_NewFrameActions, in_pAction);
}

//graphics::VSubAreaContext* VView::CreateSubAreaContext()
//{
//	if( m_pMainContext != 0 )
//	{
//		return new graphics::VSubAreaContext( m_pMainContext );
//	}
//	else
//	{
//		V3D_THROW(VException, "Could not create sub area context: main context is 0");
//	}
//}

////void CreateTestModel(const std::string& resname);
//
////VModel model;
//
////const IVMesh* pmesh = 0;
////const IVMaterial* pmat = 0;
//
//class VGLFWContext : public IVRenderContext
//{
//public:
//	VGLFWContext()
//	{
//		int result = glfwOpenWindow(400, 300, 8, 8, 8, 8, 24, 0, GLFW_WINDOW);
//		glfwSetWindowTitle("test render window");
//	}
//	
//	virtual void MakeCurrent()
//	{
//	}
//	
//	virtual void SwapBuffers()
//	{
//		glfwSwapBuffers();
//	}
//	
//	virtual IVRenderContext* CreateOffscreenContext(const VDisplaySettings* in_pDisplaySettings)
//	{
//		V3D_THROW(VException, "not supported, yet");
//	}
//};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------



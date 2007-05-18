/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include "VRenderFrameAction.h"
//-----------------------------------------------------------------------------
#include <iostream>

#include <V3d/Graphics/VDisplaySettings.h>
#include <V3d/Scene/VSimpleShooting.h>

#include "../../Source/Graphics/OpenGL/Context/VWin32WindowContext.h"

#include "VView.h"
#include <set>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace std;
using namespace graphics;
using namespace scene;

namespace {
	const std::string g_strGridPropertyName = "v3d.graphics.showGrid";
	const std::string g_strRenderPropertyName = "v3d.graphics.render";
}

namespace {
	class VMutex
	{
	public:
		VMutex()
		{
			m_Mutex = glfwCreateMutex();
			//V3D_ASSERT( m_Mutex != NULL );
		}

		~VMutex()
		{
			glfwDestroyMutex( m_Mutex );
		}

	private:
		GLFWmutex m_Mutex;

		friend class VMutexLock;
	};

	class VMutexLock
	{
	public:
		VMutexLock( VMutex& mutex )
		{
			if( mutex.m_Mutex == NULL )
			{
				mutex.m_Mutex = glfwCreateMutex();
				V3D_ASSERT( mutex.m_Mutex != NULL );
			}

			m_Mutex = mutex.m_Mutex;
			glfwLockMutex( m_Mutex );
		}

		void Unlock()
		{
			if( m_Mutex != 0 )
			{
				V3D_LOG("rele..");
				glfwUnlockMutex( m_Mutex );
				m_Mutex = 0;
				V3D_LOGLN(".ased");
			}
		}

		~VMutexLock()
		{
			Unlock();
		}

	private:
		GLFWmutex m_Mutex;
	};

	//class VMainRenderFrameAction : public IVFrameAction
	//{
	//public:

	//	virtual void Init()
	//	{
	//	}

	//	virtual void UpdateFrame(vfloat32 in_fFrameDuration)
	//	{
	//		V3D_LOGLN("logging in VMainRenderFrameAction.UpdateFrame");
	//		VMutexLock lock( m_Mutex );
	//		V3D_LOGLN("done");

	//		const RenderActionSet::iterator raend = m_RenderActions.end();
	//		for(RenderActionSet::iterator renderAction = m_RenderActions.begin();
	//			renderAction != raend;
	//			++renderAction)
	//		{
	//			VRenderFrameAction* rfa = *renderAction;
	//			rfa->Render();
	//		}
	//	}

	//	virtual void Shutdown()
	//	{
	//	}

	//	void Add(VRenderFrameAction* renderAction)
	//	{
	//		V3D_LOGLN("logging VMainRenderFrameAction.Add");
	//		VMutexLock lock( m_Mutex );
	//		V3D_LOGLN("done");

	//		m_RenderActions.insert( renderAction );
	//		lock.Unlock();

	//		VView::GetInstance()->Add( renderAction );
	//	}

	//	void Remove(VRenderFrameAction* renderAction)
	//	{
	//		VView::GetInstance()->Remove( renderAction );

	//		V3D_LOGLN("loggin VMainRenderFrameAction.Remove");
	//		VMutexLock lock( m_Mutex );
	//		V3D_LOGLN("done");

	//		m_RenderActions.erase( renderAction );
	//	}

	//private:
	//	VMutex m_Mutex;
	//	typedef std::set<VRenderFrameAction*> RenderActionSet;
	//	RenderActionSet m_RenderActions;
	//	//VSharedPtr<graphics::IVRenderContext> m_pContext;
	//};

	//VMainRenderFrameAction g_MainRenderAction;
}

void VRenderFrameAction::InitRendering(VNativeWindowHandle handle)
{
	//VView::GetInstance()->Add( &g_MainRenderAction );
}

void VRenderFrameAction::ShutdownRendering()
{
	//VView::GetInstance()->Remove( &g_MainRenderAction );
}

VRenderFrameAction::VRenderFrameAction(VNativeWindowHandle in_Hwnd)
{
	m_pShooting = 0;
	m_HWND = HWND(in_Hwnd);		
	m_nWidth = 0;
	m_nHeight = 0;
	m_bResized = false;
}

void VRenderFrameAction::RegisterSelf()
{
	VView::GetInstance()->Add( this );
	//g_MainRenderAction.Add( this );
}

void VRenderFrameAction::UnregisterSelf()
{
	VView::GetInstance()->Remove( this );
	//g_MainRenderAction.Remove( this );
}

void VRenderFrameAction::Init()
{
	cout << "\tCreating display settings" << endl;
	VDisplaySettings settings;
	settings.SetWidth(200);
	settings.SetHeight(200);
	settings.SetPosition(0, 0);

	cout << "\tCreating context" << endl;
	VWin32WindowContext* pContext = new VWin32WindowContext( m_HWND, &settings );
	pContext->ShareListsWith( VView::GetInstance()->GetMainContext() );
	//IVRenderContext* pContext = VView::GetInstance()->CreateSubAreaContext(m_HWND);

	cout << "\tCreating device" << endl;
	m_pDevice.Assign(new VOpenGLDevice(settings, pContext));

	if( ! property::ExistsProperty(g_strGridPropertyName.c_str()) )
	{
		property::SetProperty(g_strGridPropertyName.c_str(), true);	
	}

	if( ! property::ExistsProperty(g_strRenderPropertyName.c_str()) )
	{
		property::SetProperty(g_strRenderPropertyName.c_str(), true);	
	}

	HWND hWnd = GetAncestor(m_HWND, GA_ROOT);
	m_pInputManager = new input::VDIInputManager(hWnd);
	m_pInputManager->SetActive(false);
}

v3d::input::IVInputManager* VRenderFrameAction::GetInputManager()
{
	return m_pInputManager;
}

void VRenderFrameAction::Shutdown()
{
}

void VRenderFrameAction::SetArea(vint left, vint top, vint right, vint bottom)
{
	if( m_pDevice != 0 )
	{
		m_pDevice->SetViewport(left, top, right, bottom);
	}
}

//void VRenderFrameAction::setSize(vuint width, vuint height)
//{
//	m_nWidth = width;
//	m_nHeight = height;
//	m_bResized = true;
//
//	if( m_pDevice.Get() != 0 )
//	{
//		m_pDevice->SetViewport(0, 0, m_nWidth, m_nHeight);
//	}
//}

void VRenderFrameAction::UpdateFrame(vfloat32 in_fFrameDuration)
{
	Render();
}

void VRenderFrameAction::Render()
{
	m_bResized = false;

	if( m_pShooting != 0 && m_pShooting->IsActive() )
	{
		m_pShooting->UpdateAndCull();
		m_pShooting->Render();
	}
	else if( m_pDevice.Get() != NULL )
	{
		m_pDevice->BeginScene();
		m_pDevice->EndScene(IVDevice::FlipScene);
	}

	if( m_pShooting == 0 )
	{
		static vuint count = 100;

		if( count >= 100 )
		{
			vout << "alert! no shooting" << vendl;
			count = 0;
		}

		++count;
	}

	if( m_pInputManager->GetStandardKey(input::KeyEscape).IsDown() )
	{
		SetIgnoreInput(true);
		vout << "Disabled input" << vendl;
	}
}

void VRenderFrameAction::SetIgnoreInput(vbool ignore)
{
	m_pInputManager->SetActive(! ignore);
}

void VRenderFrameAction::SetShooting(v3d::scene::IVShooting* in_pShooting)
{
	m_pShooting = in_pShooting;
	if( in_pShooting == 0 )
		return;

	VSimpleShooting* baseShooting = in_pShooting->Convert<VSimpleShooting>();
	if( baseShooting != 0 )
	{
		baseShooting->SetRenderTarget( GetDevice() );
	}
}

v3d::graphics::IVDevice* VRenderFrameAction::GetDevice()
{
	return m_pDevice.Get();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------


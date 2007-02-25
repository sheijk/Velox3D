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

VRenderFrameAction::VRenderFrameAction(VNativeWindowHandle in_Hwnd)
{
	m_pShooting = 0;
	m_HWND = HWND(in_Hwnd);		
	m_nWidth = 0;
	m_nHeight = 0;
	m_bResized = false;
}

void VRenderFrameAction::Init()
{
	cout << "\tCreating display settings" << endl;
	VDisplaySettings settings;
	settings.SetWidth(200);
	settings.SetHeight(200);
	settings.SetPosition(0, 0);

	cout << "\tCreating context" << endl;
	IVRenderContext* pContext(new VWin32WindowContext(m_HWND, &settings));

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

void VRenderFrameAction::setSize(vuint width, vuint height)
{
	m_nWidth = width;
	m_nHeight = height;
	m_bResized = true;

	if( m_pDevice.Get() != 0 )
	{
		m_pDevice->SetViewport(0, 0, m_nWidth, m_nHeight);
	}
}


void VRenderFrameAction::UpdateFrame(vfloat32 in_fFrameDuration)
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

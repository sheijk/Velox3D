/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Core/Modules/VVeloxApp.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

VVeloxApp::VVeloxMainProxy::VVeloxMainProxy(VVeloxApp* pApp) : 
	m_pApp(pApp), VNamedObject("main", 0)
{
}

vint VVeloxApp::VVeloxMainProxy::Main(const std::vector<std::string>& args)
{
	return m_pApp->Main(args);
}

VVeloxApp::VVeloxApp()
{
}

VVeloxApp::~VVeloxApp()
{
}

void VVeloxApp::Initialize()
{
	m_pMainService.reset(new VVeloxMainProxy(this));
}

void VVeloxApp::Shutdown()
{
	m_pMainService.release();
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------


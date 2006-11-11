/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include "VUpdateManagerCallAction.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using entity::VEntity;
using entity::VUpdateManagerPart;

VUpdateManagerCallAction::VUpdateManagerCallAction()
{
	m_pUpdateManager = 0;
	// dummy updating, no "moving"
	m_fUpdateSpeedFactor = .0f;
}

void VUpdateManagerCallAction::Init()
{
}

void VUpdateManagerCallAction::UpdateFrame(vfloat32 in_fFrameDuration)
{
	if( m_pUpdateManager != 0 )
		m_pUpdateManager->Update(in_fFrameDuration * m_fUpdateSpeedFactor);
}

void VUpdateManagerCallAction::Shutdown()
{
}

void VUpdateManagerCallAction::SetEntity(entity::VEntity* in_pEntity)
{
	m_pUpdateManager = in_pEntity->GetPart<VUpdateManagerPart>();
//	m_pUpdateManager = GetPart<VUpdateManagerPart>(in_pEntity);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------


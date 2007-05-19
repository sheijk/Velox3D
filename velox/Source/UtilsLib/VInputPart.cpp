/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Utils/VInputPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VInputPart::VInputPart()
{
	m_pInputManager = 0;
}

VInputPart::~VInputPart()
{
}

void VInputPart::SetInputManager(input::IVInputManager* in_pInputManager)
{
	m_pInputManager = in_pInputManager;
}

input::IVInputManager* VInputPart::GetInputManager() const
{
	return m_pInputManager;
}

V3D_REGISTER_PART_PARSER(VInputPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------


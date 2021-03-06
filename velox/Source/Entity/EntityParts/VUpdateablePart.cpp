/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Entity/VUpdateablePart.h>
//-----------------------------------------------------------------------------
#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VUpdateManagerPart::VUpdateManagerPart()
{
}

VUpdateManagerPart::~VUpdateManagerPart()
{
	m_pChilds.clear();
}

void VUpdateManagerPart::Update(vfloat32 in_Seconds)
{
	for(std::list<IVUpdateablePart*>::iterator iter = m_pChilds.begin();
		iter != m_pChilds.end();
		++iter)
	{
		(*iter)->Update(in_Seconds);
	}
}

void VUpdateManagerPart::OnActivate()
{
}

void VUpdateManagerPart::OnDeactivate()
{
}

void VUpdateManagerPart::Register(IVUpdateablePart* in_pChild)
{
	V3D_ASSERT(in_pChild != 0);

	if(std::find(m_pChilds.begin(), m_pChilds.end(), in_pChild)
		== m_pChilds.end())
	{
		m_pChilds.insert(m_pChilds.end(), in_pChild);
	}
}

void VUpdateManagerPart::Unregister(IVUpdateablePart* in_pChild)
{
	V3D_ASSERT(in_pChild != 0);

	std::list<IVUpdateablePart*>::iterator iter = std::find(m_pChilds.begin(),
		m_pChilds.end(), in_pChild);

	//nothing found here
	if(iter == m_pChilds.end())
	{
		V3D_THROW(VException, "part not found to delete. surely you coded a bug");
		return;
	}

	m_pChilds.erase(iter); 
}

V3D_REGISTER_PART_PARSER(VUpdateManagerPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------

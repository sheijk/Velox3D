#include "VSceneGraphPart.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VSceneGraphPart::VSceneGraphPart()
{
	m_bActive = false;
	m_pParent = 0;
}

VSceneGraphPart::VSceneGraphPart(VSceneGraphPart* in_pParent)
{
	//TODO: sollte der sich hier nicht beim parent registrieren? --sheijk
	m_bActive = false;
	m_pParent = in_pParent;
}

void VSceneGraphPart::Update()
{
	//TODO: zuerst selbst updaten, sonst sind die kinder noch an der
	// alten position --sheijk
	for(std::list<VSceneGraphPart*>::iterator iter = m_pChilds.begin();
		iter != m_pChilds.end();
		++iter)
	{
		(*iter)->Update();
	}

	m_pRigidBodyPart->SetRBTransform(GetAbsoluteTransform());
}

void VSceneGraphPart::SetParent(VSceneGraphPart* in_pParent)
{
	V3D_ASSERT(in_pParent != 0);

	if (m_bActive)
	{
		m_pParent->RemoveChild(this);
		in_pParent->AddChild(this);
	}
    
	m_pParent = in_pParent;
}

void VSceneGraphPart::AddChild(VSceneGraphPart* in_pChild)
{
	V3D_ASSERT(in_pChild != 0);
	//TODO: check if in_pChild ist already present
	m_pChilds.push_back(in_pChild);
}

void VSceneGraphPart::RemoveChild(VSceneGraphPart* in_pChild)
{
	// child sollte evtl benachrichtigt werden --sheijk
	std::list<VSceneGraphPart*>::iterator iter = 
		std::find(m_pChilds.begin(), m_pChilds.end(), in_pChild);

	m_pChilds.erase(iter);
}

void VSceneGraphPart::Activate()
{
	//TODO: erst pruefen ob aktiv, sonst doppelt angemeldet.
	// ausserdem sollten alle childs auch aktiviert werden --sheijk
	if (m_pParent != 0)
        m_pParent->AddChild(this);

	m_bActive = true;
}

void VSceneGraphPart::Deactivate()
{
	// auch alle kinder deaktivieren(?) --sheijk
	if (m_pParent != 0)
		m_pParent->RemoveChild(this);

	m_bActive = false;
}

void VSceneGraphPart::TellNeighbourPart(const utils::VFourCC& in_Id, IVPart& in_Part)
{
	if (in_Part.IsOfType<VRigidBodyPart>())
		if ( in_Id == utils::VFourCC("body") )
			m_pRigidBodyPart = in_Part.Convert<VRigidBodyPart>();
}

void VSceneGraphPart::SetTransform(const VRBTransform& in_Transform)
{
	m_Transform = in_Transform;
}

VRBTransform VSceneGraphPart::GetTransform() const
{
	return m_Transform;
}

VRBTransform VSceneGraphPart::GetAbsoluteTransform()
{
	//TODO: aus VRBTransform auslesen (wird nur durch Update aktualisiert) --sheijk
	return m_pParent->GetAbsoluteTransform()*m_Transform;
}


//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------

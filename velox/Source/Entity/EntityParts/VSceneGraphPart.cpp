#include <v3dlib/EntityParts/VSceneGraphPart.h>
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
	m_bActive = false;
	m_pParent = in_pParent;
}

VSceneGraphPart::~VSceneGraphPart()
{
	Deactivate();

	for(std::list<VSceneGraphPart*>::iterator iter = m_pChilds.begin();
		iter != m_pChilds.end();
		++iter)
	{
		delete *iter;
		m_pChilds.erase(iter);
	}
	m_pChilds.clear();
}

void VSceneGraphPart::Update()
{
	m_pRigidBodyPart->SetTransform(m_pParent->GetAbsoluteTransform()*m_Transform);

	for(std::list<VSceneGraphPart*>::iterator iter = m_pChilds.begin();
		iter != m_pChilds.end();
		++iter)
	{
		(*iter)->Update();
	}
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
	
	//Falls das Kind noch nicht da ist hinzuügen und neue Eltern setzen
	if ( std::find(m_pChilds.begin(), m_pChilds.end(), in_pChild)
		== m_pChilds.end() )
	{
        m_pChilds.push_back(in_pChild);
		in_pChild->SetParent(this);
	}
}

void VSceneGraphPart::RemoveChild(VSceneGraphPart* in_pChild)
{
	std::list<VSceneGraphPart*>::iterator iter = 
		std::find(m_pChilds.begin(), m_pChilds.end(), in_pChild);
	
	if ( iter != m_pChilds.end() )
	{
		(*iter)->Deactivate();
        m_pChilds.erase(iter);
	}
}

void VSceneGraphPart::Activate()
{
	if (!m_bActive)
	{
        if (m_pParent != 0)
			m_pParent->AddChild(this);

		for(std::list<VSceneGraphPart*>::iterator iter = m_pChilds.begin();
			iter != m_pChilds.end();
			++iter)
		{
			(*iter)->Activate();
		}

		m_bActive = true;
	}
}

void VSceneGraphPart::Deactivate()
{
	if (m_bActive)
	{
        if (m_pParent != 0)
            m_pParent->RemoveChild(this);
		
		for(std::list<VSceneGraphPart*>::iterator iter = m_pChilds.begin();
			iter != m_pChilds.end();
			++iter)
		{
			(*iter)->Deactivate();
		}
	}
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
	return *m_pRigidBodyPart->GetTransform();
}


//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------

#include <v3dlib/EntityParts/VSceneGraphPart.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VSceneGraphPart::VSceneGraphPart() : 
	m_bActive(false),
	m_pParent(IVPart::Ancestor, GetDefaultId(), this)
{
	//TODO: das soll nicht auf ein selbst erzeugtes part, sonder auf das part
	// im entity welches ueber eine VPartConnection bekommen wird zeigen!!!
	m_pRigidBodyPart = new VRigidBodyPart();

	m_relativeTransform.GetXAxis() = VVector3f(1.0f, 0.0f, 0.0f);
	m_relativeTransform.GetYAxis() = VVector3f(0.0f, 1.0f, 0.0f);
	m_relativeTransform.GetZAxis() = VVector3f(0.0f, 0.0f, 1.0f);
	m_relativeTransform.SetPosition(VVector3f(0.0f, 0.0f, 0.0f));
}

VSceneGraphPart::~VSceneGraphPart()
{
}

void VSceneGraphPart::Update()
{
	if(m_pParent.Get() != 0)
	{
		m_Transform = m_pParent->GetTransform() * m_relativeTransform;

		m_pRigidBodyPart->SetTransform(m_Transform);
	}

	for(std::list<VSceneGraphPart*>::iterator iter = m_pChilds.begin();
		iter != m_pChilds.end();
		++iter)
	{
		(*iter)->Update();
	}
}

void VSceneGraphPart::AddChild(VSceneGraphPart* in_pChild)
{
	V3D_ASSERT(in_pChild != 0);
	
	if(std::find(m_pChilds.begin(), m_pChilds.end(), in_pChild)
		== m_pChilds.end())
	{
        m_pChilds.push_back(in_pChild);
	}
}

void VSceneGraphPart::RemoveChild(VSceneGraphPart* in_pChild)
{
	V3D_ASSERT(in_pChild != 0);

	std::list<VSceneGraphPart*>::iterator iter = std::find(m_pChilds.begin(),
		m_pChilds.end(), in_pChild);
	
	//TODO: AUF KEINEN FALL EIN ENTITY PART LOESCHEN, DAS DARF NUR VENTITY!!!!!
	delete* iter;
	m_pChilds.erase(iter);
}

void VSceneGraphPart::Activate()
{
	if(!m_bActive)
	{
        if(m_pParent.Get() != 0)
			m_pParent->AddChild(this);

		//TODO: rausnehmen, die childs werden von VEntity aktiviert
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
	if(m_bActive)
	{
		if(m_pParent.Get() != 0)
			m_pParent->RemoveChild(this);

		//TODO: auch rausnehmen, VEntity deaktiviert die child parts
		for(std::list<VSceneGraphPart*>::iterator iter = m_pChilds.begin();
			iter != m_pChilds.end();
			++iter)
		{
			(*iter)->Deactivate();
		}

		m_bActive = false;
	}
}

void VSceneGraphPart::SetTransform(const math::VRBTransform& in_Transform)
{
	m_Transform = in_Transform;
}

void VSceneGraphPart::SetRelativeTransform(const math::VRBTransform& in_relTransform)
{
	m_relativeTransform = in_relTransform;
}

math::VRBTransform VSceneGraphPart::GetTransform() const
{
	return m_Transform;
}

math::VRBTransform VSceneGraphPart::GetAbsoluteTransform()
{
	return m_pRigidBodyPart->GetTransform();
}

math::VRBTransform VSceneGraphPart::GetRelativeTransform()
{
	return m_relativeTransform;
}

utils::VFourCC VSceneGraphPart::GetDefaultId()
{
	return "esgp";
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
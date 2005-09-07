#include <V3d/Scene/VSceneModelPart.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VSceneModelPart::VSceneModelPart(const graphics::VModel& in_Model) :
	m_Model(in_Model)
{
	m_pParent = 0;
}

void VSceneModelPart::Activate()
{
	if( m_pParent )
	{
		m_Id = m_pParent->Add(m_Model);
	}
}

void VSceneModelPart::Deactivate()
{
	if( m_pParent )
	{
		m_pParent->Remove(m_Id);
		m_Id = 0;
	}
}

void VSceneModelPart::TellParentPart(const utils::VFourCC& in_Id, IVPart& in_Part)
{
	m_pParent =  in_Part.Convert<VSimpleScene>();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

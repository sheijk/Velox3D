#include "VUpdateablePart.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace racer {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VUpdateablePart::VUpdateablePart(VEntityUpdater<VUpdateablePart>* in_pUpdater)
{
	m_pUpdater = in_pUpdater;
	m_bRegistered = false;
}

VUpdateablePart::~VUpdateablePart()
{
	V3D_ASSERT(m_bRegistered == false);
}

void VUpdateablePart::Activate()
{
	Register();
}

void VUpdateablePart::Deactivate()
{
	Unregister();
}

void VUpdateablePart::Register()
{
	if( m_pUpdater && !m_bRegistered )
		m_pUpdater->Add(this);
}

void VUpdateablePart::Unregister()
{
	if( m_pUpdater != 0 && m_bRegistered )
		m_pUpdater->Remove(this);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::racer
//-----------------------------------------------------------------------------

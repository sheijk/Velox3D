#include <V3d/Entity/VEntity.h>
//-----------------------------------------------------------------------------

#include <sstream>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VEntity::VEntity()
{
}

VEntity::~VEntity()
{
	// delete all parts
	for(
		PartContainer::iterator part = m_Parts.begin();
		part != m_Parts.end();
		++part)
	{
		part->second.Release();
	}
}

void VEntity::Activate()
{
	for(
		PartContainer::iterator part = m_Parts.begin();
		part != m_Parts.end();
		++part)
	{
		part->second->Activate();
	}
}

void VEntity::Deactivate()
{
	for(
		PartContainer::iterator part = m_Parts.begin();
		part != m_Parts.end();
		++part)
	{
		part->second->Deactivate();
	}
}

void VEntity::AddPart(const utils::VFourCC& in_Id, PartPtr in_pPart)
{
	if( m_Parts.find(in_Id) == m_Parts.end() )
	{
		// tell all parts about new part		 
		// tell part about all other parts
		for(
			PartContainer::iterator part = m_Parts.begin();
			part != m_Parts.end();
			++part)
		{
			part->second->TellNeighbourPart(in_Id, *in_pPart);
			in_pPart->TellNeighbourPart(part->first, *(part->second));
		}

		// add part to list
		m_Parts[in_Id] = in_pPart;
	}
	else
	{
		std::stringstream message;
		message << "Could not insert part because a part with name '";
		message << in_Id.AsStdString() << "' already exists in entity\n";
		V3D_THROW(VPartAlreadyPresentException, message.str().c_str());
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------

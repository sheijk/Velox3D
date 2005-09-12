#include <V3d/Entity/VPartBase.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VUntypedPartConnection::VUntypedPartConnection(
	IVPart::Location in_Location, 
	const std::string& in_Id, 
	VPartDependency::Condition in_Condition,
	VPartConnectionManager* in_pRegisterTo)
{
	m_Dependency.id = in_Id;
	m_Dependency.condition = in_Condition;
	m_Dependency.location = in_Location;

	in_pRegisterTo->Register(*this);
	m_pPart = 0;
}

void VUntypedPartConnection::Disconnect()
{
	m_pPart = 0;
}

const IVPart::Dependency& VUntypedPartConnection::GetDependency() const
{
	return m_Dependency;
}

void VUntypedPartConnection::Connect(
	VPartDependency::Location in_Location,
	const std::string& in_Id,
	IVPart& in_Part)
{
	if( in_Location == m_Dependency.location &&
		in_Id == m_Dependency.id )
	{
		m_pPart = &in_Part;
	}
}

IVPart* VUntypedPartConnection::GetPart() const
{
	return m_pPart;
}

/**
 * standard c'tor
 */
VPartConnectionManager::VPartConnectionManager()
{
}

/**
 * d'tor
 */
VPartConnectionManager::~VPartConnectionManager()
{
}

void VPartConnectionManager::Register(VUntypedPartConnection& in_Connection)
{
	m_Dependencies.push_back(&in_Connection);
}

void VPartConnectionManager::Connect(
	VPartDependency::Location in_Location, 
	const std::string& in_Id, 
	IVPart& in_Part)
{
    for(vuint con = 0; con < m_Dependencies.size(); ++con)
	{
		m_Dependencies[con]->Connect(in_Location, in_Id, in_Part);
	}
}

void VPartConnectionManager::Disconnect(
	VPartDependency::Location in_Location,
	const std::string& in_Id,
	IVPart& in_Part)
{
	for(vuint con = 0; con < m_Dependencies.size(); ++con)
	{
		const IVPart::Dependency& depInfo(m_Dependencies[con]->GetDependency());

		if( depInfo.id == in_Id && depInfo.location == in_Location )
			m_Dependencies[con]->Disconnect();
	}
}

vbool VPartConnectionManager::IsReady() const
{
	for(vuint con = 0; con < m_Dependencies.size(); ++con)
	{
		if( m_Dependencies[con]->GetDependency().condition == VPartDependency::Mandatory
			&& m_Dependencies[con]->GetPart() == 0 )
		{
			return false;
		}
	}

	return true;
}

vuint VPartConnectionManager::DependencyCount() const
{
	return m_Dependencies.size();
}

VPartDependency VPartConnectionManager::GetDependencyInfo(vuint in_nIndex) const
{
	if( in_nIndex < m_Dependencies.size() )
	{
		return m_Dependencies[in_nIndex]->GetDependency();
	}
	else
	{
		V3D_THROWMSG(VException, 
			"Out of range error when accessing " 
			<< in_nIndex << 
			"th dependency");
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------

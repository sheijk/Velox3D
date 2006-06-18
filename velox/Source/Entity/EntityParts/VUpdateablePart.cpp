#include <v3dlib/EntityParts/VSGAnimationPart.h>
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

void VUpdateManagerPart::Activate()
{
}

void VUpdateManagerPart::Deactivate()
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

std::string VUpdateManagerPart::GetDefaultId()
{
	return "sgum";
}

namespace {
	VPartParser<VUpdateManagerPart> parser;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#include <V3d/Scene/VMeshPartBase.h>
//-----------------------------------------------------------------------------

#include <V3d/Resource.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

using namespace v3d::entity;
using namespace v3d::resource;
using namespace v3d::graphics;

VMeshPartBase::VMeshPartBase(VResourceDataPtr<const IVMaterial> in_hMaterial) :
	m_pSceneManager(VPartDependency::Ancestor, RegisterTo()),
	m_pRigidBody(VPartDependency::Neighbour, RegisterTo())
{
	m_hMaterial = in_hMaterial;
}

VMeshPartBase::VMeshPartBase(const std::string& in_strMaterialResource)
	: m_pSceneManager(VPartDependency::Ancestor, RegisterTo()),
	m_pRigidBody(VPartDependency::Neighbour, RegisterTo())
{
	m_hMaterial = GetResourceData<IVMaterial>(in_strMaterialResource.c_str());
}


/**
* d'tor
*/
VMeshPartBase::~VMeshPartBase()
{
}

const graphics::IVMaterial& VMeshPartBase::GetMaterial() const
{
	return *m_hMaterial;
}

void VMeshPartBase::SetMaterial(
	resource::VResourceDataPtr<const graphics::IVMaterial> in_hMaterial)
{
	m_hMaterial = in_hMaterial;
}

const math::VRBTransform& VMeshPartBase::GetModelTransform() const
{
	return m_pRigidBody->GetTransform();
}

void VMeshPartBase::SetModelTransform(const math::VRBTransform& in_Transform)
{
	m_pRigidBody->SetTransform(in_Transform);
}

VRangeIterator<const IVShapePart> VMeshPartBase::GetVisibleMeshes() const
{
	return CreateSingleValueIterator<const IVShapePart>(this);
}

void VMeshPartBase::Activate()
{
	if( m_pSceneManager.IsConnected() )
		m_pSceneManager->Add(this);
}

void VMeshPartBase::Deactivate()
{
	if( m_pSceneManager.IsConnected() )
		m_pSceneManager->Remove(this);
}

void VMeshPartBase::OnMessage(
	const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	using std::string;

	if( ! in_Message.HasProperty("type") )
		return;

	string request = in_Message.Get("type").Get<string>();

	if( request == "getSettings" )
	{
		if( in_pAnswer == 0 )
			return;

		in_pAnswer->AddProperty("material", 
			m_hMaterial.GetEnclosingResource()->GetQualifiedName());
	}
	else if( request == "update" )
	{
		const string name = in_Message.Get("name").Get<string>();
		const string value = in_Message.Get("value").Get<string>();

		try
		{
			if( name == "material" ) {
				m_hMaterial = GetResourceData<IVMaterial>(value.c_str());
			}
		}
		catch(VException& e)
		{
			vout << "Failed to create model: " << e.GetErrorString() << vendl;
		}
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

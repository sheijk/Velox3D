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

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

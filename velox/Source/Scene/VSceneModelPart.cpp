#include <V3d/Scene/VSceneModelPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/VIOStream.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::resource;

VSceneModelPart::VSceneModelPart(const graphics::VModel& in_Model) :
	m_Model(in_Model)
{
	m_pParent = 0;
}

void VSceneModelPart::AddModelMesh(
	VStringParam in_strMeshResource, 
	VStringParam in_strMaterialResource)
{
	m_Model.Add(graphics::VModelMesh(
		GetResourceData<graphics::IVMesh>(in_strMeshResource),
		GetResourceData<graphics::IVMaterial>(in_strMaterialResource)
		));
}

void VSceneModelPart::RemoveAllMeshes()
{
	m_Model = graphics::VModel();
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
	vout << "parent " << in_Id.AsStdString();
	
	m_pParent = in_Part.Convert<VSimpleScene>();
	
	vout << (m_pParent ? " ok" : " failed") << vendl;
}

utils::VFourCC VSceneModelPart::GetDefaultId()
{
	return "gfxp";
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

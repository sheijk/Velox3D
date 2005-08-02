#include <V3d/Scene/VSceneModelPart.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/VIOStream.h>

#include <V3d/Messaging/VProtocol.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::resource;
using namespace std;

VSceneModelPart::VSceneModelPart(const graphics::VModel& in_Model) :
	m_Model(in_Model),
	m_pParent(IVPart::Ancestor, utils::VFourCC("scen"), this)
{
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
	if( m_pParent.Get() != 0 )
	{
		m_Id = m_pParent->Add(m_Model);
	}
}

void VSceneModelPart::Deactivate()
{
	if( m_pParent.Get() != 0 )
	{
		m_pParent->Remove(m_Id);
		m_Id = 0;
	}
}

namespace {
	messaging::VProtocol addProtocol = messaging::VProtocol()
		.SetDefault("request", "ok")
		.SetDefault("resource", "");
}

void VSceneModelPart::Send(const messaging::VMessage& in_Message)
{
	string request = in_Message.Get("command").Get<string>();

	if( request == "add" )
	{
		string mesh = in_Message.Get("mesh").Get<string>();
		string material = in_Message.Get("material").Get<string>();

		AddModelMesh(mesh.c_str(), material.c_str());
	}
}

utils::VFourCC VSceneModelPart::GetDefaultId()
{
	return "gfxp";
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

#include <v3d/Physics/Bounding/VBoundingSphereVolumePart.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

math::VBoundingBox* VBoundingSphereVolumePart::GetBoundingBox()
{
	return 0;
}
math::VBoundingSphere* VBoundingSphereVolumePart::GetBoundingSphere()
{
	return &m_BoundingSphere;
}

VBoundingMesh* VBoundingSphereVolumePart::GetBoundingMesh()
{
	return 0;
}

vbool VBoundingSphereVolumePart::HasBoundingMesh()
{
	return false;
}

void VBoundingSphereVolumePart::Activate()
{
	;
}

void VBoundingSphereVolumePart::Deactivate()
{
	;
}

math::VPlane* VBoundingSphereVolumePart::GetBoundingPlane()
{
	return 0;
}

void VBoundingSphereVolumePart::OnMessage(
	const messaging::VMessage& in_Message,
	messaging::VMessage* in_pAnswer)
{
	using std::string;

	if( ! in_Message.HasProperty("type") )
		return;

	const string request = in_Message.GetAs<string>("type");

	if( request == "getSettings" )
	{
		if( in_pAnswer != 0 )
		{
			in_pAnswer->AddProperty("Position", m_BoundingSphere.GetPosition());
			in_pAnswer->AddProperty("Radius", m_BoundingSphere.GetRadius());
		}
	}
	else if( request == "update" )
	{
		const string name = in_Message.GetAs<string>("name");
		//const string val = in_pAnswer->GetAs<string>("value");

		if( name == "Position" )
		{
			VVector3f pos = in_Message.GetAs<VVector3f>("value");
			m_BoundingSphere.SetPosition(pos);

			vout << "BoundingSphere: position set to " << pos << vendl;
		}

		if( name == "Radius" )
		{
			vfloat32 radius = in_Message.GetAs<vfloat32>("value");
			m_BoundingSphere.SetRadius(radius);

			vout << "BoundingSphere: radius set to " << radius << vendl;
		}
	}
}

V3D_REGISTER_PART_PARSER(VBoundingSphereVolumePart);
//-----------------------------------------------------------------------------
} // namespace v3d::
}
//-----------------------------------------------------------------------------

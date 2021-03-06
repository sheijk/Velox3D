/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/Bounding/VBoundingPlaneVolumePart.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace math;

math::VBoundingBox* VBoundingPlaneVolumePart::GetBoundingBox()
{
	return 0;
}
math::VBoundingSphere* VBoundingPlaneVolumePart::GetBoundingSphere()
{
	return 0;
}

VBoundingMesh* VBoundingPlaneVolumePart::GetBoundingMesh()
{
	return 0;
}

vbool VBoundingPlaneVolumePart::HasBoundingMesh()
{
	return false;
}

math::VPlane* VBoundingPlaneVolumePart::GetBoundingPlane()
{
	return &m_Plane;
}
math::VCCylinder* VBoundingPlaneVolumePart::GetBoundingCylinder()
{
  return 0;
}

void VBoundingPlaneVolumePart::OnMessage(
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
			in_pAnswer->AddProperty("Normal", m_Plane.GetNormal());
			in_pAnswer->AddProperty("Distance", m_Plane.GetDistance());
		}
	}
	else if( request == "update" )
	{
		const string name = in_Message.GetAs<string>("name");
		//const string val = in_pAnswer->GetAs<string>("value");

		if( name == "Normal" )
		{
			VVector3f pos = in_Message.GetAs<VVector3f>("value");
			m_Plane.SetNormal(pos);

			vout << "Physics: normal set to " << pos << vendl;
		}

		if( name == "Distance" )
		{
			vfloat32 pos = in_Message.GetAs<vfloat32>("value");
			m_Plane.SetDistance(pos);

			vout << "Physics: distance set to " << pos << vendl;
		}
	}
}

V3D_REGISTER_PART_PARSER(VBoundingPlaneVolumePart);
//-----------------------------------------------------------------------------
}
} // namespace v3d::
//-----------------------------------------------------------------------------


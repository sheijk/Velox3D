/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/Bounding/VBoundingCCylinderVolumePart.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

math::VBoundingBox* VBoundingCCylinderVolumePart::GetBoundingBox()
{
	return 0;
}
math::VBoundingSphere* VBoundingCCylinderVolumePart::GetBoundingSphere()
{
	return 0;
}

VBoundingMesh* VBoundingCCylinderVolumePart::GetBoundingMesh()
{
	return 0;
}
math::VCCylinder* VBoundingCCylinderVolumePart::GetBoundingCylinder()
{
  return &m_BoundingCCylinder;
}

vbool VBoundingCCylinderVolumePart::HasBoundingMesh()
{
	return false;
}

void VBoundingCCylinderVolumePart::Activate()
{
	;
}

void VBoundingCCylinderVolumePart::Deactivate()
{
	;
}

math::VPlane* VBoundingCCylinderVolumePart::GetBoundingPlane()
{
	return 0;
}

void VBoundingCCylinderVolumePart::OnMessage(
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
			in_pAnswer->AddProperty("Length", m_BoundingCCylinder.GetLength());
			in_pAnswer->AddProperty("Radius", m_BoundingCCylinder.GetRadius());
		}
	}
	else if( request == "update" )
	{
		const string name = in_Message.GetAs<string>("name");
		//const string val = in_pAnswer->GetAs<string>("value");

		if( name == "Length" )
		{
			vfloat32 length = in_Message.GetAs<vfloat32>("value");
			m_BoundingCCylinder.SetParams(length, m_BoundingCCylinder.GetRadius());
		}

		if( name == "Radius" )
		{
			vfloat32 radius = in_Message.GetAs<vfloat32>("value");
			m_BoundingCCylinder.SetParams(m_BoundingCCylinder.GetLength(), radius);

			vout << "BoundingSphere: radius set to " << radius << vendl;
		}
	}
}

V3D_REGISTER_PART_PARSER(VBoundingCCylinderVolumePart);
//-----------------------------------------------------------------------------
} // namespace v3d::
}
//-----------------------------------------------------------------------------


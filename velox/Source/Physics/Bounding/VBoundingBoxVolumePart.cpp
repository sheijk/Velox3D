/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Physics/Bounding/VBoundingBoxVolumePart.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

//VBoundingBoxVolumePart::VBoundingBoxVolumePart()
//{
//	;
//}

math::VBoundingBox* VBoundingBoxVolumePart::GetBoundingBox()
{
	return &m_BoundingBox;
}
math::VBoundingSphere* VBoundingBoxVolumePart::GetBoundingSphere()
{
	return 0;
}

VBoundingMesh* VBoundingBoxVolumePart::GetBoundingMesh()
{
	return 0;
}
math::VCCylinder* VBoundingBoxVolumePart::GetBoundingCylinder()
{
  return 0;
}


vbool VBoundingBoxVolumePart::HasBoundingMesh()
{
	return false;
}

math::VPlane* VBoundingBoxVolumePart::GetBoundingPlane()
{
	return 0;
}

void VBoundingBoxVolumePart::Activate()
{
	;
}

void VBoundingBoxVolumePart::Deactivate()
{
	;
}

void VBoundingBoxVolumePart::OnMessage(
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
			in_pAnswer->AddProperty("MinPoint", m_BoundingBox.GetMinPoint());
			in_pAnswer->AddProperty("MaxPoint", m_BoundingBox.GetMaxPoint());
			in_pAnswer->AddProperty("Length",  m_BoundingBox.GetLength());
		}
	}
	else if( request == "update" )
	{
		const string name = in_Message.GetAs<string>("name");
		//const string val = in_pAnswer->GetAs<string>("value");

		if( name == "MinPoint" )
		{
			VVector3f pos = in_Message.GetAs<VVector3f>("value");
			m_BoundingBox.SetMinPoint(pos);

			vout << "BoundingBox: min point set to " << pos << vendl;
		}

		if( name == "MaxPoint" )
		{
			VVector3f pos = in_Message.GetAs<VVector3f>("value");
			m_BoundingBox.SetMaxPoint(pos);

			vout << "BoundingBox: max point set to " << pos << vendl;
		}
	}
}

V3D_REGISTER_PART_PARSER(VBoundingBoxVolumePart);
//-----------------------------------------------------------------------------
}
} // namespace v3d::
//-----------------------------------------------------------------------------


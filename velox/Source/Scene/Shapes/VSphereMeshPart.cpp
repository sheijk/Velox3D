/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/Shapes/VSphereMeshPart.h>
//-----------------------------------------------------------------------------
#include <V3d/OpenGL.h>
#include <GL/glut.h>

#include <v3d/Graphics/IVDevice.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Messaging/VMessageInterpreter.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VSphereMeshPart::VSphereMeshPart(vfloat32 in_fRadius, vuint in_nDetail) :
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
	m_fRadius = in_fRadius;
	m_nDetail = in_nDetail;
}

void VSphereMeshPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	//ApplyParameterValues(in_Device);

	glPushAttrib(GL_NORMALIZE);
	glEnable(GL_NORMALIZE);
	glutSolidSphere(m_fRadius, m_nDetail, m_nDetail);
	glPopAttrib() ;
}

void VSphereMeshPart::OnMessage(const messaging::VMessage& in_Message, 
	messaging::VMessage* in_pAnswer)
{
	static messaging::VMessageInterpreter interpreter;

	if( ! interpreter.IsInitialized() )
	{
		interpreter.AddMemberOption("radius", this, &m_fRadius);
		interpreter.AddMemberOption("detail", this, &m_nDetail);

		interpreter.SetInitialized(true);
	}

	InterpreteMessage(interpreter, in_Message, in_pAnswer);
}

V3D_REGISTER_PART_PARSER(VSphereMeshPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene

//-----------------------------------------------------------------------------


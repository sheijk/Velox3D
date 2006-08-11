#include <V3d/Scene/Shapes/VPlaneMeshPart.h>
//-----------------------------------------------------------------------------

#include <V3d/OpenGL.h>
#include <V3d/Graphics/IVDevice.h>

#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Messaging/VMessageInterpreter.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

VPlaneMeshPart::VPlaneMeshPart(vfloat32 in_fSize) :
	m_fSize(in_fSize),
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
	m_Position = ToVector3f(-in_fSize/2, -2, -in_fSize/2);
	m_Right = ToVector3f(in_fSize, 0, 0);
	m_Up = ToVector3f(0, 0, in_fSize);
}

VPlaneMeshPart::VPlaneMeshPart(
	vfloat32 in_fSize, 
	const std::string& in_strMaterialResource
	) : 
	m_fSize(in_fSize),
	VMeshPartBase(in_strMaterialResource)
{
	m_Position = ToVector3f(-in_fSize/2, -2, -in_fSize/2);
	m_Right = ToVector3f(in_fSize, 0, 0);
	m_Up = ToVector3f(0, 0, in_fSize);
}

namespace {
	void glVertex(const math::VVector3f& vertex)
	{
		glVertex3f(vertex[0], vertex[1], vertex[2]);
	}
}

void VPlaneMeshPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	//ApplyParameterValues(in_Device);

	bool cullFace = glIsEnabled(GL_CULL_FACE) == GL_TRUE;
	glDisable(GL_CULL_FACE);

	glBegin(GL_QUADS);
	//TODO: normal
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glVertex(m_Position);
	glTexCoord2f(1, 0); glVertex(m_Position + m_Right);
	glTexCoord2f(1, 1); glVertex(m_Position + m_Right + m_Up);
	glTexCoord2f(0, 1); glVertex(m_Position + m_Up);
	//glTexCoord2f(1, 1); glVertex(m_Position);
	//glTexCoord2f(0, 1); glVertex(m_Position + m_Right);
	//glTexCoord2f(0, 0); glVertex(m_Position + m_Right + m_Up);
	//glTexCoord2f(1, 0); glVertex(m_Position + m_Up);
	glEnd();

	//const vfloat32 ypos = -2;

	//glBegin(GL_QUADS);
	//glColor3f(1, 1, 1);
	//glVertex3f(-m_fSize, ypos, -m_fSize);
	//glVertex3f(-m_fSize, ypos, m_fSize);
	//glVertex3f(m_fSize, ypos, m_fSize);
	//glVertex3f(m_fSize, ypos, -m_fSize);
	//glEnd();

	if( cullFace )
		glEnable(GL_CULL_FACE);
}

void VPlaneMeshPart::CenterAt(const VVector3f& in_Center)
{
	m_Position = in_Center - ((m_Right + m_Up)*.5f);
}

VVector3f VPlaneMeshPart::GetPosition() const
{
	return m_Position;
}

void VPlaneMeshPart::SetPosition(const VVector3f& in_Position)
{
	m_Position = in_Position;
}

VVector3f VPlaneMeshPart::GetRight() const
{
	return m_Right;
}

void VPlaneMeshPart::SetRight(const VVector3f& in_Right)
{
	m_Right = in_Right;
}

VVector3f VPlaneMeshPart::GetUp() const
{
	return m_Up;
}

void VPlaneMeshPart::SetUp(const VVector3f& in_Up)
{
	m_Up = in_Up;
}

void VPlaneMeshPart::OnMessage(
	const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer)
{
	static messaging::VMessageInterpreter interpreter;

	if( ! interpreter.IsInitialized() )
	{
		interpreter.AddMemberOption("right", this, &m_Right);
		interpreter.AddMemberOption("up", this, &m_Up);
		interpreter.AddMemberOption("pos", this, &m_Position);

		interpreter.SetInitialized(true);
	}

	messaging::VMessageInterpreter::Result result = 
		interpreter.HandleMessage(this, in_Message, in_pAnswer);

	if( result != messaging::VMessageInterpreter::Done )
		VMeshPartBase::OnMessage(in_Message, in_pAnswer);

	//switch(result) {
	//case messaging::VMessageInterpreter::GetSettings:
	//	{
	//		AddVariables(in_pAnswer);
	//	} break;
	//case messaging::VMessageInterpreter::ApplySetting:
	//	{
	//		ApplySetting(in_Message);
	//	} break;
	//}
}

//-----------------------------------------------------------------------------


V3D_REGISTER_PART_PARSER(VPlaneMeshPart);

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

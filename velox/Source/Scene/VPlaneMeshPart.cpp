#include <V3d/Scene/Shapes/VPlaneMeshPart.h>
//-----------------------------------------------------------------------------

#include <V3d/OpenGL.h>
#include <V3d/Graphics/IVDevice.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VPlaneMeshPart::VPlaneMeshPart(vfloat32 in_fSize) :
	m_fSize(in_fSize),
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
}

VPlaneMeshPart::VPlaneMeshPart(
	vfloat32 in_fSize, const std::string& in_strMaterialResource) : 
m_fSize(in_fSize),
VMeshPartBase(in_strMaterialResource)
{
}

void VPlaneMeshPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	const vfloat32 ypos = -2;

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(-m_fSize, ypos, -m_fSize);
	glVertex3f(-m_fSize, ypos, m_fSize);
	glVertex3f(m_fSize, ypos, m_fSize);
	glVertex3f(m_fSize, ypos, -m_fSize);
	glEnd();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

#include <V3d/Graphics/VPointLight.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

VVector3f VPointLight::GetPosition() const
{
	return m_Position;
}

void VPointLight::SetPosition(const VVector3f& in_Position)
{
	m_Position = in_Position;
}

VColor4f VPointLight::GetAmbient() const
{
	return m_Ambient;
}

void VPointLight::SetAmbient(const VColor4f& in_Ambient)
{
	m_Ambient = in_Ambient;
}

VColor4f VPointLight::GetSpecular() const
{
	return m_Specular;
}

void VPointLight::SetSpecular(const VColor4f& in_Specular)
{
	m_Specular = in_Specular;
}

VColor4f VPointLight::GetDiffuse() const
{
	return m_Diffuse;
}

void VPointLight::SetDiffuse(const VColor4f& in_Diffuse)
{
	m_Diffuse = in_Diffuse;
}


//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

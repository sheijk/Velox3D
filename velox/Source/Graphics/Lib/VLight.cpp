#include <V3d/Graphics/VLight.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VLight::VLight()
{
	m_fW = 1.0f;
}

/**
 * d'tor
 */
VLight::~VLight()
{
}

VRangeIterator<IVParameterValue> VLight::Parameters()
{
	return CreateAccesssorIterator<VPair2ndDerefAccessor, IVParameterValue>(
		m_Parameters.begin(), m_Parameters.end());
}

VSharedPtr<IVParameterValue> VLight::GetParameter(const std::string& in_strName)
{
	ParameterMap::iterator param = m_Parameters.find(in_strName);

	if( param != m_Parameters.end() )
	{
		return param->second;
	}
	else
	{
		return SharedPtr<IVParameterValue>(0);
	}
}

void VLight::AddParameter(
	const std::string& in_strName, 
	VSharedPtr<IVParameterValue> in_pParameter)
{
	if( m_Parameters.find(in_strName) == m_Parameters.end() )
	{
		m_Parameters.insert(make_pair(in_strName, in_pParameter));
	}
}

void VLight::ApplyTo(VRangeIterator<IVParameter> in_Parameters)
{
	VRangeIterator<IVParameter> currentParam = in_Parameters;
	while( currentParam.HasNext() )
	{
		const std::string name = currentParam->GetName();
        
		ParameterMap::iterator value = m_Parameters.find(name);

		if( value != m_Parameters.end() )
		{
			value->second->Apply(*currentParam);
		}

		++currentParam;
	}
}

VVector3f VLight::GetPosition() const
{
	return m_Position;
}

void VLight::SetPosition(const VVector3f& in_Position)
{
	m_Position = in_Position;
}


VColor4f VLight::GetAmbientColor() const
{
	return ambientColor;
}

void VLight::SetAmbientColor(const VColor4f& in_AmbientColor)
{
	ambientColor = in_AmbientColor;
}

VColor4f VLight::GetDiffuseColor() const
{
	return diffuseColor;
}

void VLight::SetDiffuseColor(const VColor4f& in_DiffuseColor)
{
	diffuseColor = in_DiffuseColor;
}

VColor4f VLight::GetSpecularColor() const
{
	return specularColor;
}

void VLight::SetSpecularColor(const VColor4f& in_SpecularColor)
{
	specularColor = in_SpecularColor;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

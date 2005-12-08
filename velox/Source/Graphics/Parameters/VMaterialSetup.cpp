#include <V3d/Graphics/Parameters/VMaterialSetup.h>
//-----------------------------------------------------------------------------

#include <V3d/Graphics/Parameters/IVParameterValue.h>
#include <V3d/Graphics/IVMaterial.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VMaterialSetup::VMaterialSetup()
{
}

/**
 * d'tor
 */
VMaterialSetup::~VMaterialSetup()
{
}

void VMaterialSetup::Apply(IVMaterial& io_Material) const
{
	for(NameValueMap::const_iterator value = m_Values.begin();
		value != m_Values.end();
		++value)
	{
		IVParameter* pParam = io_Material.GetParameterByName(value->first);

		if( pParam != 0 )
		{
			value->second->Apply(*pParam);
		}
	}
}

void VMaterialSetup::Add(VStringParam in_strParamName, VSharedPtr<IVParameterValue> in_Value)
{
	m_Values[std::string(in_strParamName)] = in_Value;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

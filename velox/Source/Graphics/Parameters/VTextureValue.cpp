/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Graphics/Parameters/VTextureValue.h>
//-----------------------------------------------------------------------------

#include <V3d/Graphics/IVParameter.h>
#include <V3d/Resource/VResourceId.h>
#include <V3d/Resource/VResource.h>
#include <V3d/Graphics/IVTexture.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VTextureValue::VTextureValue()
{
}

VTextureValue::VTextureValue(const std::string& in_strTextureResource)
{
	m_strTextureResource = in_strTextureResource;
}

void VTextureValue::Apply(const IVParameter& in_Param) const
{
	in_Param.ApplyTexture(m_strTextureResource.c_str());
}

std::string VTextureValue::GetTextureResource() const 
{ 
	return m_strTextureResource; 
}

void VTextureValue::SetTextureResource(const std::string& in_Value)
{
	//if( resource::ExistsResourceData<graphics::IVTexture>(in_Value.c_str()) )
	try
	{
		m_strTextureResource = in_Value;
		resource::GetResourceData<graphics::IVTexture>(in_Value.c_str());
	}
	catch(VException&)
	{
		// no texture for resource, ignore this setting
	}
}

void VTextureValue::Set(const std::string& in_NewValue)
{
	SetTextureResource(in_NewValue);
}

std::string VTextureValue::Get() const
{
	return m_strTextureResource;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------


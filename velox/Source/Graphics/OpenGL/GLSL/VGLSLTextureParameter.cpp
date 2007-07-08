/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VGLSLTextureParameter.h"
//-----------------------------------------------------------------------------

#include <V3d/Resource.h>
#include <V3d/Graphics/OpenGLUtils.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VGLSLTextureParameter::VGLSLTextureParameter(
	GLhandleARB in_hProgram, VStringParam in_strName, vuint in_nTextureUnit)
	: VGLSLParameter(in_hProgram, in_strName, IVParameter::Texture)
{
	m_nTextureUnit = in_nTextureUnit;
	m_bWasFineLastTime = true;
}

/**
 * d'tor
 */
VGLSLTextureParameter::~VGLSLTextureParameter()
{
}

void VGLSLTextureParameter::ApplyTexture(VStringParam in_strResourceName) const
{
	using namespace resource;

	m_pTexture = VResourceDataPtr<IVTexture>();

	if( in_strResourceName != 0 && in_strResourceName[0] != '\0' )
	{
		try
		{
			m_pTexture = GetMutableResourceData<IVTexture>(in_strResourceName);
			m_bWasFineLastTime = true;
		}
		catch(VException&)
		{
			m_bWasFineLastTime = false;
		}

		if( &*m_pTexture == 0 )
			m_pstrTextureResource.Assign(new std::string(in_strResourceName));

		V3D_GLCHECK( glUniform1iARB(GetLocation(), m_nTextureUnit) );	
	}
}

std::string VGLSLTextureParameter::TextureResource() const
{
	if( m_pTexture != 0 && m_pTexture.GetEnclosingResource() != 0 )
		return m_pTexture.GetEnclosingResource()->GetQualifiedName();
	else
		return "";
}

void VGLSLTextureParameter::BindTexture()
{	
	if( m_pstrTextureResource.Get() != 0 )
	{
		try
		{
			std::string newTextureResource = *m_pstrTextureResource;
			m_pTexture = resource::GetMutableResourceData<IVTexture>(newTextureResource.c_str());
			m_pstrTextureResource.Release();
		}
		catch(VException&)
		{}
	}

	if( &*m_pTexture != 0 )
	{
		V3D_GLCHECK( m_pTexture->Bind(m_nTextureUnit) );
	}
}

void VGLSLTextureParameter::UnbindTexture()
{
	if( &*m_pTexture != 0 )
	{
		V3D_GLCHECK( m_pTexture->Unbind() );
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------


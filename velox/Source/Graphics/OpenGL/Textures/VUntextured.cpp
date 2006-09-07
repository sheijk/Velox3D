/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VUntextured.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

VUntextured::VUntextured()
{
	//Dummy
}

VUntextured::VUntextured(const image::VImage& in_Image, int in_TextureID) :  
	VBaseTexture(in_Image, 0)
{
	m_iTextureID = in_TextureID;
}

VUntextured::~VUntextured()
{
	//Dummy
}

void VUntextured::Bind(vuint in_nTextureUnit)
{
	//Dummy
}

void VUntextured::Unbind()
{
	//Dummy
}
//-----------------------------------------------------------------------------
}}// namespace v3d::graphics
//-----------------------------------------------------------------------------


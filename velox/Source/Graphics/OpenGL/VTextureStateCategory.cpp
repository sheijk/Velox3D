#include "VTextureStateCategory.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VTextureStateCategory::VTextureStateCategory()
	: m_DefaultState(VTextureState::NoTexture)
{
}

vfloat32 VTextureStateCategory::GetPriority() const
{
	return .9f;
}

const IVRenderState& VTextureStateCategory::GetDefault() const
{
	return m_DefaultState;
}

VTextureState* VTextureStateCategory::GetTextureState(
	const VMaterialDescription::TextureRef& in_Ref)
{
	TextureMap::iterator texIter = m_Textures.find(in_Ref.hData);

	// if texture already exists
	if( texIter != m_Textures.end() )
	{
		// return it
		return texIter->second;
	}
	// if texture does not exist
	else
	{
		// create it
		return CreateTextureState(in_Ref);
	}
}

VTextureState* VTextureStateCategory::CreateTextureState(
	const VMaterialDescription::TextureRef& in_Ref)
{
	V3D_ASSERT(in_Ref.hData != 0);
	V3D_ASSERT(in_Ref.nWidth > 0);
	V3D_ASSERT(in_Ref.nHeight > 0);
	V3D_ASSERT(in_Ref.hData->GetDataAddress() != 0);

	vbyte* temp = in_Ref.hData->GetDataAddress();

	// look if in_Refture already exists
	// if it doesn't, create it

	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glPixelStorei  (GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR);
	glTexEnvi	   (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);

	gluBuild2DMipmaps(
		GL_TEXTURE_2D, 
		GL_RGB, 
		in_Ref.nWidth, 
		in_Ref.nHeight,
		GL_RGB,
		GL_UNSIGNED_BYTE, 
		in_Ref.hData->GetDataAddress()
		);

	VTextureState* pTexState = new VTextureState(id);

	// store texure
	m_Textures[in_Ref.hData] = pTexState;

	return pTexState;
}

VTextureState* VTextureStateCategory::CreateState(const VMaterialDescription& in_Descr)
{
	// if a texture exists
	if( in_Descr.pTextureList == 0 )
	{
		return &m_DefaultState;
	}
	else
	{
		//const VMaterialDescription::TextureRef& tex(*in_Descr.pTextureList);
		//VTextureState* pState = new VTextureState(id);

		//GLint texId = GetTextureId(*in_Descr.pTextureList);

		//VTextureState* pState = new VTextureState(texId);

		return GetTextureState(*in_Descr.pTextureList);
	}
}


//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------

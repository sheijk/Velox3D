#include "VTextureStateCategory.h"
//-----------------------------------------------------------------------------
#include <v3d/Graphics/GraphicsExceptions.h>

#include <V3dLib/Graphics/Materials/StateTypes.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
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
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_S,
		GetGLModeNum(in_Ref.wrapTexCoordU) );
    glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_T,
		GetGLModeNum(in_Ref.wrapTexCoordV) );
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,
		GetGLModeNum(in_Ref.minificationFilter) );
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,
		GetGLModeNum(in_Ref.magnificationFilter) );
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
		return GetTextureState(*in_Descr.pTextureList);
	}
}

VTextureState* VTextureStateCategory::CreateState(const VRenderPass& in_Pass)
{
	// if a texture is specified
	VState const* pTextureState = in_Pass.GetStateByName("texture");
	if( pTextureState != 0 )
	{
		// if a texture is referenced by file name, load it using the image service
		if( pTextureState->ContainsParameter("file") )
		{
			//// load image
			//std::string imageFileName;
			//pTextureState->GetParameter("file", imageFileName);

			//VServicePtr<image::IVImageFactory> pImageService;
			//image::IVImageFactory::ImagePtr pImage =
			//	pImageService->CreateImage(imageFileName.c_str());

			//// create buffer
			vbool notImplementedYet = false;
			V3D_ASSERT(notImplementedYet);

			return 0;
		}
		// if a texture is referenced by a buffer id, get and check it
		else if( pTextureState->ContainsParameter("bufferref") )
		{
			VMaterialDescription::TextureRef texRef;
			void* hBuffer = 0;
			pTextureState->GetParameter<void*>("bufferref", hBuffer);
			texRef.hData = static_cast<VMaterialDescription::ByteBufferHandle>(hBuffer);
			pTextureState->GetParameter("width", texRef.nWidth);
			pTextureState->GetParameter("height", texRef.nHeight);

			VTextureFilter magnification, minification;
			pTextureState->GetParameter("magnification.filter", magnification);
			texRef.magnificationFilter = (VMaterialDescription::TextureFilter)magnification;
			pTextureState->GetParameter("minification.filter", minification);
			texRef.minificationFilter = (VMaterialDescription::TextureFilter)minification;

			VTextureWrapMode wrapu, wrapv;
			pTextureState->GetParameter("wrapu", wrapu);
			texRef.wrapTexCoordU = (VMaterialDescription::TextureWrapMode)wrapu;
			pTextureState->GetParameter("wrapv", wrapv);
			texRef.wrapTexCoordV = (VMaterialDescription::TextureWrapMode)wrapv;

			return GetTextureState(texRef);
		}
		// necessary state parameters are missing
		else
		{
			V3D_THROW(VMissingStateParameterException, "The effect description "
				"contained a 'texture' state which is missing 'file' or "
				"buffer reference parameters");
		}
	}
	else
	{
		return &m_DefaultState;
	}
}

vuint VTextureStateCategory::GetGLModeNum(const TextureFilter in_Filer)
{
	switch( in_Filer )
	{
	case VMaterialDescription::FilterNearest:				return GL_NEAREST;
	case VMaterialDescription::FilterLinear:				return GL_LINEAR;
	case VMaterialDescription::FilterNearestMipmapNearest:	return GL_NEAREST_MIPMAP_NEAREST;
	case VMaterialDescription::FilterLinearMipmapNearest:	return GL_LINEAR_MIPMAP_NEAREST;
	case VMaterialDescription::FilterNearestMipmapLinear:	return GL_NEAREST_MIPMAP_LINEAR;  
	case VMaterialDescription::FilterLinearMipmapLinear:	return GL_LINEAR_MIPMAP_LINEAR;
	};

	V3D_THROW(VException, "illegal texture filter");
}

vuint VTextureStateCategory::GetGLModeNum(const TextureWrapMode  in_WrapMode)
{
	switch( in_WrapMode )
	{
	case VMaterialDescription::TextureRepeat:	return GL_REPEAT;
	case VMaterialDescription::TextureClamp:	return GL_CLAMP;
	}

	V3D_THROW(VException, "illegal texture wrapping mode");
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------

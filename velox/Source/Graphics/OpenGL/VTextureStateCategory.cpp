#include "VTextureStateCategory.h"
//-----------------------------------------------------------------------------
#include <v3d/Graphics/GraphicsExceptions.h>

#include <V3dLib/Graphics/Materials/StateTypes.h>
#include "VCubemapTextureState.h"

#include <V3d/Image/VImage.h>
#include <V3d/Resource.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d::resource;

V3D_DECLARE_EXCEPTION(VInvalidEffectDescriptionException, VGraphicException);

VTextureStateCategory::VTextureStateCategory()
	: m_DefaultState()
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

VTextureState2D* VTextureStateCategory::GetTextureState(
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

VTextureState2D* VTextureStateCategory::CreateTextureState(
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

	VTextureState2D* pTexState = new VTextureState2D(id);

	// store texure
	m_Textures[in_Ref.hData] = pTexState;

	return pTexState;
}

VTextureState2D* VTextureStateCategory::Create2DState(const VState* in_pTextureState)
{
	// if a texture is referenced by resource name
	if( in_pTextureState->ContainsParameter("res") )
	{
		using namespace resource;

		std::string resName;
		in_pTextureState->GetParameter("res", resName);

		// get texture state
		VResourceManagerPtr pResMan;

		VResourceId pRes = pResMan->GetResourceByName(resName.c_str());
		VResourceDataPtr<const VTextureState2D> pState = 
			pRes->GetData<VTextureState2D>();

		return const_cast<VTextureState2D*>(&* pState);
	}
	// if a texture is referenced by a buffer id, get and check it
	if( in_pTextureState->ContainsParameter("bufferref") )
	{
		VMaterialDescription::TextureRef texRef;
		void* hBuffer = 0;
		in_pTextureState->GetParameter<void*>("bufferref", hBuffer);
		texRef.hData = static_cast<VMaterialDescription::ByteBufferHandle>(hBuffer);
		in_pTextureState->GetParameter("width", texRef.nWidth);
		in_pTextureState->GetParameter("height", texRef.nHeight);

		VTextureFilter magnification, minification;
		in_pTextureState->GetParameter("magnification.filter", magnification);
		texRef.magnificationFilter = (VMaterialDescription::TextureFilter)magnification;
		in_pTextureState->GetParameter("minification.filter", minification);
		texRef.minificationFilter = (VMaterialDescription::TextureFilter)minification;

		VTextureWrapMode wrapu, wrapv;
		in_pTextureState->GetParameter("wrapu", wrapu);
		texRef.wrapTexCoordU = (VMaterialDescription::TextureWrapMode)wrapu;
		in_pTextureState->GetParameter("wrapv", wrapv);
		texRef.wrapTexCoordV = (VMaterialDescription::TextureWrapMode)wrapv;

		return GetTextureState(texRef);
	}
	// necessary state parameters are missing
	else
	{
		V3D_THROW(VMissingStateParameterException, "The effect description "
			"contained a 'texture' state which is missing 'res' "
			"reference parameters referencing a resource where the texture "
			"is located");
	}
}

template<typename DataType>
VResourceDataPtr<const DataType> GetDataFromResource(VStringParam in_strResName)
{
	VResourceId res = VResourceManagerPtr()->GetResourceByName(in_strResName);
	VResourceDataPtr<const DataType> data = res->GetData<DataType>();
	return data;
}

IVRenderState* VTextureStateCategory::CreateCubeMapState(
	const VState* in_pTextureState)
{
	using std::string;
	IVRenderState* pCubemapState = 0;

	if( in_pTextureState->ContainsParameter("posx") &&
		in_pTextureState->ContainsParameter("posy") &&
		in_pTextureState->ContainsParameter("posz") &&
		in_pTextureState->ContainsParameter("negx") &&
		in_pTextureState->ContainsParameter("negy") &&
		in_pTextureState->ContainsParameter("negz") )
	{
		// get states and state names for each side from resource manager
		string posxRes;
		in_pTextureState->GetParameter("posx", posxRes);
		VResourceDataPtr<const VTextureStatePosX> pPosXState = 
			GetDataFromResource<VTextureStatePosX>(posxRes.c_str());

		string posyRes;
		in_pTextureState->GetParameter("posy", posyRes);
		VResourceDataPtr<const VTextureStatePosY> pPosYState = 
			GetDataFromResource<VTextureStatePosY>(posyRes.c_str());

		string poszRes;
		in_pTextureState->GetParameter("posz", poszRes);
		VResourceDataPtr<const VTextureStatePosZ> pPosZState = 
			GetDataFromResource<VTextureStatePosZ>(poszRes.c_str());

		string negxRes;
		in_pTextureState->GetParameter("negx", negxRes);
		VResourceDataPtr<const VTextureStateNegX> pNegXState = 
			GetDataFromResource<VTextureStateNegX>(negxRes.c_str());

		string negyRes;
		in_pTextureState->GetParameter("negy", negyRes);
		VResourceDataPtr<const VTextureStateNegY> pNegYState = 
			GetDataFromResource<VTextureStateNegY>(negyRes.c_str());

		string negzRes;
		in_pTextureState->GetParameter("negz", negzRes);
		VResourceDataPtr<const VTextureStateNegZ> pNegZState = 
			GetDataFromResource<VTextureStateNegZ>(negzRes.c_str());

		// create a new state for the cube map
		pCubemapState = new VCubemapTextureState(
			pPosXState, pPosYState, pPosZState,
			pNegXState, pNegYState, pNegZState);
	}
	else
	{
		V3D_THROW(VInvalidEffectDescriptionException,
			"CubeMap texture effect description's node 'texture' must contain "
			"attributes named '[pos/neg][x/y/z]' which reference the six cube "
			"map textures");
	}

	V3D_ASSERT(0 != pCubemapState);
	return pCubemapState;
}

IVRenderState* VTextureStateCategory::CreateState(const VRenderPass& in_Pass)
{
	// if a texture is specified
	VState const* pTextureState = in_Pass.GetStateByName("texture");
	if( pTextureState != 0 )
	{
		// determine texture type
		std::string textureType = "2d";
		if( pTextureState->ContainsParameter("type") )
		{
			pTextureState->GetParameter("type", textureType);
		}

		if( textureType == "2d" )
		{
			return Create2DState(pTextureState);
		}
		if( textureType == "cubeMap" )
		{
			return CreateCubeMapState(pTextureState);			
		}
		else
		{
			V3D_THROW(VInvalidEffectDescriptionException,
				"Type 'TODO' is an invalid texture type");
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

#include "VTextureStateResType.h"
//-----------------------------------------------------------------------------

#include <v3d/Image/VImage.h>

#include <V3dLib/Graphics/Materials/StateTypes.h>
#include <V3dLib/Graphics/Materials/VModeTypeInfo.h>
#include "../../Graphics/OpenGL/VTextureState.h"

#include <V3d/OpenGL.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::resource;
using namespace v3d::image;

//-----------------------------------------------------------------------------
/**
 * Options for creation of a texture
 *
 * @author sheijk
 */
class VTextureOptions
{
public:
	VTextureOptions();

	VTextureOptions(
		VTextureFilter in_MagnificationFilter,
		VTextureFilter in_MinificationFilter,
		VTextureWrapMode in_WrapModeU,
		VTextureWrapMode in_WrapModeV
		);

	VTextureFilter GetMagnificationFilter() const;
	VTextureFilter GetMinificationFilter() const;

	VTextureWrapMode GetTextureWrapModeU() const;
	VTextureWrapMode GetTextureWrapModeV() const;
	
private:
	VTextureFilter m_MagnificationFilter;
	VTextureFilter m_MinificationFilter;

	VTextureWrapMode m_TextureWrapModeU;
	VTextureWrapMode m_TextureWrapModeV;
};

VTextureOptions::VTextureOptions()
{
	m_MagnificationFilter = FilterLinear;
	m_MinificationFilter = FilterLinear;
	m_TextureWrapModeU = TextureRepeat;
	m_TextureWrapModeV = TextureRepeat;
}

VTextureOptions::VTextureOptions(
	VTextureFilter in_MagnificationFilter,
	VTextureFilter in_MinificationFilter,
	VTextureWrapMode in_WrapModeU,
	VTextureWrapMode in_WrapModeV
	)
{
	m_MagnificationFilter = in_MagnificationFilter;
	m_MinificationFilter = in_MinificationFilter;
	m_TextureWrapModeU = in_WrapModeU;
	m_TextureWrapModeV = in_WrapModeV;
}

VTextureFilter VTextureOptions::GetMagnificationFilter() const
{
	return m_MagnificationFilter;
}

VTextureFilter VTextureOptions::GetMinificationFilter() const
{
	return m_MinificationFilter;
}

VTextureWrapMode VTextureOptions::GetTextureWrapModeU() const
{
	return m_TextureWrapModeU;
}

VTextureWrapMode VTextureOptions::GetTextureWrapModeV() const
{
	return m_TextureWrapModeV;
}

//-----------------------------------------------------------------------------

namespace {
	vuint GetGLModeNum(const VTextureFilter in_Filer)
	{
		switch( in_Filer )
		{
		case FilterNearest:				return GL_NEAREST;
		case FilterLinear:				return GL_LINEAR;
		case FilterNearestMipmapNearest:	return GL_NEAREST_MIPMAP_NEAREST;
		case FilterLinearMipmapNearest:	return GL_LINEAR_MIPMAP_NEAREST;
		case FilterNearestMipmapLinear:	return GL_NEAREST_MIPMAP_LINEAR;  
		case FilterLinearMipmapLinear:	return GL_LINEAR_MIPMAP_LINEAR;
		};

		V3D_THROW(VException, "illegal texture filter");
	}

	vuint GetGLModeNum(const VTextureWrapMode in_WrapMode)
	{
		return GetTextureWrapModeInfo().GetGLEnum(in_WrapMode);
		//switch( in_WrapMode )
		//{
		//case TextureRepeat:	return GL_REPEAT;
		//case TextureClamp:	return GL_CLAMP;
		//}

		//V3D_THROW(VException, "illegal texture wrapping mode");
	}

	IVRenderState* CreateTextureState(
		const image::VImage& image,
        const VTextureOptions& in_Options,
		const GLenum in_TextureTarget
		)
	{
		V3D_ASSERT(image.GetWidth() > 0);
		V3D_ASSERT(image.GetHeight() > 0);
		V3D_ASSERT(image.GetPixelData() != 0);

		const vbyte* temp = image.GetPixelData();

		GLuint id;
		glGenTextures(1, &id);
		glBindTexture(in_TextureTarget, id);

		//TODO: optionen fuer texturen.. muessen pro textur unterschiedlich
		// deshalb wird wrap mode etc ignoriert
		// sein, anstatt pro bild...
		glPixelStorei  (GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(
			in_TextureTarget,
			GL_TEXTURE_WRAP_S,
			GL_CLAMP_TO_EDGE
			//GetGLModeNum(in_Options.GetTextureWrapModeU()) 
			);
		glTexParameteri(
			in_TextureTarget,
			GL_TEXTURE_WRAP_T,
			GL_CLAMP_TO_EDGE
			//GetGLModeNum(in_Options.GetTextureWrapModeV()) 
			);
		glTexParameteri(
			in_TextureTarget,
			GL_TEXTURE_MIN_FILTER,
			GetGLModeNum(in_Options.GetMinificationFilter()) );
		glTexParameteri(
			in_TextureTarget,
			GL_TEXTURE_MAG_FILTER,
			GetGLModeNum(in_Options.GetMagnificationFilter()) );
		glTexEnvi	   (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);

		gluBuild2DMipmaps(
			in_TextureTarget, 
			GL_RGB, 
			image.GetWidth(), 
			image.GetHeight(),
			GL_RGB,
			GL_UNSIGNED_BYTE, 
			image.GetPixelData()
			);

		switch(in_TextureTarget)
		{
			case GL_TEXTURE_2D: return reinterpret_cast<IVRenderState*>(new VTexture2D(image, id));
			case GL_TEXTURE_CUBE_MAP_POSITIVE_X: return reinterpret_cast<IVRenderState*>(new VCubemapPosX(image, id));
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_X: return reinterpret_cast<IVRenderState*>(new VCubemapNegX(image, id));
			case GL_TEXTURE_CUBE_MAP_POSITIVE_Y: return reinterpret_cast<IVRenderState*>(new VCubemapPosY(image, id));
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y: return reinterpret_cast<IVRenderState*>(new VCubemapNegY(image, id));
			case GL_TEXTURE_CUBE_MAP_POSITIVE_Z: return reinterpret_cast<IVRenderState*>(new VCubemapPosZ(image, id));
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z: return reinterpret_cast<IVRenderState*>(new VCubemapNegZ(image, id));
		}
	}
} // anomymous namespace

/**
 * standard c'tor
 */
VTextureStateResType::VTextureStateResType()
{
	m_TextureTargets[VTypeId::Create<VTexture2D>()] = GL_TEXTURE_2D;
	m_TextureTargets[VTypeId::Create<VCubemapPosX>()] = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
	m_TextureTargets[VTypeId::Create<VCubemapNegX>()] = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
	m_TextureTargets[VTypeId::Create<VCubemapPosY>()] = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
	m_TextureTargets[VTypeId::Create<VCubemapNegY>()] = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
	m_TextureTargets[VTypeId::Create<VCubemapPosZ>()] = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
	m_TextureTargets[VTypeId::Create<VCubemapNegZ>()] = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;

	for(TextureTargetMap::iterator it = m_TextureTargets.begin();
		it != m_TextureTargets.end();
		++it)
	{
		m_ManagedTypes.push_back(it->first);
	}
}

/**
 * d'tor
 */
VTextureStateResType::~VTextureStateResType()
{
}

GLenum VTextureStateResType::GetTextureTarget(resource::VTypeId in_Type) const
{
	std::map<resource::VTypeId, GLenum>::const_iterator it;
	it = m_TextureTargets.find(in_Type);
	V3D_ASSERT(it != m_TextureTargets.end());
	return it->second;
}

VRangeIterator<VTypeId> VTextureStateResType::CreatedTypes()
{
	return CreateBeginIterator< std::vector<resource::VTypeId> >(m_ManagedTypes);
}

vbool VTextureStateResType::Generate(
	resource::VResource* in_pResource,
	resource::VTypeId in_Type)
{
	V3D_ASSERT(std::find(m_ManagedTypes.begin(), m_ManagedTypes.end(), in_Type) 
		!= m_ManagedTypes.end());
//	V3D_ASSERT(resource::VTypeId::Create<VTextureState2D>() == in_Type);

	// if texture state does not exist, yet

	if( ! in_pResource->ContainsData(in_Type) )
	//if( ! in_pResource->ContainsData<VTextureState>() )
	{
		VResourceDataPtr<const VImage> pImage;

		// get VImage for resource
		try
		{
			pImage = in_pResource->GetData<VImage>();
		}
		catch(resource::VDataNotFoundException&)
		{
			return false;
		}

		// try to get texture options
		VTextureOptions options;

		try
		{
			VResourceDataPtr<const VTextureOptions> pOptions = 
				in_pResource->GetData<VTextureOptions>();

			options = *pOptions;
		}
		catch(resource::VDataNotFoundException&)
		{
		}

		// determine texture target
		GLenum target = GetTextureTarget(in_Type);

		// create opengl texture state from it
		in_pResource->AddDynamicTypedData(CreateTextureState(*pImage, options, target));

		//in_pResource->DumpInfo(":::");
	}

	return true;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

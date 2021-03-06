/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VTextureStateResType.h"
//-----------------------------------------------------------------------------

#include <V3d/Image/VImage.h>
#include <V3d/Graphics/Materials/StateTypes.h>
#include <V3d/Graphics/Materials/VModeTypeInfo.h>
#include "../../Graphics/OpenGL/VTextureState.h"

#include "../../Graphics/OpenGL/Textures/VCubeMapTexture.h"

#include <V3d/OpenGL.h>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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

}} // namespace v3d::graphics
V3D_TYPEINFO(v3d::graphics::VTextureOptions);
namespace v3d { namespace graphics {

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

	GLenum FormatForBPP(vuint bpp)
	{
		switch(bpp)
		{
		case 8: return GL_LUMINANCE;
		//case 16: return GL_RGB;
		case 24: return GL_RGB;
		case 32: return GL_RGBA;
		default: V3D_THROWMSG(VException, "no support for textures with "
					 << bpp << " bits per pixel");
		}
	}

	VTexture2D* CreateTexture2D(
		const image::VImage& image,
        const VTextureOptions& in_Options,
		const GLenum in_TextureTarget
		)
	{
		V3D_ASSERT(image.GetWidth() > 0);
		V3D_ASSERT(image.GetHeight() > 0);
		V3D_ASSERT(image.GetPixelData() != 0);
		V3D_ASSERT(image.GetBitsPerPixel() % 8 == 0);
		V3D_ASSERT(image.GetBitsPerPixel() >= 8);
		V3D_ASSERT(image.GetBitsPerPixel() <= 32);

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
			image.GetBitsPerPixel() / 8,
			image.GetWidth(), 
			image.GetHeight(),
			FormatForBPP(image.GetBitsPerPixel()),
			GL_UNSIGNED_BYTE, 
			image.GetPixelData()
			);

		VTexture2D* pTexture = 0;

		switch(in_TextureTarget)
		{
			case GL_TEXTURE_2D: pTexture = new VTexture2D(image, id);
			//case GL_TEXTURE_CUBE_MAP_POSITIVE_X: pTexture = new VCubemapPosX(image, id);
			//case GL_TEXTURE_CUBE_MAP_NEGATIVE_X: pTexture = new VCubemapNegX(image, id);
			//case GL_TEXTURE_CUBE_MAP_POSITIVE_Y: pTexture = new VCubemapPosY(image, id);
			//case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y: pTexture = new VCubemapNegY(image, id);
			//case GL_TEXTURE_CUBE_MAP_POSITIVE_Z: pTexture = new VCubemapPosZ(image, id);
			//case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z: pTexture = new VCubemapNegZ(image, id);
		}

		if( pTexture != 0 )
		{
			//TODO: VTexture2D anstatt IVRenderState in der resource speichern
			return pTexture;
			//return new VTextureState(pTexture);
		}
		else
		{
			V3D_THROWMSG(VGraphicException, 
				"Could not create texture state of type " << in_TextureTarget
				<< ": invalid target type");
		}
	}
} // anomymous namespace

/**
 * standard c'tor
 */
VTextureStateResType::VTextureStateResType()
{
	m_TextureTargets[GetTypeInfo<VTexture2D>()] = GL_TEXTURE_2D;
	m_TextureTargets[GetTypeInfo<IVTexture>()] = GL_TEXTURE_2D;
	m_TextureTargets[GetTypeInfo<VCubeMapTexture>()] = GL_TEXTURE_CUBE_MAP;

	//m_TextureTargets[VTypeId::Create<VCubemapPosX>()] = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
	//m_TextureTargets[VTypeId::Create<VCubemapNegX>()] = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
	//m_TextureTargets[VTypeId::Create<VCubemapPosY>()] = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
	//m_TextureTargets[VTypeId::Create<VCubemapNegY>()] = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
	//m_TextureTargets[VTypeId::Create<VCubemapPosZ>()] = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
	//m_TextureTargets[VTypeId::Create<VCubemapNegZ>()] = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;

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

GLenum VTextureStateResType::GetTextureTarget(VTypeInfo in_Type) const
{
	std::map<VTypeInfo, GLenum>::const_iterator it;
	it = m_TextureTargets.find(in_Type);
	V3D_ASSERT(it != m_TextureTargets.end());
	return it->second;
}

VRangeIterator<VTypeInfo> VTextureStateResType::CreatedTypes()
{
	return CreateBeginIterator< std::vector<VTypeInfo> >(m_ManagedTypes);
}

VRangeIterator<VTypeInfo> VTextureStateResType::ManagedTypes()
{
	return CreatedTypes();
}

vbool VTextureStateResType::Create2DTexture(VResource* in_pResource, const VTypeInfo& in_Type)
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
	in_pResource->AddData<VTexture2D>(CreateTexture2D(*pImage, options, target));

	return true;
}

namespace {
	VResource* ChildOrException(VResource* in_pResource, const std::string& name) 
	{
		VResource* res = in_pResource->GetSubResource(name);

		if( res == 0 )
		{
			V3D_THROWMSG( VResourceException, 
				"Could not find child '" << name << "' of resource '"
				<< in_pResource->GetQualifiedName() << "'" );
		}
		else
		{
			return res;
		}
	}
}

vbool VTextureStateResType::CreateCubeTexture(VResource* in_pResource, const VTypeInfo& in_Type)
{
	VResourceDataPtr<const VImage> left = ChildOrException(in_pResource, "left.jpg")->GetData<VImage>();
	VResourceDataPtr<const VImage> right = ChildOrException(in_pResource, "right.jpg")->GetData<VImage>();
	VResourceDataPtr<const VImage> top = ChildOrException(in_pResource, "top.jpg")->GetData<VImage>();
	VResourceDataPtr<const VImage> bottom = ChildOrException(in_pResource, "bottom.jpg")->GetData<VImage>();
	VResourceDataPtr<const VImage> front = ChildOrException(in_pResource, "front.jpg")->GetData<VImage>();
	VResourceDataPtr<const VImage> back = ChildOrException(in_pResource, "back.jpg")->GetData<VImage>();

	std::auto_ptr<VCubeMapTexture> cubemap( new VCubeMapTexture(
		*front, *back, *left, *right, *top, *bottom) );

	in_pResource->AddData<VCubeMapTexture>( cubemap.release() );

	return true;
}

vbool VTextureStateResType::Generate(
	resource::VResource* in_pResource,
	VTypeInfo in_Type)
{
	// if texture state does not exist, yet
	if( ! in_pResource->ContainsData(in_Type) )
	{
		if( in_Type == GetTypeInfo<VTexture2D>() )
		{
			return Create2DTexture( in_pResource, in_Type );
		}
		else if( in_Type == GetTypeInfo<VCubeMapTexture>() )
		{
			return CreateCubeTexture( in_pResource, in_Type );
		}
		else if( in_Type == GetTypeInfo<IVTexture>() )
		{
			vbool createdTexture = false;
			
			if( ! createdTexture )
			{
				createdTexture = Create2DTexture( in_pResource, in_Type );
			}

			if( ! createdTexture )
			{
				createdTexture = CreateCubeTexture( in_pResource, in_Type );
			}

			return createdTexture;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

vbool VTextureStateResType::AllowMutableAccess(
	const VTypeInfo& in_TypeInfo, 
	const resource::VResource* in_Resource) const
{
	return true;
}

void VTextureStateResType::NotifyChange(
	const VTypeInfo& in_Type, resource::VResource* in_pResource)
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

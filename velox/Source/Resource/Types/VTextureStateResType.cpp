#include "VTextureStateResType.h"
//-----------------------------------------------------------------------------

#include <v3d/Image/VImage.h>

#include <V3dLib/Graphics/Materials/StateTypes.h>
#include "../../Graphics/OpenGL/VTextureState.h"

#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>

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
		switch( in_WrapMode )
		{
		case TextureRepeat:	return GL_REPEAT;
		case TextureClamp:	return GL_CLAMP;
		}

		V3D_THROW(VException, "illegal texture wrapping mode");
	}

	VTextureState* CreateTextureState(
		const image::VImage& image,
        const VTextureOptions& in_Options
		)
	{
		V3D_ASSERT(image.GetWidth() > 0);
		V3D_ASSERT(image.GetHeight() > 0);
		V3D_ASSERT(image.GetPixelData() != 0);

		const vbyte* temp = image.GetPixelData();

		GLuint id;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		//TODO: optionen fuer texturen.. muessen pro textur unterschiedlich
		// sein, anstatt pro bild...
		glPixelStorei  (GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_WRAP_S,
			GetGLModeNum(in_Options.GetTextureWrapModeU()) );
		glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_WRAP_T,
			GetGLModeNum(in_Options.GetTextureWrapModeV()) );
		glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER,
			GetGLModeNum(in_Options.GetMinificationFilter()) );
		glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_MAG_FILTER,
			GetGLModeNum(in_Options.GetMagnificationFilter()) );
		glTexEnvi	   (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);

		gluBuild2DMipmaps(
			GL_TEXTURE_2D, 
			GL_RGB, 
			image.GetWidth(), 
			image.GetHeight(),
			GL_RGB,
			GL_UNSIGNED_BYTE, 
			image.GetPixelData()
			);

		VTextureState* pTexState = new VTextureState(id);

		return pTexState;
	}
} // anomymous namespace

/**
 * standard c'tor
 */
VTextureStateResType::VTextureStateResType()
{
}

/**
 * d'tor
 */
VTextureStateResType::~VTextureStateResType()
{
}

resource::VResourceData::TypeId VTextureStateResType::GetTypeId() const
{
	return resource::VResource::GetTypeId<VTextureState>();
}

vbool VTextureStateResType::Generate(resource::VResource* in_pResource)
{
	// if texture state does not exist, yet
	if( ! in_pResource->ContainsData<VTextureState>() )
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

		// create opengl texture state from it
		in_pResource->AddData(CreateTextureState(*pImage, options));
	}

	return true;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

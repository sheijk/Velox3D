#ifndef V3D_VTEXTURESTATECATEGORY_H
#define V3D_VTEXTURESTATECATEGORY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include "VTextureState.h"

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class VTextureStateCategory : public IVStateCategory
{
	VTextureState m_DefaultState;
public:
	VTextureStateCategory() : m_DefaultState(VTextureState::NoTexture)
	{
	}

	virtual vfloat32 GetPriority() const
	{
		return .9f;
	}

	virtual const IVRenderState& GetDefault() const
	{
		return m_DefaultState;
	}

	VTextureState* CreateState(const VMaterialDescription& in_Descr)
	{
		// if a texture exists
		if( in_Descr.pTextureList == 0 )
		{
			return &m_DefaultState;
		}
		else
		{
			const VMaterialDescription::TextureRef& tex(*in_Descr.pTextureList);

			V3D_ASSERT(tex.hData != 0);
			V3D_ASSERT(tex.nWidth > 0);
			V3D_ASSERT(tex.nHeight > 0);
			V3D_ASSERT(tex.hData->GetDataAddress() != 0);

			vbyte* temp = tex.hData->GetDataAddress();

			// look if texture already exists
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
				tex.nWidth, 
				tex.nHeight,
				GL_RGB,
				GL_UNSIGNED_BYTE, 
				tex.hData->GetDataAddress()
				);

			VTextureState* pState = new VTextureState(id);
			return pState;
		}
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURESTATECATEGORY_H

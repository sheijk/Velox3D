#ifndef V3D_VMATERIALDESCRIPTION_H
#define V3D_VMATERIALDESCRIPTION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VMeshDescription.h>
#include <v3d/Utils/Graphics/VColor4f.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // f***in' VC auto indent ;)

struct VMaterialDescription
{
	// types

	typedef VMeshDescription::ByteBufferHandle ByteBufferHandle;

	/**
	 * The polygon mode for rendering.
	 * Filled means normal
	 * Point means render vertices as points
	 * Line means wireframe
	 */
    enum PolygonMode
	{
		Filled, Point, Line
	};

	/**
	 * The depth buffer test mode
	 */
	enum DepthTest
	{
		DepthAlways,
		DepthOnLess,
		DepthOnLessEqual,
		DepthOnGreater,
		DepthOnGreaterEqual,
		DepthNever,
		DepthOnEqual,
		DepthOnNotEqual
	};

	/**
	 * The depth buffer write mode
	 */
	enum DepthMask
	{
		DepthWrite,
		DepthReadOnly
	};

	/**
	 * A reference to a texture
	 * add references to more textures using AddTexture for mult texturing
	 */
	struct TextureRef
	{
		vuint nWidth, nHeight;
		ByteBufferHandle hData;

		TextureRef* pNext;
	};

	// data

	PolygonMode frontPolyMode;
	PolygonMode backPolyMode;

	TextureRef* pTextureList;

	v3d::utils::graphics::VColor4f defaultColor;

	// functions

	// setting sensible default values
	VMaterialDescription() :
		frontPolyMode(Filled),
		backPolyMode(Filled),
		pTextureList(0),
		defaultColor(1, 1, 1, 1)
	{
	}

	void AddTexture(TextureRef* in_pTexture)
	{
		if( pTextureList == 0 )
		{
			pTextureList = in_pTexture;
		}
		else
		{
			// append at the end
			TextureRef* pTex = pTextureList;
			while(pTex->pNext != 0)
			{
				pTex = pTex->pNext;
			}
			pTex->pNext = in_pTexture;
		}
	}
};

//-----------------------------------------------------------------------------
} // namepace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMATERIALDESCRIPTION_H

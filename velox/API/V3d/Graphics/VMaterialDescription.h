
#ifndef V3D_VMATERIALDESCRIPTION_H
#define V3D_VMATERIALDESCRIPTION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VMeshDescription.h>
#include <V3dLib/Graphics/Geometry/VColor4f.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // f***in' VC auto indent ;)

struct VMaterialDescription
{
	// types

	typedef VMeshDescription::BufferHandle ByteBufferHandle;

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
	 * Blending factors
	 */
	enum BlendFactor
	{
		BlendZero,
		BlendOne,
		BlendSourceColor,
		BlendOneMinusSourceColor,
		BlendDestColor,
		BlendOneMinusDestColor,
		BlendSourceAlpha,
		BlendOneMinusSourceAlpha,
		BlendDestAlpha,
		BlendOneMinusDepthAlpha,
		BlendSourceAlphaSaturate
	};

	/**
	 * Handling of texture coordinates outside the range [0,1]
	 */
	enum TextureWrapMode
	{
		TextureRepeat,
		TextureClamp
	};

	/**
	 * Filtering of textures for minification/magnification
	 */
	enum TextureFilter
	{
		FilterNearest,
		FilterLinear,
		FilterNearestMipmapNearest,
		FilterLinearMipmapNearest,
		FilterNearestMipmapLinear,
		FilterLinearMipmapLinear
	};

	/**
	 * Enable or disable any color channel for writing
	 */
	struct ColorBufferMask
	{
		inline ColorBufferMask();

		vbool writeRed;
		vbool writeGreen;
		vbool writeBlue;
		vbool writeAlpha;
	};

	/**
	 * A reference to a texture
	 * add references to more textures using AddTexture for mult texturing
	 */
	struct TextureRef
	{
		inline TextureRef();

		vuint nWidth, nHeight;
		ByteBufferHandle hData;
		TextureFilter minificationFilter;
		TextureFilter magnificationFilter;
		TextureWrapMode wrapTexCoordU;
		TextureWrapMode wrapTexCoordV;

		TextureRef* pNext;
	};

	// data

	PolygonMode frontPolyMode;
	PolygonMode backPolyMode;

	DepthTest depthTestFunction;
	DepthMask depthWriteMask;

	TextureRef* pTextureList;

	v3d::graphics::VColor4f defaultColor;

	ColorBufferMask colorMask;

	vbool enableBlending;
	BlendFactor sourceBlendFactor;
	BlendFactor destBlendFactor;

	// functions

	// setting sensible default values
	inline VMaterialDescription();

	inline void AddTexture(TextureRef* in_pTexture);
};

VMaterialDescription::VMaterialDescription()  :
	frontPolyMode(Filled),
	backPolyMode(Filled),
	depthTestFunction(DepthOnLess),
	depthWriteMask(DepthWrite),
	pTextureList(0),
	defaultColor(1, 1, 1, 1),
	colorMask(),
	enableBlending(false),
	sourceBlendFactor(BlendSourceAlpha),
	destBlendFactor(BlendOneMinusSourceAlpha)
{
}

void VMaterialDescription::AddTexture(TextureRef* in_pTexture)
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

VMaterialDescription::ColorBufferMask::ColorBufferMask()
{
	writeRed = true;
	writeGreen = true;
	writeBlue = true;
	writeAlpha = true;
}

VMaterialDescription::TextureRef::TextureRef() :
	nWidth(0), nHeight(0), hData(0),
	minificationFilter(FilterLinear),
	magnificationFilter(FilterLinear),
	wrapTexCoordU(TextureRepeat),
	wrapTexCoordV(TextureRepeat)
{
}

//-----------------------------------------------------------------------------
} // namepace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMATERIALDESCRIPTION_H

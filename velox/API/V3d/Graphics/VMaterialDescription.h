#ifndef V3D_VMATERIALDESCRIPTION_H
#define V3D_VMATERIALDESCRIPTION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VMeshDescription.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // f***in' VC auto indent ;)

struct VMaterialDescription
{
	// types
	
	typedef VMeshDescription::ByteBufferHandle ByteBufferHandle;

    enum PolygonMode
	{
		Filled, Point, Line
	};

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

	// functions

	// setting sensible default values
	VMaterialDescription() :
		frontPolyMode(Filled),
		backPolyMode(Filled),
		pTextureList(0)
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

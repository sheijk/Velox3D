#ifndef V3D_VIMAGE_H
#define V3D_VIMAGE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VBuffer.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace image{
//-----------------------------------------------------------------------------

/**
 * Represents a decoded image file as pixel buffer
 waers nicht sinnvoller, die Werte zu kapseln damit sie nicht veraendert
 werden koennen? die buffer groesse kann ja auch nicht mehr geaendert werden
 -- sheijk
 */
struct VImage
{
	VImage(){};
	~VImage()
	{
		//TODO: ich fass es nicht.. -- sheijk
		// delete, und copy c'tor und = operator fehlen... das ding schreit 
		// ja foermlich nach speicherfehlern
		pData->~VBuffer();
	}
	vuint iHeight;
	vuint iWidth;
	vuint iBPP;

	typedef graphics::VBuffer<vuchar> ImageData;
	ImageData* pData;
};
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------

#endif // V3D_VIMAGE_H

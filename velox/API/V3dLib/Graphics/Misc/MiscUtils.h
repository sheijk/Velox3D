#ifndef V3D_SHEIJKUTILS20040407_H
#define V3D_SHEIJKUTILS20040407_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
#include <v3d/Image.h>
#include <v3d/Graphics.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * achtung: diese funktion erzeugt buffer, welche nicht automatisch wieder
 * freigegeben werden.
 *
 * matDesc = BuildTextureMaterial(device, fileName);
 * ...
 * device.DeleteBuffer(mat.Desc.pTextureList.hData);
 *
 * @author sheijk
 */
VMaterialDescription BuildTextureMaterial(
	IVDevice* in_pDevice,
	VStringParam in_pcTextureFile)
{
	using namespace v3d::image;
	using namespace v3d::graphics;

	IVImageFactory* pFactory = QueryObject<IVImageFactory>("image.service");

	IVImageFactory::ImagePtr myImage = pFactory->CreateImage(in_pcTextureFile);

	VMaterialDescription texMat;

	VMaterialDescription::TextureRef* pTexRef =
		new VMaterialDescription::TextureRef();

	IVDevice::BufferHandle hTextureBuffer = in_pDevice->CreateBuffer(
		IVDevice::Texture,
		myImage->pData,
		IVDevice::Buffer::DropData
		);

	pTexRef->nWidth = myImage->iWidth;
	pTexRef->nHeight = myImage->iHeight;
	pTexRef->hData = hTextureBuffer;

	texMat.AddTexture(pTexRef);

	return texMat;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_SHEIJKUTILS20040407_H

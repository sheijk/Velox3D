//TODO: insert header file name
#include <V3dLib/Graphics/Misc/MiscUtils.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VObjectRegistry.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------

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

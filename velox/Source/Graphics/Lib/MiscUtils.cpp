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

	//TODO: automatisch auf 2^n Groesse skalieren
	VImage image(myImage->GetWidth(), myImage->GetHeight(), 24);
	pFactory->ConvertImage(*myImage, image);

	VMaterialDescription texMat;

	VMaterialDescription::TextureRef* pTexRef =
		new VMaterialDescription::TextureRef();

	IVDevice::BufferHandle hTextureBuffer = in_pDevice->CreateBuffer(
		IVDevice::Texture,
		image.pData,
		//myImage->pData,
		IVDevice::Buffer::DropData
		);

	pTexRef->nWidth = myImage->iWidth;
	pTexRef->nHeight = myImage->iHeight;
	pTexRef->hData = hTextureBuffer;

	texMat.AddTexture(pTexRef);

	return texMat;
}

VMaterialDescription::ColorBufferMask NoColorWrites()
{
	VMaterialDescription::ColorBufferMask mask;

	mask.writeRed = false;
	mask.writeGreen = false;
	mask.writeBlue = false;
	mask.writeAlpha = false;

	return mask;
}

void ApplyMaterial(IVDevice& in_Device,
				   const IVMaterial* in_pMaterial)
{
	for(vuint prio = 0; prio < in_pMaterial->StateCount(); ++prio)
	{
		in_Device.ApplyState(in_pMaterial->GetState(prio));
	}
}

void RenderMesh(IVDevice& in_Device, IVDevice::MeshHandle in_hMesh)
{
	for(vuint matid = 0; matid < in_hMesh->GetMaterialCount(); ++matid)
	{
		IVMaterial* pMaterial = & in_hMesh->GetMaterial(matid);

		ApplyMaterial(in_Device, pMaterial);
		in_Device.RenderMesh(in_hMesh);
	}
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
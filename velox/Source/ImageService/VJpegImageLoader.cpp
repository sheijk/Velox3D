//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Image/IVImageFactory.h>
#include <v3d/Image/VImage.h>
#include <v3d/vfs/IVTempDataProvider.h>
#include <fstream>
#include <iostream>
#include "VJpegImageLoader.h"

#undef CreateFile
#pragma warning (disable : 4244)
//-----------------------------------------------------------------------------
namespace v3d {
namespace image{
//-----------------------------------------------------------------------------

VJpegImageLoader::VJpegImageLoader()
{
	m_iWidth = 0;
	m_iHeight = 0;
	m_iBPP = 0;
	m_pData = 0;
	pImageData = 0;

	Register();
}
//----------------------------------------------------------------------------
VImage* VJpegImageLoader::Create(vfs::IVStream* in_pStream, VStringParam in_sExt)
{
	VImage* pImage;

	vfs::IVTempDataProvider* pTempManager =
		QueryObject<vfs::IVTempDataProvider>("tempfile.service");

	VStringParam theFile = pTempManager->CreateFile(in_pStream);

	struct jpeg_decompress_struct cinfo;

	FILE *pFile;

	pFile = fopen(theFile, "rb");
	
	// Create an error handler
	jpeg_error_mgr jerr;

	// Have our compression info object point to the error handler address
	cinfo.err = jpeg_std_error(&jerr);

	// Initialize the decompression object
	jpeg_create_decompress(&cinfo);

	// Specify the data source (Our file pointer)	
	jpeg_stdio_src(&cinfo, pFile);

	// Allocate the structure that will hold our eventual jpeg data (must free it!)
	pImageData = (tImageJPG*)malloc(sizeof(tImageJPG));

	// Decode the jpeg file and fill in the image data structure to pass back
	DecodeJPG(&cinfo, pImageData);

	// This releases all the stored memory for reading and decoding the jpeg
	jpeg_destroy_decompress(&cinfo);

	// Return the jpeg data (remember, you must free this data after you are done)

	pImage = new VImage();
	
	pImage->pData = new VImage::ImageData(pImageData->data,
		pImageData->sizeX * pImageData->sizeY);

	pImage->iWidth = pImageData->sizeX;
	pImage->iHeight = pImageData->sizeY;
	
	return pImage;

}
//-----------------------------------------------------------------------------

void VJpegImageLoader::DecodeJPG(jpeg_decompress_struct* cinfo, tImageJPG *pImageData)
{
	// Read in the header of the jpeg file
	jpeg_read_header(cinfo, TRUE);

	// Start to decompress the jpeg file with our compression info
	jpeg_start_decompress(cinfo);

	// Get the image dimensions and row span to read in the pixel data
	pImageData->rowSpan = cinfo->image_width * cinfo->num_components;
	pImageData->sizeX   = cinfo->image_width;
	pImageData->sizeY   = cinfo->image_height;

	// Allocate memory for the pixel buffer
	pImageData->data = new unsigned char[pImageData->rowSpan * pImageData->sizeY];

	// Here we use the library's state variable cinfo.output_scanline as the
	// loop counter, so that we don't have to keep track ourselves.

	// Create an array of row pointers
	unsigned char** rowPtr = new unsigned char*[pImageData->sizeY];
	for (int i = 0; i < pImageData->sizeY; i++)
		rowPtr[i] = &(pImageData->data[i*pImageData->rowSpan]);

	// Now comes the juice of our work, here we extract all the pixel data
	int rowsRead = 0;
	while (cinfo->output_scanline < cinfo->output_height) 
	{
		// Read in the current row of pixels and increase the rowsRead count
		rowsRead += jpeg_read_scanlines(cinfo, &rowPtr[rowsRead], cinfo->output_height - rowsRead);
	}

	// Delete the temporary row pointers
	delete [] rowPtr;

	// Finish decompressing the data
	jpeg_finish_decompress(cinfo);
}

void VJpegImageLoader::Register()
{
	IVImageFactory* Factory = QueryObject<IVImageFactory>("image.service");
	Factory->Register(this, "jpg");
	Factory->Register(this, "jpeg");
}
//-----------------------------------------------------------------------------
#pragma warning (default : 4244)
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------

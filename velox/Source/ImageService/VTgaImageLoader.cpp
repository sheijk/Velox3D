//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Image/IVImageFactory.h>
#include <v3d/Image/VImage.h>
#include "VTgaImageLoader.h"
#include <memory.h>

#pragma warning (disable : 4244)
//-----------------------------------------------------------------------------
namespace v3d {
namespace image{
//-----------------------------------------------------------------------------

VTgaImageLoader::VTgaImageLoader()
{
	m_iWidth = 0;
	m_iHeight = 0;
	m_iBPP = 0;
	m_pData = NULL;

	Register();
}
//----------------------------------------------------------------------------
VImage* VTgaImageLoader::Create(vfs::IVStream* in_pStream)
{
	in_pStream->Read(&m_FileHeader.IDLength, sizeof(vchar));
	in_pStream->Read(&m_FileHeader.ColorMapType, sizeof(vchar));
	in_pStream->Read(&m_FileHeader.ImageType, sizeof(vchar));
	in_pStream->Read(&m_FileHeader.ColorMapIndex, sizeof(vshort));
	in_pStream->Read(&m_FileHeader.ColorMapLength, sizeof(vshort));
	in_pStream->Read(&m_FileHeader.ColorMapSize, sizeof(vchar));
	in_pStream->Read(&m_FileHeader.XOrigin, sizeof(vshort));
	in_pStream->Read(&m_FileHeader.YOrigin, sizeof(vshort));
	in_pStream->Read(&m_FileHeader.Width, sizeof(vshort));
	in_pStream->Read(&m_FileHeader.Height, sizeof(vshort));
	in_pStream->Read(&m_FileHeader.BPP, sizeof(vchar));
	in_pStream->Read(&m_FileHeader.Attributes, sizeof(vchar));

	if(m_FileHeader.IDLength != 0)
		in_pStream->SetPos(vfs::IVStream::Anchor::Begin,m_FileHeader.IDLength);
	
	vulong theByteCount = 0;
	vulong theCurrentPosition = in_pStream->GetPos();
	
	in_pStream->SetPos(vfs::IVStream::Anchor::End,0);
	theByteCount = in_pStream->GetPos();

	in_pStream->SetPos(vfs::IVStream::Anchor::Begin, theCurrentPosition);

	vuchar* theDataBuffer = new vuchar[theByteCount+1]; //TODO error checking
	in_pStream->Read(theDataBuffer, theByteCount);


	Error Result = ReadBuffer(theDataBuffer);
	delete theDataBuffer;

	if( Result != NO_ERROR)
		return NULL;



	VImage* pImage  = new VImage();
	pImage->pData = new VImage::ImageData(m_pData,
					 m_FileHeader.Width * m_FileHeader.Height);
	
	pImage->iWidth  = m_iWidth;
	pImage->iHeight = m_iHeight;
	pImage->iBPP    = m_iBPP;

	return pImage;

}
//-----------------------------------------------------------------------------

VTgaImageLoader::Error VTgaImageLoader::ReadBuffer(vuchar* in_pBuffer)
{
	if (m_FileHeader.ColorMapType != 0)
		return WRONG_COLOR_MAP;

	if (m_FileHeader.ImageType != 2 && m_FileHeader.ImageType != 3 &&
		m_FileHeader.ImageType != 10)
		return WRONG_IMAGE_TYPE;


	vuint iSize = m_FileHeader.Width * m_FileHeader.Height;

	if (m_FileHeader.BPP != 32 && m_FileHeader.BPP != 24 &&
		m_FileHeader.BPP != 8)
		return WRONG_BPP; 

	if(m_FileHeader.ImageType != 10)
		m_pData = GetData(in_pBuffer);
	else
		m_pData = GetCompressedData(in_pBuffer);

	if (m_pData == NULL)
		return WRONG_DATA;

	m_iBPP	  = m_FileHeader.BPP;
	m_iHeight = m_FileHeader.Height;
	m_iWidth  = m_FileHeader.Width;

	return NO_ERROR;
}

//-----------------------------------------------------------------------------

vuchar* VTgaImageLoader::GetData(vuchar* in_pBuffer)
{
	switch(m_FileHeader.BPP)
	{
	case 8:
		return Get8Bit(in_pBuffer);
		break;
	case 24:
		return Get24Bit(in_pBuffer);
		break;
	case 32:
		return Get32Bit(in_pBuffer);
		break;
	}

	return NULL;

}

//-----------------------------------------------------------------------------

vuchar* VTgaImageLoader::Get8Bit(vuchar* in_pBuffer)
{
	vuint iSize = m_FileHeader.Width * m_FileHeader.Height;
	vuchar* Data8Bit = new vuchar [iSize];
	if (Data8Bit == 0)
		return NULL;

	if (!memcpy(Data8Bit, in_pBuffer, iSize))
	{
		delete [] Data8Bit;
		return NULL;
	}

	return Data8Bit;
}
//-----------------------------------------------------------------------------

vuchar* VTgaImageLoader::Get24Bit(vuchar* in_pBuffer)
{
	vuchar iSwap;
	vuint iSize = m_FileHeader.Width * m_FileHeader.Height;
	vuint iCache = iSize * 3;

	vuchar* Data24Bit = new vuchar[iCache];
	if (Data24Bit == 0)
		return NULL;

	if (!memcpy(Data24Bit, in_pBuffer, iCache))
	{
		delete Data24Bit;
		return NULL;
	}

	for (vuint i = 0; i < iCache; i+= 3)
	{
		iSwap			= Data24Bit[i];
		Data24Bit[i]	= Data24Bit[i+2]; 
		Data24Bit[i+2]  = iSwap;
	}

	return Data24Bit;
}
//-----------------------------------------------------------------------------

vuchar* VTgaImageLoader::Get32Bit(vuchar* in_pBuffer)
{
	vuchar iSwap;
	vuint iSize  = m_FileHeader.Width * m_FileHeader.Height;
	vuint iCache = iSize * 4;

	vuchar* Data32Bit = new vuchar[iCache];
	if (Data32Bit == 0)
		return NULL;


	if (!memcpy(Data32Bit, in_pBuffer, iCache))
	{
		delete Data32Bit;
		return NULL;
	}

	for (vuint i = 0; i < iCache; i+= 4)
	{
		iSwap			= Data32Bit[i];
		Data32Bit[i]	= Data32Bit[i+2]; 
		Data32Bit[i+2]  = iSwap;
	}

	return Data32Bit;
}
//-----------------------------------------------------------------------------



vuchar* VTgaImageLoader::GetCompressedData(vuchar* in_pBuffer)
{
	vulong iBufferOffset = 0;
	vuchar iOffset;
	vuchar* pImageData;
	vuint iSize = m_FileHeader.Width * m_FileHeader.Height;

	if(m_FileHeader.BPP == 32)
	{
		iOffset = 4;
		pImageData = new vuchar[iSize * 4];
	}

	else
		if(m_FileHeader.BPP == 24)
		{
			iOffset = 3;
			pImageData = new  vuchar[iSize *3];
		}

	vuchar* pPixelBuffer;

	vuchar r,g,b,a;
	vuchar PacketHeader, PacketSize;


	for(vuint row = m_FileHeader.Height - 1; row >= 0; row--)
	{
		pPixelBuffer = pImageData + row * m_FileHeader.Width * iOffset;
		for(vint column = 0; column < m_FileHeader.Width; )
		{
			PacketHeader = *in_pBuffer + iBufferOffset;//TODO check
			iBufferOffset += sizeof(vuchar);

			PacketSize = 1 + (PacketHeader & 0x7f);

			if(PacketHeader & 0x80)
			{
				switch(m_FileHeader.BPP)
				{

				case 24:
					b = *in_pBuffer + iBufferOffset;
					iBufferOffset += sizeof(vuchar);

					g = *in_pBuffer + iBufferOffset;
					iBufferOffset += sizeof(vuchar);

					r = *in_pBuffer + iBufferOffset;
					iBufferOffset += sizeof(vuchar);

					a = 255;
					break;

				case 32:

					b = *in_pBuffer + iBufferOffset;
					iBufferOffset += sizeof(vuchar);

					g = *in_pBuffer + iBufferOffset;
					iBufferOffset += sizeof(vuchar);

					r = *in_pBuffer + iBufferOffset;
					iBufferOffset += sizeof(vuchar);

					a = *in_pBuffer + iBufferOffset;
					iBufferOffset += sizeof(vuchar);
					break;
				}

				for(int j=0;j<PacketSize;j++)
				{
					*pPixelBuffer++ =  r;
					*pPixelBuffer++ =  g;
					*pPixelBuffer++ =  b;
					if(iOffset == 4)
						*pPixelBuffer++ =  a;
					column++;

					if(column == m_FileHeader.Width)
					{
						column = 0;
						if(row > 0)
							row--;
						else
							goto LeavePoint;
						pPixelBuffer = pImageData + row * m_FileHeader.Width * iOffset;
					}
				}
			}
			else
			{
				for(int j = 0; j<PacketSize; j++)
				{
					switch(m_FileHeader.BPP)
					{
					case 24:
						b = *in_pBuffer + iBufferOffset;
						iBufferOffset += sizeof(vuchar);

						g = *in_pBuffer + iBufferOffset;
						iBufferOffset += sizeof(vuchar);

						r = *in_pBuffer + iBufferOffset;
						iBufferOffset += sizeof(vuchar);

						*pPixelBuffer++ = r;
						*pPixelBuffer++ = g;
						*pPixelBuffer++ = b;
						break;

					case 32:
						b = *in_pBuffer + iBufferOffset;
						iBufferOffset += sizeof(vuchar);

						g = *in_pBuffer + iBufferOffset;
						iBufferOffset += sizeof(vuchar);

						r = *in_pBuffer + iBufferOffset;
						iBufferOffset += sizeof(vuchar);

						a = *in_pBuffer + iBufferOffset;
						iBufferOffset += sizeof(vuchar);

						*pPixelBuffer++ = r;
						*pPixelBuffer++ = g;
						*pPixelBuffer++ = b;
						*pPixelBuffer++ = a;
						break;
					}
					column++;
					if(column == m_FileHeader.Width)
					{
						column = 0;
						if(row > 0)
							row--;
						else 
							goto LeavePoint;
						pPixelBuffer = pImageData + row * m_FileHeader.Width * iOffset;
					}
				}
			}
		}
LeavePoint:;

	}

	return pImageData;
}

//-----------------------------------------------------------------------------

void VTgaImageLoader::Register()
{
	IVImageFactory* Factory = QueryObject<IVImageFactory>("image.service");
	Factory->Register(this, "tga");
}
#pragma warning (disable : 4244)
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------

#include <Image/VImageTga.h>
#include <Core/VDebug.h>

VImageTga::VImageTga()
{
	m_pData	= NULL;
	m_iWidth = 0;
	m_iHeight= 0;
	m_iBpp = 0;
}

VImageTga::~VImageTga()
{
	if (m_pData != NULL)
	{
		delete [] m_pData;
	}
}

vint VImageTga::fgets(FILE* pFile)
{
	vuchar b1;
	vuchar b2;

	b1 = fgetc(pFile);
	b2 = fgetc(pFile);

	return ((vshort)(b1 + b2 * 256));
}

vuchar* VImageTga::GetCompressedData(const std::string& in_rStrFilename, vuint iSize)
{
	vint i = 0;
	vint j = 0;

	FILE* pFile = NULL;
	pFile = fopen(in_rStrFilename.c_str(), "rb");

	m_TgaHeader.m_ucIDLength = fgetc(pFile);
	m_TgaHeader.m_ucColorMapType = fgetc(pFile);
	m_TgaHeader.m_ucImageType = fgetc(pFile);
	m_TgaHeader.m_usColorMapIndex = fgets(pFile);
	m_TgaHeader.m_usColorMapLength = fgets(pFile);
	m_TgaHeader.m_ucColorMapSize = fgetc(pFile);
	m_TgaHeader.m_usXOrigin = fgets(pFile);
	m_TgaHeader.m_usYOrigin = fgets(pFile);
	m_TgaHeader.m_usWidth = fgets(pFile);
	m_TgaHeader.m_usHeight = fgets(pFile);
	m_TgaHeader.m_ucBPP = fgetc(pFile);
	m_TgaHeader.m_ucAttributes = fgetc(pFile);

		
	if (m_TgaHeader.m_ucIDLength != 0)
	{
		fseek(pFile, m_TgaHeader.m_ucIDLength, SEEK_CUR);
	}

	vuchar ucOffset;
	vuchar* pucImageData;

	if (m_TgaHeader.m_ucBPP == 32)
	{
		ucOffset = 4;
		pucImageData = new vuchar[iSize *4];
	}
	else if (m_TgaHeader.m_ucBPP == 24)
	{
		ucOffset = 3;
		pucImageData = new vuchar[iSize *3];
	}

	vuchar* pucPixelBuffer;
	vuchar r, g, b, a;
	vuchar Packetm_TgaHeader;
	vuchar PacketSize;

	vint iRow = 0;
	vint iColumn = 0;


	for (iRow=m_TgaHeader.m_usHeight-1; iRow>=0; iRow--)
	{
		pucPixelBuffer = pucImageData + iRow * m_TgaHeader.m_usWidth * ucOffset;
		for (iColumn = 0; iColumn < m_TgaHeader.m_usWidth;)
		{
			Packetm_TgaHeader = getc(pFile);
			PacketSize = 1 + (Packetm_TgaHeader & 0x7f);

			if (Packetm_TgaHeader & 0x80)
			{
				switch (m_TgaHeader.m_ucBPP)
				{

				case 24 :
					b = getc(pFile);
					g = getc(pFile);
					r = getc(pFile);
					a = 255;
					break;

				case 32 :
					b = getc(pFile);
					g = getc(pFile);
					r = getc(pFile);
					a = getc(pFile);
				break;
				}

				for (j=0; j<PacketSize; j++)
				{
					*pucPixelBuffer++ = r;
					*pucPixelBuffer++ = g;
					*pucPixelBuffer++ = b;
					if (ucOffset == 4)
					{
						*pucPixelBuffer++ = a;
					}
					iColumn++;

					if (iColumn == m_TgaHeader.m_usWidth)
					{
						iColumn = 0;
						if (iRow > 0)
						{
							iRow--;
						}
						else
						{
#pragma todo ( NEVER EVER USE GOTO )
							goto LeavePovint;
						}
						pucPixelBuffer = pucImageData + iRow * m_TgaHeader.m_usWidth * ucOffset;
					}
				}
			}
			else
			{
				for (j=0; j<PacketSize; j++)
				{
					switch (m_TgaHeader.m_ucBPP)
					{

					case 24 :
						b = getc(pFile);
						g = getc(pFile);
						r = getc(pFile);
						*pucPixelBuffer++ = r;
						*pucPixelBuffer++ = g;
						*pucPixelBuffer++ = b;
						break;

					case 32 :
						b = getc(pFile);
						g = getc(pFile);
						r = getc(pFile);
						a = getc(pFile);
						*pucPixelBuffer++ = r;
						*pucPixelBuffer++ = g;
						*pucPixelBuffer++ = b;
						*pucPixelBuffer++ = a;
						break;
					}
					
					iColumn++;
					
					if (iColumn == m_TgaHeader.m_usWidth)
					{
						iColumn = 0;
						if(iRow > 0)
						{
							iRow--;
						}
						else 
						{
							goto LeavePovint;
						}
						pucPixelBuffer = pucImageData + iRow * m_TgaHeader.m_usWidth * ucOffset;
					}
				}
			}
		}
#pragma todo ( NEVER EVER USE GOTO )
LeavePovint:;
	}
	
	return pucImageData;
}

vuchar* VImageTga::GetData(vuchar* in_pucBuffer, const vuint in_uiSize)
{
	switch(m_iBpp)
	{
	case 8 :
	
		return Get8Bit(in_pucBuffer, in_uiSize);
		break;

	case 24 :
		
		return Get24Bit(in_pucBuffer, in_uiSize);
		break; 

 	case 32 :

		return Get32Bit(in_pucBuffer, in_uiSize);
		break;
	}

	return NULL;
}

vuchar* VImageTga::Get8Bit(vuchar* in_pucBuffer, const vuint in_uiSize)
{
	vuchar* pucData = new vuchar[in_uiSize];
	if (pucData == NULL)
	{
		return NULL;
	}

	if (!memcpy(pucData, in_pucBuffer, in_uiSize))
	{
      delete [] pucData;
      return NULL;
	}
	
	return pucData;
}


vuchar* VImageTga::Get24Bit(vuchar* in_pucBuffer, const vuint in_uiSize)
{
	vuchar ucSwap = 0;
	vuint ucCache = in_uiSize * 3;

	vuchar* pucData = new vuchar[ucCache];
	if (pucData == NULL)
	{
		return NULL;
	}

	if (!memcpy(pucData, in_pucBuffer, ucCache))
	{
		delete [] pucData;
		return NULL;
	}
     
	for (vuint i=0; i<ucCache; i+=3)
	{
		ucSwap = pucData[i];
		pucData[i] = pucData[i + 2]; 
		pucData[i + 2] = ucSwap;
	}

	return pucData;
}

vuchar* VImageTga::Get32Bit(vuchar* in_pucBuffer, const vuint in_uiSize)
{
	vuint i = 0;
	vuchar ucSwap;
	vuint ucCache = in_uiSize * 4;

	vuchar* pucData = new vuchar[ucCache];
	if (pucData == 0)
	{
		return NULL;
	}
	
	if (!memcpy(pucData, in_pucBuffer, ucCache))
	{
		delete [] pucData;
		return NULL;
	}

	//swap the values for RGB order
	for (i=0; i<ucCache; i+=4)
	{
		ucSwap = pucData[i];
		pucData[i] = pucData[i + 2]; 
		pucData[i + 2] = ucSwap;
	}

	return pucData; 
}

VRESULT VImageTga::ReadBuffer(vuchar* in_pucBuffer, const std::string& in_rStrFilename)
{
	vuchar* pucBuffer = in_pucBuffer;
	
	if (m_TgaHeader.m_ucColorMapType != 0)
	{
		return VERROR_IMAGE_BADCOLORMAP;
	}
	if (m_TgaHeader.m_ucImageType != 2 && m_TgaHeader.m_ucImageType != 3 && m_TgaHeader.m_ucImageType != 10)
	{
		return VERROR_IMAGE_BADTYPE;
	}
	   
	m_iWidth = m_TgaHeader.m_usWidth;
	m_iHeight = m_TgaHeader.m_usHeight;
	m_iBpp = m_TgaHeader.m_ucBPP;
   
	vuint iSize = m_iWidth * m_iHeight;
   
	if (m_iBpp != 32 && m_iBpp != 24 && m_iBpp != 8)
	{
		return VERROR_IMAGE_BADBPP;
	}

	if (m_TgaHeader.m_ucImageType != 10)
	{
		m_pData = GetData(pucBuffer, iSize);
	}
	else
	{
		m_pData = GetCompressedData(in_rStrFilename, iSize);
	}

	if (m_pData == NULL)
	{
		return VERROR_IMAGE_DECODE;
	}

	return VOK;
}

VRESULT VImageTga::Load(const std::string& in_rStrFilename)
{
	VRESULT eResult;
	FILE* pFile = NULL;
	vuchar* pucBuffer = NULL;
	vuint uiSize;

	pFile = fopen(in_rStrFilename.c_str(), "rb");

	if (pFile == NULL) 
	{
		return VERROR_FILE_NOTFOUND;
	}

	m_TgaHeader.m_ucIDLength = fgetc(pFile);
	m_TgaHeader.m_ucColorMapType = fgetc(pFile);
	m_TgaHeader.m_ucImageType = fgetc(pFile);
	m_TgaHeader.m_usColorMapIndex = fgets(pFile);
	m_TgaHeader.m_usColorMapLength = fgets(pFile);
	m_TgaHeader.m_ucColorMapSize = fgetc(pFile);
	m_TgaHeader.m_usXOrigin = fgets(pFile);
	m_TgaHeader.m_usYOrigin = fgets(pFile);
	m_TgaHeader.m_usWidth = fgets(pFile);
	m_TgaHeader.m_usHeight = fgets(pFile);
	m_TgaHeader.m_ucBPP = fgetc(pFile);
	m_TgaHeader.m_ucAttributes = fgetc(pFile);

	if (m_TgaHeader.m_ucIDLength != 0)
	{
		fseek(pFile, m_TgaHeader.m_ucIDLength, SEEK_CUR);
	}

	vlong lCur;
	lCur = ftell(pFile);
	fseek(pFile, 0L, SEEK_END);
	uiSize = ftell(pFile);
	fseek(pFile, lCur, SEEK_SET);
	
	if (!(pucBuffer = new vuchar[uiSize + 1]))
	{
		fclose(pFile);
		return VERROR_MEMORY_NOMEM;
	}

	fread(pucBuffer, 1, uiSize, pFile);

	eResult = ReadBuffer(pucBuffer, in_rStrFilename);
	if (eResult != VOK)
	{
		return eResult;
	}

	delete [] pucBuffer;
	pucBuffer = NULL;

	fclose(pFile);
	
	return VOK;
}

VRESULT VImageTga::Destroy()
{
	if (m_pData != NULL)
	{
		delete [] m_pData;
		m_pData = NULL;
	}

	return VOK;
}
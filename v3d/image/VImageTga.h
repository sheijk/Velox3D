#ifndef V3D_VIMAGETGA_H
#define V3D_VIMAGETGA_H


#include <stdio.h>
#include <memory.h>

#include <Image/IVImage.h>


class VImageTga : public IVImage
{
public:

	VImageTga();
	~VImageTga();
	
	VRESULT Load(const std::string& in_rStrFilename);
	VRESULT Destroy();

private:

	//internal tga header
	typedef struct TgaHeader
	{
		vuchar m_ucIDLength;
		vuchar m_ucColorMapType;
		vuchar m_ucImageType;
		vuchar m_ucColorMapSize;
		vuchar m_ucBPP;
		vuchar m_ucAttributes;
		vushort m_usColorMapIndex;
		vushort m_usColorMapLength;
		vushort m_usXOrigin;
		vushort m_usYOrigin;
		vushort m_usWidth;
		vushort m_usHeight;
	
	};

	TgaHeader m_TgaHeader;

	VRESULT ReadBuffer(vuchar *pBuffer, const std::string& in_rStrFilename);

	vuchar* GetData(vuchar *pBuffer, vuint iSize);
	vuchar* GetCompressedData(const std::string& in_rStrFilename, vuint iSize);
	vuchar* Get8Bit(vuchar *pBuffer, const vuint iSize);
	vuchar* Get24Bit(vuchar *pBuffer, const vuint iSize);
	vuchar* Get32Bit(vuchar *pBuffer, const vuint iSize);
	
	vint fgets(FILE *fp);
		

};

#endif
#ifndef V3D_IVIMAGE_H
#define V3D_IVIMAGE_H

#include <Core/VTypes.h>

#include <string>

class IVImage
{
public :

	vint GetWidth()	const;
	vint GetHeight() const;
	vint GetBPP() const;
	vuchar* GetData() const;

	virtual VRESULT Load(const std::string& in_rStrFilename) = 0;
	virtual VRESULT Destroy() = 0;
	
protected :

	vint m_iWidth;
	vint m_iHeight;
	vint m_iBpp;
	vuchar* m_pData;
};

#endif
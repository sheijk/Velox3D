//
// *** VMemoryFile ***
//
// Synopsis:
//    - Loads a file into memory
//
// Description:
//    - 
//
// See also:
//    - 
//

#ifndef V3D_VMEMORYFILE_H
#define V3D_VMEMORYFILE_H

#include <windows.h>
#include <string>

#include <Core/VTypes.h>

using std::string;

class VMemoryFile
{
private:

	vulong m_ulSize;
    vuchar* m_pucData;
    string m_sFilename;

protected:

	void Release();


public:
	VMemoryFile(void);
	~VMemoryFile(void);

	vulong  GetSize();
	vuchar* GetData();
	vuchar* GetData(vint iOffset) const;
	const vchar*   GetFilename() const;
	vuchar* Alloc(vint iSize);
	virtual vbool Load(const vchar* cFilename);
	virtual vbool Load(const vchar* cFilename, vuchar* pucPointer, vint iSize);


};

#endif 

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

#include <Utils/VMemoryFile.h>

VMemoryFile::VMemoryFile()
{
	m_ulSize = 0;
	m_pucData = NULL;
	m_sFilename = "";
}

VMemoryFile::~VMemoryFile()
{
	Release();
}


vuchar* VMemoryFile::GetData(vint iOffset) const
{ 
	return m_pucData + iOffset;
}

vuchar* VMemoryFile::GetData()
{
	return m_pucData;
}

const vchar* VMemoryFile::GetFilename() const
{
	return m_sFilename.c_str();
}

unsigned long VMemoryFile::GetSize()
{
	return m_ulSize;
}

void VMemoryFile::Release()
{
    if(m_pucData)
	{
        free (m_pucData);
        m_pucData = NULL;
    }
     m_ulSize = 0;
     m_sFilename = "";
}

vuchar* VMemoryFile::Alloc(vint iSize)
{
	return (vuchar*) malloc(iSize);
}

vbool VMemoryFile::Load(const vchar* cFilename, vuchar* pucPointer, vint iSize) 
{
    if(cFilename && pucPointer && iSize > 0)
	{
        Release();
        m_sFilename = cFilename;
        m_pucData = pucPointer;
        m_ulSize = iSize;
        return true;
     }
    return false;
}

///////////////////////////////////////////////////////////////////////////////

bool VMemoryFile::Load(const vchar* cFilename) 
{
	HANDLE hFileHandle = CreateFile(cFilename, GENERIC_READ, 0, 0, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 0);
	if(hFileHandle == INVALID_HANDLE_VALUE)
		return false;
	
	Release();
	m_ulSize = GetFileSize(hFileHandle, 0);

	if(m_ulSize > 0)
	{
		m_pucData = Alloc(m_ulSize);
		if(!m_pucData)
		{
			m_ulSize = 0;
			return false;
		}

		DWORD r = 0;
		BOOL b = ReadFile(hFileHandle, m_pucData, m_ulSize, &r, 0);
		if(b == FALSE || r != m_ulSize)
		{
			if(m_pucData)
			{
				free(m_pucData);
				m_pucData = NULL;
			}
            m_ulSize = 0;
			return false;
		}

		m_sFilename = cFilename;
		return true;
	}

	return false;
}









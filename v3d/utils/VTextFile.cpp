#include <Utils/VTextFile.h>

VTextFile::VTextFile()
{
	m_pfFilePointer = NULL;
}

vbool VTextFile::OpenFile(const vchar *pcFilename)
{
	if(m_pfFilePointer != NULL)
		fclose(m_pfFilePointer);
	
	m_pfFilePointer = NULL;

	if(pcFilename == NULL)
		return false;


	m_pfFilePointer = fopen(pcFilename, "a");
	
	if(m_pfFilePointer == NULL)
		return false;
	
	return true;
}

VRESULT VTextFile::Write(const vchar *pcText, ...)
{
	VFormattedOutput::Write(pcText);		//FIXME: NOT TESTED!!!

	if(!OpenFile(m_sFilename.c_str()))
		return VERROR_FILE_NOTFOUND;

	fprintf(m_pfFilePointer, "%s", VFormattedOutput::GetTextBuffer());

	fclose(m_pfFilePointer);

	return VOK;
}

VRESULT VTextFile::Initialize(vchar *pcFilename)
{
		
		m_pfFilePointer = fopen(pcFilename, "w");
		
		
		if(m_pfFilePointer == NULL)
            return VERROR_FILE_NOTFOUND;
		
		m_sFilename = pcFilename;
		
		fclose(m_pfFilePointer);

		return VOK;
}

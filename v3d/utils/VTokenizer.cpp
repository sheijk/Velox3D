#include <Utils/VTokenizer.h>


VTokenizer::VTokenizer(const vchar* cDelims, vbool bLowerCase)
 {  
	VMemoryFile();
    m_sDelimiters = cDelims;
	m_bLowerCase = bLowerCase;
   
 }

vint VTokenizer::GetNumTokens(vint iLine) const
{
    if((unsigned) iLine < m_vTokenLines.size())
        return (int)m_vTokenLines[iLine].m_vTokens.size();
    
	return 0;
}

const string& VTokenizer::GetToken(vint iLine, vint iIndex) const
{
    return m_vTokenLines[iLine].m_vTokens[iIndex];
}

vbool VTokenizer::Load(const vchar* cFilename)
{
	if(VMemoryFile::Load(cFilename))
	{
		Tokenize((vchar*) GetData());
        return true;
    }

	return false;
}

vbool VTokenizer::Load(const vchar* cFilename, vuchar* pucPointer, vint iSize)
{
	if(VMemoryFile::Load(cFilename, pucPointer, iSize))
	{
		Tokenize((vchar*) GetData(0));
		return true;
	}

	return false;
}

void VTokenizer::Tokenize(vchar* pcString)
{
	m_vTokenLines.clear();
	int count = 0, c = 0;
	while((unsigned)c < GetSize()) {
		vchar tmp[4096];
		vchar* p = tmp;
		while((unsigned)c < GetSize()) {
			vchar ch = *(vchar*) GetData(c++);
			if(ch == 0x0d)
			{
				if((ch = *(vchar*) GetData(c)) == 0x0a)
				{
					c++;
				}
				break;
			}
			else
				if(ch == 0x0a)
					break;
				
				*p++ = ch;
		}
		*p = 0;

		// setup line, remember line number
		VTokenLine line;
		line.m_iNumber = count++;

		// dont process empty lines
		if(p-tmp==0) continue;

		// process tokens
		vchar* token = strtok(tmp, m_sDelimiters.c_str());
		while(token) {
			// skip stuff after the comment
			if(token[0]=='/'&&token[1]=='/') {
				break;
			}

			if(m_bLowerCase)
			{
				strlwr(token);
			}

			line.m_vTokens.push_back(token);
			token = strtok(0, m_sDelimiters.c_str());
		}

		// don't add empty lines
		if(line.m_vTokens.size())
            m_vTokenLines.push_back(line);
		
	}
}


const vchar* VTokenizer::GetNextToken(vint & riLine, vint & riToken) const
{
	if(riToken >= GetNumTokens(riLine))
	{
		riLine++;
		riToken = 0;
	}

	if(riLine < GetNumLines())
	{
		return GetToken(riLine, riToken++).c_str();
	}
	
	return 0;
}







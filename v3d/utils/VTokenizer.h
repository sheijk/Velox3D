//
// Synopsis:
//    - A tokenizer class
//
// Description:
//    - 
//
// See also:
//    - 
//


#ifndef V3D_VTOKENIZER_H
#define V3D_VTOKENIZER_H

#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

#include <Core/VTypes.h>
#include <Utils/VMemoryFile.h>
#include <Utils/VTokenLine.h>


using std::string;
using std::vector;



class VTokenizer : public VMemoryFile
{
public:

	VTokenizer(const vchar* Delims = " \t", vbool bLowerCase = false);
        
	vint& GetNumLines() const;
	vint GetNumTokens(vint Line) const;
	const string& GetToken(vint iLine, vint iIndex) const;

	vbool Load(const vchar* cFilename);
	vbool Load(const vchar* cFilename, vuchar* pucPointer, vint iSize);

protected:

	void Tokenize(vchar* pcString);
	const vchar* VTokenizer::GetNextToken(vint & riLine,vint & riToken) const;



	
private:

	vector<VTokenLine> m_vTokenLines;
	string m_sDelimiters;

	vbool m_bLowerCase;


};

#endif
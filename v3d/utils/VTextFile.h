//
// *** VTextFile ***
//
// Synopsis:
//    - Writes text to a file
//
// Description:
//    - 
//
// See also:
//    - 
//

#ifndef V3D_VTEXTFILE_H
#define V3D_VTEXTFILE_H

#include <stdio.h>
#include <string>


#include <Core/VTypes.h>
#include <Utils/VFormattedOutput.h>

using std::string;

class VTextFile : public VFormattedOutput
{

private:

	vbool OpenFile(const vchar *pcFilename);

	string m_sFilename;
	FILE *m_pfFilePointer;

public:

	VTextFile();
		
	const vchar* GetFilename();

	VRESULT Initialize(vchar *pcFilename);
	VRESULT Write(const vchar *pcText, ...); //Writes text to a file

};


#endif
//
// *** VFormattedOutput ***
//
// Synopsis:
//    - Write formatted output using a pointer to a list of arguments
//
// Description:
//    - 
//
// See also:
//    - 
//

#ifndef V3D_VFORMATTEDOUTPUT_H
#define V3D_VFORMATTEDOUTPUT_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <Core/VTypes.h>



class VFormattedOutput
{
private:

	vchar  m_cBuffer[256];

public:

	VFormattedOutput(void);
	~VFormattedOutput(void);

	

	VRESULT Write(const vchar *pcText, ...); //Writes text into a buffer
	vchar* GetTextBuffer();
	vint   GetStringLenght();

};

#endif

//
// *** VTokenLine ***
//
// Synopsis:
//    - Holds a line of tokens in a list
//
// Description:
//    - 
//
// See also:
//    - 
//

#include <Utils/VTokenLine.h>


VTokenLine::VTokenLine()
{
	Clear();
}

void VTokenLine::Clear()
{
	m_iNumber = 0;
	m_vTokens.clear();
}

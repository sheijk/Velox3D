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

#ifndef V3D_VTOKENLINE_H
#define V3D_VTOKENLINE_H

#include <Core/VTypes.h>

#include <string>
#include <vector>

using std::string;
using std::vector;


class VTokenLine {
public:
	
	VTokenLine();
	
	void Clear();
	
	vint m_iNumber;
	vector<string> m_vTokens;
};


#endif 

/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSIMPLETOKENIZER_2005_03_07_H
#define V3D_VSIMPLETOKENIZER_2005_03_07_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <list>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
* A simple tokenizer class. Takes a string and a delimeter character
* and parses the string into a list of tokens
*
* @author sheijk
*/
class VSimpleTokenizer
{
public:
	typedef std::list<std::string>::iterator Iterator;

	VSimpleTokenizer(const std::string& in_strString, char in_cDelimeter);

	Iterator TokenBegin();
	Iterator TokenEnd();

private:
	std::list<std::string> m_Tokens;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VSIMPLETOKENIZER_2005_03_07_H


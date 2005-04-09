#include <V3d/Utils/VSimpleTokenizer.h>
//-----------------------------------------------------------------------------

#include <algorithm>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VSimpleTokenizer::VSimpleTokenizer(
								   const std::string& in_strString, char in_cDelimeter)
{
	std::string::const_iterator tokenStart = in_strString.begin();
	std::string::const_iterator tokenEnd;

	while( true )
	{
		tokenEnd = std::find(tokenStart, in_strString.end(), in_cDelimeter);
		if( tokenStart == in_strString.end() )
			break;

		// get token
		std::string token(tokenStart, tokenEnd);
		m_Tokens.push_back(token);

		tokenStart = tokenEnd;
		if( tokenStart != in_strString.end() )
			++tokenStart;
	}
}

VSimpleTokenizer::Iterator VSimpleTokenizer::TokenBegin()
{
	return m_Tokens.begin();
}

VSimpleTokenizer::Iterator VSimpleTokenizer::TokenEnd()
{
	return m_Tokens.end();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------

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

#include <Utils/VFormattedOutput.h>


VRESULT VFormattedOutput::Write(const vchar *pcText, ...)
{
	va_list	arguments;

	if (pcText == NULL)
		return VERROR_INPUT_NOPARAM;

	va_start(arguments, pcText);
	vsprintf(m_cBuffer, pcText, arguments);
	va_end(arguments);

	return VOK;
}

vchar* VFormattedOutput::GetTextBuffer()
{
	return m_cBuffer;
}

vint VFormattedOutput::GetStringLenght()
{
	vint i;
    i = (vint)strlen(m_cBuffer);
	return i;
}
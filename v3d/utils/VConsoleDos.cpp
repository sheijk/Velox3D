#include <Utils/VConsoleDos.h>


VRESULT VConsoleDos::Initialize()
{
	AllocConsole();
	
	return VOK;
}

VRESULT VConsoleDos::Shutdown()
{
	FreeConsole();

	return VOK;
}

void VConsoleDos::Write(const vchar *pcText, ...)
{
	VFormattedOutput::Write(pcText); //FIXME: NOT TESTESD
	
	m_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(m_hOut, VFormattedOutput::GetTextBuffer(), VFormattedOutput::GetStringLenght(),
		&m_dwCount, NULL);
}

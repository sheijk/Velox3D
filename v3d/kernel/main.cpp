#include "VKernel.h"

#include <Utils/SmartPtr/VGuards.h>

#include <iostream>

using std::cout;
using std::endl;

//-----------------------------------------------------------------------------
// global kernel instance
VPointer<VKernel>::AutoPtr g_pKernel;

//-----------------------------------------------------------------------------

/** the main function */
int main(int argv, char* argc[])
{
	// create the kernel
	g_pKernel.Reset(new VKernel());

	try
	{
		// load and init
		g_pKernel->ProcessIniFile("init.xml");
	}
	catch(VException exc)
	{
		cout << "Exeption while processing init.xml: "
			<< "\"" << exc.GetErrorString() << "\""
			<< " in file \"" << exc.GetErrorFile() << "\""
			<< ", line \"" << exc.GetErrorLine() << "\""
			<< " extended error string: \"" 
			<< exc.GetExtendedErrorString() << "\""
			<< endl << endl;
	}

	// delete kernel
	g_pKernel.Release();

	// exit program
	return 0;
}

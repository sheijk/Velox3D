#include "VKernel.h"
#include <v3d/Core/SmartPtr/VGuards.h>

#include <iostream>

//-----------------------------------------------------------------------------
using std::cout;
using std::endl;
using namespace v3d;
using namespace v3d::kernel;
//-----------------------------------------------------------------------------

// global kernel instance
VPointer<VKernel>::AutoPtr g_pKernel;

//-----------------------------------------------------------------------------

/** the main function */
int main(int argv, char* argc[])
{
	char* pcXmlFileName = 0;

	// create the kernel
	g_pKernel.Assign(new VKernel());

	// get name of xml config file

	if( argv > 1 )
	{
		pcXmlFileName = argc[1];
	}
	else
	{
		pcXmlFileName = "init.xml";
	}

	cout << "Using xml config file <" << pcXmlFileName << ">\n" << endl;

	try
	{
		// load and init
		g_pKernel->ProcessIniFile(pcXmlFileName);
	}
	catch(VException& exc)
	{
		cout << "\n\nException while processing \"" << pcXmlFileName << "\":\n"
			<< "\"" << exc.GetErrorString() << "\"\n"
			<< "file \"" << exc.GetErrorFile() << "\"\n"
			<< "line \"" << exc.GetErrorLine() << "\"\n"
			<< "extended error string: "
			<< "\"" << exc.GetExtendedErrorString() << "\""
			<< endl << endl;
		throw exc;
	}

	// delete kernel
	g_pKernel.Release();

	throw std::string("let's shutdown :)");

	// exit program
	return 0;
}

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

//		V3D_THROW(VException, "lala");
	}
	catch(VException exc)
	{
		cout << "Exception while processing \"" << pcXmlFileName << "\":"
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

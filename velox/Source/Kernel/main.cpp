#include "VKernel.h"
#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/Core/VIOStream.h>
//#include <iostream>

//-----------------------------------------------------------------------------
//using std::cout;
//using std::endl;
using namespace v3d;
using namespace v3d::kernel;
//-----------------------------------------------------------------------------

// global kernel instance
VPointer<VKernel>::AutoPtr g_pKernel;

//-----------------------------------------------------------------------------

/** the main function */
int main(int argv, char* argc[])
{

	vchar* pcXmlFileName = 0;

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

	vout << "Using xml config file <" << pcXmlFileName << ">\n";// << endl;
	
	try
	{
		// load and init
		g_pKernel->ProcessIniFile(pcXmlFileName);
	}

	catch(VException& exc)
	{
	
		vout << "\n\nException while processing \"" << pcXmlFileName << "\":\n"
			<< "\"" << exc.GetErrorString() << "\"\n"
			<< "file \"" << exc.GetErrorFile() << "\"\n"
			<< "line \"" << exc.GetErrorLine() << "\"\n"
			<< "extended error string: "
			<< "\"" << exc.GetExtendedErrorString() << "\"";
			//<< endl << endl;
		
	}

	// delete kernel
	g_pKernel.Release();

	// exit program
	return 0;
}

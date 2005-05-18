#include "VKernel.h"
#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/Core/VIOStream.h>
#include <sstream>

//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::kernel;
//-----------------------------------------------------------------------------

namespace
{
	// global kernel instance
	VSharedPtr<VKernel> g_pKernel;
}

namespace v3d {
	const char* GetModuleName()
	{
		return "app";
	}
} // namespace v3d
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
	
	try
	{
		// load and init
		std::string fileName;
		fileName = pcXmlFileName;
		g_pKernel->ProcessIniFile(fileName);
	}
	catch(VException& exc)
	{
		std::ostringstream ostr;
	
		ostr 
			<< "\n\n----------------------------------------\n"
			<< "Exception while processing \"" << pcXmlFileName << "\":\n"
			<< "Message: \"" << exc.GetErrorString() << "\"\n"
			<< "File:    \"" << exc.GetErrorFile() << "\"\n"
			<< "Line:    \"" << exc.GetErrorLine() << "\"\n"
			<< "XErr:    \"" << exc.GetExtendedErrorString() << "\"\n"
			<< "\n";
			//<< endl << endl;
        
		const char* pcMessage = ostr.str().c_str();

		std::string msg = ostr.str();

		vout << pcMessage;

		// force a breakpoint
		__asm
		{ 
			// if you stop here, an uncaught exception occured. check the value
			// of pcMessage/msg to get further information
			// when done, simply continue to end application gracefully
			int 3; 
		}
	}

	// delete kernel
	g_pKernel.Release();

	// exit program
	return 0;
}

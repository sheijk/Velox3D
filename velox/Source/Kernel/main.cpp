/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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
	const vchar* pcXmlFileName = "init.xml";

	// create the kernel
	g_pKernel.Assign(new VKernel());

	// get name of xml config file

	if( argv > 2 )
	{
		const std::string arg1 = argc[1];
		const std::string arg2 = argc[2];

		if( arg1 == "-ini" )
			pcXmlFileName = arg2.c_str();

		//pcXmlFileName = argc[1];
	}
	
	try
	{
		// load and init
		std::string fileName;
		fileName = pcXmlFileName;
		g_pKernel->SetArguments(argv, argc);
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

		vout << msg;

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



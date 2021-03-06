/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/Core/VIOStream.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/SmartPtr/VSharedPtr.h>
#include "../VKernel.h"
#include "VCommandLineParser.h"
#include "VWinDialogBox.h"
//-----------------------------------------------------------------------------
#include <windows.h>
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::kernel;
//-----------------------------------------------------------------------------
 
namespace
{
	// global kernel instance
	VSharedPtr<VKernel> g_pKernel;
}

//-----------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine,
				   int iCmdShow)
{
	//TODO: variablen namen mit grossbuchstaben am anfang verwirren, 
	// lieber theCommandLine oder so (sheijk)

	win32::VCommandLineParser CmdLn;
	const vchar* pcXmlFileName = 0;

	// create the kernel
	g_pKernel.Assign(new VKernel());
	
	// get name of xml config file
	CmdLn.AnalyseCommandLine();
	pcXmlFileName = CmdLn.GetEntity("init");
	if(pcXmlFileName == NULL)
		pcXmlFileName = "init.xml";



	vout << "-------------------------------------------------------" << vendl;
	vout << "Starting v3d engine..." << vendl;
	vout << "-------------------------------------------------------" << vendl;
	vout << "Using xml config file <" << pcXmlFileName << ">" << vendl;
	vout << "-------------------------------------------------------" << vendl;

	try
	{
		// load and init
		g_pKernel->ProcessIniFile(pcXmlFileName);
	}
	catch(VException& exc)
	{
		std::ostringstream str;

		str << exc.GetErrorString() << "\n\n";
		str << "File: " << exc.GetErrorFile() << "\n";
		str << "Line: "<< exc.GetErrorLine() << "\n\n";
		str << exc.GetExtendedErrorString() << "\n";

		
		win32::VWinDialogBox dialog;
		dialog.Show(str.str().c_str(), "Exception", win32::VWinDialogBox::IS_ICONINFORMATION,
			win32::VWinDialogBox::BS_OK);
		
	}

	// delete kernel
	g_pKernel.Release();

	// exit program
	return 0;

}


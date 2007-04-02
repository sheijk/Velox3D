/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCONSOLEREDIRECTOR_H
#define V3D_VCONSOLEREDIRECTOR_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Utils/IVStringStream.h>
#include <V3d/Core/VIOStream.h>
#include <V3d/Console/IVConsoleService.h>
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#define WIN32_LEAN_AND_MEAN

#ifdef V3D_WIN32
#include <windows.h>
#endif
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {

	using std::cout;
	using std::ofstream;
	using std::ios_base;
//-----------------------------------------------------------------------------

namespace {
	void SendBootupMessage(VStringParam in_strMessage)
	{
		//OutputDebugString(in_strMessage);
		//cout << in_strMessage;

		ofstream file("init.log", ios_base::app);
		file << in_strMessage;
		file.close();
	}

	/** 
	 * The console redirector redirects vout streaming into the console
	 * window that is registered as error listener
	 */
	class VConsoleRedirector : public utils::IVStringStream
	{
	public:
		VConsoleRedirector();
		~VConsoleRedirector();
		virtual void Write(VStringParam in_strString);
		virtual void Flush() {};

	private:
		void SendToVeloxConsole(VStringParam in_pcMessage);

		console::IVConsoleService* m_Console;
		typedef std::list<std::string> StringList;
		StringList m_StringList;

	};


	VConsoleRedirector::VConsoleRedirector()
	{
		m_Console = NULL;
	}
	VConsoleRedirector::~VConsoleRedirector()
	{
	}

	void VConsoleRedirector::SendToVeloxConsole(VStringParam in_pcMessage)
	{
		//cout << in_pcMessage;
		m_Console->Write(in_pcMessage);
	}

	void VConsoleRedirector::Write(VStringParam in_strString)
	{
		cout << in_strString;
		cout.flush();

#ifdef V3D_WIN32
		OutputDebugString(in_strString);
#endif

		if(m_Console)
		{
			m_Console->Write(in_strString);
			}
		else
		{
			if( VObjectRegistry::GetInstance()->ContainsObject("console.service") )
			{
				m_Console = 
					QueryObject<console::IVConsoleService>("console.service");
				StringList::iterator iter = m_StringList.begin();
				for(; iter != m_StringList.end(); iter++)
				{
					SendToVeloxConsole(iter->c_str());
					// m_Console->Write(iter->c_str());
				}
				SendToVeloxConsole(in_strString);
				//m_Console->Write(in_strString);
			}
			else
			{
				m_StringList.push_back(in_strString);
				
				SendBootupMessage(in_strString);
			}


		}
	}

	VConsoleRedirector Redirector;
}

utils::IVStringStream& vout(Redirector);
const char* vendl = "\n";

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------

#endif // V3D_VCONSOLEREDIRECTOR_H


#include <v3d/Core/VIOStream.h>
#include "VKernelIniReader.h"
#include "VKernelException.h"
//#include <iostream>
//-----------------------------------------------------------------------------
using namespace v3d::xml;
//using namespace std;
//-----------------------------------------------------------------------------
namespace v3d {
namespace kernel{
//-----------------------------------------------------------------------------
/**
 * standard c'tor
 */
VKernelIniReader::VKernelIniReader(ServiceList* in_pServiceList)
{
	m_State = ConfigState;
	m_pServiceList = in_pServiceList;
	m_AppName = "";
}

/**
 * d'tor
 */
VKernelIniReader::~VKernelIniReader()
{
}

void VKernelIniReader::OnComment(VStringParam pText)
{
}

void VKernelIniReader::OnElementClose(IVXMLElement* pElement)
{
	std::string ElementName;
	ElementName = pElement->GetName().AsCString();
	if(ElementName == "Services")
		m_State = MainState;
	
}

void VKernelIniReader::OnElementOpen(IVXMLElement* pElement)
{
	std::string sElementName;
	sElementName = pElement->GetName().AsCString();
	
	switch (m_State)
	{
	case ConfigState:
		{
			if(sElementName == "Config")
			{
				m_State = ServiceState;
				vout << "Parsing configuration of ini file:" << vendl;
				vout << "-------------------------------------------------------" << vendl;
			}
			else
			{			
				std::string errorMsg = "xml ini file invalid expected \"Config\", got \"";
				errorMsg += sElementName;
				errorMsg += "\"";
				V3D_THROW(VKernelIniException, errorMsg.c_str());
			}
		} break;
	case ServiceState:
		{
			if(sElementName == "Services")
				m_State = ServiceElementState;
			else
			{			
				std::string errorMsg = "xml ini file invalid expected \"Services\", got \"";
				errorMsg += sElementName;
				errorMsg += "\"";
				V3D_THROW(VKernelIniException, errorMsg.c_str());
			}
		} break;
	case ServiceElementState:
		{
			if(sElementName == "Service")
			{
				std::string sServiceName =
					pElement->GetFirstAttribute()->GetValue().AsCString();
				std::string sServiceDesc =
					pElement->NextAttribute()->GetValue().AsCString();
				std::string sServiceFile =
					pElement->NextAttribute()->GetValue().AsCString();
				vout << "Service Name: " << sServiceName << vendl;
				vout << "Service Description: " << sServiceDesc << vendl;
				vout << "Service Filename: " << sServiceFile << vendl;
				
				m_pServiceList->push_back(ServicePointer(new VServiceProxy(sServiceFile)));
				
			}
		} break;
	case MainState:
		{
			if(sElementName == "Main")
			{
				m_AppName = pElement->GetAttribute("id")->GetValue().AsCString();
				if(m_AppName.length() == 0)
					V3D_THROW(VKernelIniException, "Main application is not valid.");
			}
		}
		
	}
}

void VKernelIniReader::OnFileEnd()
{
	vout << "-------------------------------------------------------" << vendl;
	vout << "Parsing configuration file done" << vendl;
	vout << "-------------------------------------------------------" << vendl;
}

void VKernelIniReader::OnText(VStringParam pText)
{
}

VStringParam VKernelIniReader::GetAppName()
{
	return m_AppName.c_str();
}

//-----------------------------------------------------------------------------
} // namespace v3d
} // namespace kernel
//-----------------------------------------------------------------------------

#include "VKernelIniReader.h"
#include "VKernelException.h"
#include <iostream>
//-----------------------------------------------------------------------------
using namespace v3d::xml;
using namespace std;
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
	std::string ElementName;
	ElementName = pElement->GetName().AsCString();
	
	switch (m_State)
	{
	case ConfigState:
		{
			if(ElementName == "Config")
			{
				m_State = ServiceState;
				cout << "Parsing configuration of ini file" << endl;
				cout << "-------------------------------------------" << endl;
			}
			else
			{			
				std::string errorMsg = "xml ini file invalid expected \"Config\", got \"";
				errorMsg += ElementName;
				errorMsg += "\"";
				V3D_THROW(VKernelIniException, errorMsg.c_str());
			}
		} break;
	case ServiceState:
		{
			if(ElementName == "Services")
				m_State = ServiceElementState;
			else
			{			
				std::string errorMsg = "xml ini file invalid expected \"Services\", got \"";
				errorMsg += ElementName;
				errorMsg += "\"";
				V3D_THROW(VKernelIniException, errorMsg.c_str());
			}
		} break;
	case ServiceElementState:
		{
			if(ElementName == "Service")
			{
				std::string ServiceName = pElement->GetFirstAttribute()->GetValue().AsCString();
				std::string ServiceDesc = pElement->NextAttribute()->GetValue().AsCString();
				std::string ServiceFile = pElement->NextAttribute()->GetValue().AsCString();
				cout << "Service Name: " << ServiceName << endl;
				cout << "Service Description: " << ServiceDesc << endl;
				cout << "Service Filename: " << ServiceFile << endl;

				m_pServiceList->push_back(ServicePointer(new VServiceProxy(ServiceFile)));
				
			}
		} break;
	case MainState:
		{
			if(ElementName == "Main")
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
	cout << "Parsing configuration file done" << endl;
	cout << "-------------------------------------------" << endl;
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

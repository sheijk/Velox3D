#include "VKernel.h"
//-----------------------------------------------------------------------------
#include <Utils/smartptr/VGuards.h>
#include <Error/VException.h>
#include <Kernel/ObjReg/VObjectRegistry.h>

#include "tinyxml/tinyxml.h"

#include <iostream>

using std::string;
using std::cout;
using std::endl;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

VKernel::VKernel()
{
}

VKernel::~VKernel()
{
}

/**
 * loads the ini file and parses it's content. services will
 * be loaded and control will be given to the app service
 */
void VKernel::ProcessIniFile(std::string in_strFileName)
{
	// parse file
	ParseFile(in_strFileName);

	// generate init sequence
	GenerateInitSequence();

	// load and init services
	LoadServices();

	// delegate control to app service
	DelegateControl();
}

struct VServiceInfo
{
	void Parse(TiXmlElement* in_pElement)
	{
		strId = in_pElement->Attribute("id");
		strDesc = in_pElement->Attribute("desc");
		strFileName = in_pElement->Attribute("filename");
	}

	string strId;
	string strDesc;
	string strFileName;
};

/**
 * Parses the xml file and creates a list of service info entries
 */
void VKernel::ParseFile(const string &in_strFileName)
{
	TiXmlElement* pRootNode = 0;
	TiXmlElement* pServiceSectionNode = 0;
	TiXmlElement* pServiceNode = 0;
	TiXmlElement* pMainNode = 0;
	VServiceInfo serviceInfo;
	
	// load xml file
	TiXmlDocument iniDoc(in_strFileName.c_str());
	iniDoc.LoadFile();

	if( iniDoc.Error() )
	{
		V3D_THROW(VKernelException, 
			string("could not load file <") + in_strFileName + string(">"));
	}

	// remove all services
	m_Services.clear();

	// get "Config" Section
	pRootNode = iniDoc.RootElement();

	if( pRootNode == 0 ) V3D_THROW(VKernelException, "no root element");

	cout << "pRootNode: " << pRootNode->Value() << endl;

	// get "Services" Section
	pServiceSectionNode = pRootNode->FirstChildElement();

	if( pServiceSectionNode == 0 ) 
	{
		V3D_THROW(VKernelException, "no \"Config\" section");
	}

	cout << "pServiceSectionNode: " << pServiceSectionNode->Value() << endl;

	// parse all services
	pServiceNode = pServiceSectionNode->FirstChildElement();

	while( pServiceNode != 0 )
	{
		// parse service
		serviceInfo.Parse(pServiceNode);

		/*
		cout << "service:"
			<< "id=\"" << serviceInfo.strId << "\" "
			<< "desc=\"" << serviceInfo.strDesc << "\" "
			<< "filename=\"" << serviceInfo.strFileName << "\""
			<< endl;
		*/

		// add service info to list
		m_Services.push_back(
			ServicePointer(new VServiceProxy(serviceInfo.strFileName)) );

		// get next service info xml element
		pServiceNode = pServiceNode->NextSiblingElement();
	}

	// get "Main" Section
	pMainNode = pServiceSectionNode->NextSiblingElement();

	if( pMainNode == 0 ) V3D_THROW(VKernelException, "main service not found");

	cout << "main service: \"" << pMainNode->Value() << "\"" << endl;

	// parse main service info

	// create service DLL info
}

/**
 * Does nothing so far
 */
void VKernel::GenerateInitSequence()
{
	// get dependencies for all DLLs
	// sort
}

void VKernel::LoadServices()
{
	// intialize services
	ServiceList::iterator serviceIter = m_Services.begin();

	try
	{
		for( ; serviceIter != m_Services.end(); ++serviceIter )
		{
			(*serviceIter)->Initialize(VObjectRegistry::GetInstance());
		}
	}
	catch(VKernelException exc)
	{
		cout << "Error loading service in file <" 
			 << exc.GetErrorFile() 
			 << ">" << endl
			 << "Error information: \""
			 << exc.GetErrorString()
			 << "\"" << endl;
	}
}

void VKernel::DelegateControl()
{
	// get application service

	// start it
}

void VKernel::Shutdown()
{
	// deinitialize all services

	// unload dlls
}

//-----------------------------------------------------------------------------
#include "VKernel.h"
//-----------------------------------------------------------------------------
#include <Utils/smartptr/VGuards.h>
#include <Error/VException.h>

#include "tinyxml/tinyxml.h"

#include <iostream>

using std::string;
using std::cout;
using std::endl;
//-----------------------------------------------------------------------------

class VKernelException : public VException
{
public:
	VKernelException(
		std::string in_Error, 
		std::string in_File, 
		int in_nLine)
		: VException(in_Error, in_File, in_nLine)
	{
	}
};

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

	// load dlls
	LoadDLLs();

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

void VKernel::ParseFile(const string &in_strFileName)
{
	// load xml file
	TiXmlDocument iniDoc(in_strFileName.c_str());
	iniDoc.LoadFile();


	// get "Config Section
	TiXmlElement* pRoot = iniDoc.RootElement();

	if( pRoot == 0 ) V3D_THROW(VKernelException, "no root element");

	cout << "pRoot: " << pRoot->Value() << endl;

	// get "Services" Section
	TiXmlElement* pServiceSection = pRoot->FirstChildElement();

	if( pServiceSection == 0 ) V3D_THROW(VKernelException, "no \"Config\" section");

	cout << "pServiceSection: " << pServiceSection->Value() << endl;

	// parse all services
	TiXmlElement* pService = pServiceSection->FirstChildElement();

	VServiceInfo serviceInfo;

	while( pService != 0 )
	{
		// parse service
		serviceInfo.Parse(pService);

		cout << "service:"
			<< "id=\"" << serviceInfo.strId << "\" "
			<< "desc=\"" << serviceInfo.strDesc << "\" "
			<< "filename=\"" << serviceInfo.strFileName << "\""
			<< endl;

		pService = pService->NextSiblingElement();
	}

	// get "Main" Section
	TiXmlElement* pMain = pServiceSection->NextSiblingElement();

	if( pMain == 0 ) V3D_THROW(VKernelException, "main service not found");

	cout << "main service: \"" << pMain->Value() << "\"" << endl;

	// create service DLL info
}

void VKernel::LoadDLLs()
{
}

void VKernel::GenerateInitSequence()
{
	// get dependencies for all DLLs

	// sort
}

void VKernel::LoadServices()
{
	// intialize services
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
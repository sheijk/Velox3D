#include "TestLib.h"

#include <iostream>
#include <vector>

#include <V3d/Core/VIOStream.h>

// :))
#define protected public
#include "../../Source/Kernel/VKernel.h"
#undef protected

#undef GetMessageA

#include "../../Source/XMLService/VXMLService.h"
#include <V3d/Core/Modules/VModuleBase.h>

#include <V3dLib/Math.h>
#include <V3dLib/Property.h>

#include "../../Source/XMLService/VXMLElement.h"

#include <sstream>

using namespace std;
using namespace v3d;

VSharedPtr<kernel::VKernel> g_pKernel;

VSharedPtr<xml::VXMLService> g_pXMLService;

namespace {
	vbool g_bInitialized = false;
}

void Initialize()
{	
	if( g_bInitialized )
	{
		return;
	}
	
	g_bInitialized = true;
	
	try {
		cout << "Initializing velox... " << endl;
		
		// create kernel
		cout << "\tCreating kernel" << endl;
		g_pKernel.Assign(new kernel::VKernel());
		g_pKernel->CreateObjectRegistry();
		
		// create xml service
		cout << "\tCreating xml service" << endl;
		g_pXMLService.Assign(new xml::VXMLService());
	
		// load local module (from VKernel.cpp)	
		try
		{
			cout << "\tCreating services" << endl;
			v3d::VModuleBase::GetInstance()->Initialize();
		}
		catch(VModuleLoadFailure&)
		{}
		
		cout << "\tSetting test property" << endl;
		property::SetProperty<std::string>("blup", "value of blup");
		
		// initialize glfw
		glfwInit();
	
		cout << "done" << endl;
	}
	catch(VException& e) {
		cout 
			<< "\n\n----------------------------------------\n"
			<< "Exception while initializing:\n"
			<< "Message: \"" << e.GetErrorString() << "\"\n"
			<< "File:    \"" << e.GetErrorFile() << "\"\n"
			<< "Line:    \"" << e.GetErrorLine() << "\"\n"
			<< "XErr:    \"" << e.GetExtendedErrorString() << "\"\n"
			<< "\n";
	}
	catch(...) {
		cout << "An unknown error occurred while initializing\n" << endl;
	}
}

void Shutdown()
{
	cout << "Shuting down velox... ";
	
	// shutdown kernel
	g_pKernel->Shutdown();
	g_pKernel.Release();
	
	cout << "done" << endl;
	
	g_bInitialized = false;
}

void v3d::PrintLn(const char* msg)
{
	vout << msg << vendl;
}

v3d::property::VPropertyManager* GetPropertyManager()
{
	try {
		VServicePtr<property::VPropertyManager> pPropertyManager;
		return &*pPropertyManager;
	}
	catch(VException& e) {
		cout << "Caugth exception in GetPropertyManager: "
			<< e.GetErrorString() << endl;
			
		return 0;
	}
}

v3d::resource::IVResourceManager* GetResourceManager()
{
	try {
		VServicePtr<resource::IVResourceManager> pResourceManager;
		return &*pResourceManager;
	}
	catch(VException& e) {
		return 0;
	}
}

v3d::xml::IVXMLService* GetXMLService()
{
	try {
		VServicePtr<xml::IVXMLService> pXMLService;
		return &*pXMLService;
	}
	catch(VException& e) {
		return 0;
	}
}

v3d::vfs::IVFileSystem* GetFileSystem()
{
	try {
		VServicePtr<vfs::IVFileSystem> pFileSystem;
		return &*pFileSystem;
	}
	catch(VException& e) {
		return 0;
	}
}

std::string ToString(v3d::utils::VStringValue* val)
{
	std::string str = val->Get<std::string>();
	return str;
}

v3d::xml::IVXMLElement* CreateXMLElement(VStringParam in_strName)
{
	v3d::xml::VXMLElement* pElement = new v3d::xml::VXMLElement(in_strName);
	return pElement;
}

//-----------------------------------------------------------------------------
#include <V3d/Graphics.h>
#include <V3d/Scene.h>

using namespace v3d::xml;
using namespace v3d::resource;
using namespace v3d::entity;
using namespace v3d::graphics;
using namespace v3d::scene;

v3d::VSharedPtr<IVPart> CreateModelPart(IVXMLElement* in_pElement)
{
	VModel model;
	
//	IVXMLElement::AttributeIter attribIter = in_pElement->AttributeBegin();
//	
//	while( attribIter.HasNext() )
//	{
//		std::string meshResource = attribIter->GetName();
//		std::string materialResource = attribIter->GetValue().Get<std::string>();
//
//		VModelMesh part(
//			GetResourceData<IVMesh>(meshResource.c_str()),
//			GetResourceData<IVMaterial>(materialResource.c_str())
//			);
//		
//		model.Add(part);
//	}
	
	VSharedPtr<VSceneModelPart> pModelPart(new VSceneModelPart(model));
	
	return pModelPart;
}

class VTestPart : public v3d::entity::VUnconnectedPart
{
	typedef std::map<string, string> SettingsMap;
	SettingsMap m_Settings;
public:
	VTestPart()
	{
		m_Settings["abc"] = "def";
		m_Settings["acc"] = "ddf";
	}
	
	void Activate() {}
	void Deactivate() {}

	virtual void Send(const messaging::VMessage& in_Message, messaging::VMessage* in_pAnswer = 0)
	{
		if( in_pAnswer == 0 || ! in_Message.HasProperty("type") )
			return;
			
		string type = in_Message.Get("type").Get<string>();
			
		if( type == "getSettings" )
		{
			SettingsMap::iterator iter = m_Settings.begin();
			for( ; iter != m_Settings.end(); ++iter)
			{
				in_pAnswer->AddProperty(iter->first, iter->second);
			}
		}
		else if( type == "update") 
		{
			string name = in_Message.Get("name").Get<string>();
			string value = in_Message.Get("value").Get<string>();
			
			m_Settings[name] = value;
		}
	}
	
	void AddSetting(string name, string value)
	{
		m_Settings[name] = value;
	}
	
	static std::string GetDefaultId() { return "x"; }
};

class VConnTestPart : public v3d::entity::VPartBase
{
	VPartConnection<VTestPart> m_pOtherPart;

public:
	VConnTestPart() : m_pOtherPart(VPartDependency::Neighbour, RegisterTo())
	{}
	
	void Activate()
	{
		m_pOtherPart->AddSetting("conntest", "me was here");
	}

	void Deactivate()
	{}
};

v3d::VSharedPtr<v3d::entity::IVPart> CreatePart(
	v3d::xml::IVXMLElement* in_pElement)
{
	std::string type = in_pElement->GetAttributeValue<std::string>("type");

	if( type == "model" ) 
	{
		return CreateModelPart(in_pElement);
	}
	else if( type == "scene" )
	{
		return VSharedPtr<v3d::entity::IVPart>(new v3d::scene::VSimpleScene());
	}
	else if( type == "body" )
	{
		return SharedPtr(new VRigidBodyPart());
	}
	else if( type == "x" )
	{
		return VSharedPtr<v3d::entity::IVPart>(new VTestPart());
	}
	else if( type == "y" )
	{
		return SharedPtr(new VConnTestPart());
	}
	else
	{
		return VSharedPtr<IVPart>(0);
	}
}

v3d::scene::IVShooting* CreateShooting(v3d::graphics::IVDevice* in_pDevice)
{
	VDefaultRenderAlgorithm* pRenderAlgo = new VDefaultRenderAlgorithm();
	
	return new VShooting(in_pDevice, pRenderAlgo);
}

v3d::entity::VEntity* CreateEntity()
{	
	return new VEntity();
}

//-----------------------------------------------------------------------------
//
/* namespace v3d {
	const char* GetModuleName()
	{
		return "v3dswigs";
	}
}
 */

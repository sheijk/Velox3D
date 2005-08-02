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
	
	IVXMLElement::AttributeIter attribIter = in_pElement->AttributeBegin();
	
	while( attribIter.HasNext() )
	{
		std::string meshResource = attribIter->GetName();
		std::string materialResource = attribIter->GetValue().Get<std::string>();

		VModelMesh part(
			GetResourceData<IVMesh>(meshResource.c_str()),
			GetResourceData<IVMaterial>(materialResource.c_str())
			);
		
		model.Add(part);
	}
	
	VSharedPtr<VSceneModelPart> pModelPart(new VSceneModelPart(model));
	
	return pModelPart;
}

v3d::VSharedPtr<v3d::entity::IVPart> CreatePart(
	v3d::xml::IVXMLElement* in_pElement)
{
	std::string type = in_pElement->GetAttributeValue<std::string>("type");

	if( type == "gfxm" ) 
	{
		return CreateModelPart(in_pElement);
	}
	else
	{
		return VSharedPtr<IVPart>(0);
	}
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

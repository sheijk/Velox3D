/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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

#include <V3d/Math.h>
#include <V3d/Property.h>

#include "../../Source/XMLService/VXMLElement.h"

#include <sstream>

#include <V3d/Entity/IVEntitySerializationService.h>
#include <V3d/Entity/VGenericPartParser.h>
#include <V3d/Utils/VRegisterGuard.h>

#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/operations.hpp>

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
	
	//try {
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
	//}
	//catch(VException& e) {
	//	cout 
	//		<< "\n\n----------------------------------------\n"
	//		<< "Exception while initializing:\n"
	//		<< "Message: \"" << e.GetErrorString() << "\"\n"
	//		<< "File:    \"" << e.GetErrorFile() << "\"\n"
	//		<< "Line:    \"" << e.GetErrorLine() << "\"\n"
	//		<< "XErr:    \"" << e.GetExtendedErrorString() << "\"\n"
	//		<< "\n";
	//}
	//catch(...) {
	//	cout << "An unknown error occurred while initializing\n" << endl;
	//}
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

v3d::entity::IVEntitySerializationService* GetEntitySerializationService()
{
	try {
		entity::VEntitySerializationServicePtr pSerialService;
		return &*pSerialService;
	}
	catch(VException& e) {
		return 0;
	}
}

v3d::tags::VTagRegistry* GetTagRegistry()
{
	try
	{
		tags::VTagRegistryPtr pTagRegistry;
		return &*pTagRegistry;
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
	
	VSharedPtr<VModelPart> pModelPart(new VModelPart(model));
	
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
V3D_TYPEINFO_WITHPARENT(VTestPart, v3d::entity::IVPart);

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
	
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }
};
V3D_TYPEINFO_WITHPARENT(VConnTestPart, v3d::entity::IVPart);

template<typename PartType>
VPartAndId PartWithId(PartType* in_pPart, const std::string& in_Id)
{
	VPartAndId partAndId;
	
	partAndId.part = SharedPtr(in_pPart);
	partAndId.id = in_Id;
	
	return partAndId;
}

VPartAndId CreatePart(v3d::xml::IVXMLElement* in_pElement)
{
	std::string type = in_pElement->GetAttributeValue<std::string>("type");
	VPartAndId result;
	result.SetId(type);

//	if( type == "model" ) 
//	{
//		result.SetPart(CreateModelPart(in_pElement));
//	}
//	else 
	if( type == "scene" )
	{
		vout << "creating scene. ";
		VNaiveSceneManagerPart* pSceneManager = new v3d::scene::VNaiveSceneManagerPart();
		
		vout << "building smart pointer.";
		VSharedPtr<v3d::scene::VNaiveSceneManagerPart> smartptr(pSceneManager);
		
		vout << "return " << vendl;
		result.SetPart(smartptr);
		result.SetId(VNaiveSceneManagerPart::GetDefaultId());
	}
	else if( type == "body" )
	{
		result.SetPart(SharedPtr(new VRigidBodyPart()));
	}
//	else if( type == "x" )
//	{
//		result.SetPart(SharedPtr(new VTestPart()));
//	}
	else if( type == "y" )
	{
		result.SetPart(SharedPtr(new VConnTestPart()));
	}
//	else if( type == "shooting" ) {
//	}
	else
	{
		VServicePtr<entity::IVEntitySerializationService> serializer;
		//serializer->DumpInfo();
		result.SetPart(serializer->ParsePart(*in_pElement));
	}
	
	return result;
}

namespace {
	entity::VGenericPartParser<VTestPart> testParser();
}

v3d::scene::IVShooting* CreateShooting(v3d::graphics::IVDevice* in_pDevice)
{
//	VDefaultRenderAlgorithm* pRenderAlgo = new VDefaultRenderAlgorithm();
	
//	return new VShooting(in_pDevice, pRenderAlgo);
	VSimpleShooting* pShooting = new VSimpleShooting();
	pShooting->SetRenderTarget(in_pDevice);
	return pShooting;
}

v3d::entity::VEntity* CreateEntity()
{	
	return new VEntity();
}

#include "../../Source/Graphics/OpenGL/Materials/VCGFXMaterial.h"
using namespace v3d::graphics;

bool replaceCGFXSource(v3d::resource::VResource* in_pResource, const std::string& in_strSource)
{
	try
	{
//		vout << "replacing cgfx source in " << in_pResource->GetQualifiedName()
//			<< " with <<" << in_strSource << ">>" << vendl;
			
		in_pResource->GetData<IVMaterial>();
		VResourceDataPtr<VCGFXMaterial> cgfx = in_pResource->GetMutableData<VCGFXMaterial>();
		
		return cgfx->SetShaderSource(in_strSource);
	}
	catch(VException& e)
	{
		vout << e.GetErrorString() << vendl;
		return false;
	}		
}

#include <V3d/Resource/Types/VTextFile.h>

void setTextFile(v3d::resource::VResource* in_pResource, const std::string& in_strSource)
{
	try
	{
		if( ! in_pResource->ContainsData<VTextFile>() )
		{
			VTextFile* pTextFile = new VTextFile();
			pTextFile->SetContent(in_strSource);
			in_pResource->AddData(pTextFile);
		}
	}
	catch(VException& e)
	{
		vout << e.GetErrorString() << vendl;
	}
}

//void UpdateParts(vfloat32 in_fSeconds, v3d::entity::VEntity* in_pEntity)
//{
//	if( in_pEntity == 0 )
//		return;
//
//	VRangeIterator<IVPart> part = in_pEntity->PartIterator();
//    while( part.HasNext() )
//	{
//		IVUpdateablePart* pUpdateablePart = part->Convert<IVUpdateablePart>();
//		if( pUpdateablePart != NULL )
//		{
//			pUpdateablePart->Update(in_fSeconds);
//		}
//
//		++part;
//	}
//}

bool CanBeUpdated(v3d::entity::IVPart* in_pPart)
{
	if( in_pPart != 0 )
		return in_pPart->IsOfType<IVUpdateablePart>();
	else
		return false;
}

void UpdatePart(vfloat32 in_fSeconds, v3d::entity::IVPart* in_pPart)
{
	if( in_pPart == 0 )
		return;

	IVUpdateablePart* updateablePart = in_pPart->Convert<IVUpdateablePart>();

	if( updateablePart != 0 )
	{
		updateablePart->Update(in_fSeconds);
	}
}

namespace {
	template<typename T>
	T* GetPart(VEntity* in_pEntity)
	{
		if( in_pEntity != NULL )
		{
			VRangeIterator<IVPart> part = in_pEntity->PartIterator();
			while(part.HasNext())
			{
                T* t = part->Convert<T>();

				if( t != NULL )
					return t;

				++part;
			}

			return NULL;
		}
		else
		{
			return NULL;
		}
	}
}

math::VRBTransform GetTransform(VEntity* in_pEntity)
{
	VRigidBodyPart* pRBPart = GetPart<VRigidBodyPart>(in_pEntity);

	if( pRBPart != NULL )
		return pRBPart->GetTransform();
	else
		return math::VRBTransform();	
}

void SetTransform(VEntity* in_pEntity, const math::VRBTransform& in_Transform)
{
	VRigidBodyPart* pRBPart = GetPart<VRigidBodyPart>(in_pEntity);

	if( pRBPart != NULL )
		pRBPart->SetTransform(in_Transform);
}

#include <V3d/Utils/VInputPart.h>
#include "../../Source/InputLib/VDIInputManager.h"

v3d::scene::IVShooting* FindShooting(v3d::entity::VEntity* in_pEntity)
{
	if( in_pEntity != 0 )
		return in_pEntity->GetPart<IVShooting>();
	else
		return 0;
}

v3d::scene::IVShooting* ToShooting(v3d::entity::IVPart* in_pPart)
{
	if( in_pPart != 0 )
		return in_pPart->Convert<IVShooting>();
	else
		return 0;
}


v3d::input::IVInputManager* CreateInputManager(int hwnd)
{
	return new input::VDIInputManager(HWND(hwnd));
}

void TellInputManager(
	v3d::entity::VEntity* pEntity, 
	v3d::input::IVInputManager* pInputManager)
{
	if( pEntity != 0 )
	{
		utils::VInputPart* pInputPart = pEntity->GetPart<utils::VInputPart>();

		if( pInputPart != 0 )
		{
			pInputPart->SetInputManager(pInputManager);
		}
	}
}

void DumpDir(vfs::IVDirectory& dir, const std::string& prefix)
{
	const std::string indent = ".\t";

	vout << prefix << dir.GetName() << "/" << vendl;

	VRangeIterator<vfs::IVDirectory> childdirs = dir.SubDirs();
	while( childdirs.HasNext() )
	{
		DumpDir(*childdirs, prefix + indent);
		++childdirs;
	}

	VRangeIterator<vfs::IVFile> files = dir.Files();
	while( files.HasNext() )
	{
		vout << prefix << indent << files->GetName() << vendl;
		++files;
	}
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


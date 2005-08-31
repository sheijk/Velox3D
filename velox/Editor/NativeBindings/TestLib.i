%module v3d
%{
#include "TestLib.h"
using namespace v3d;
using namespace v3d::resource;
using namespace v3d::xml;
using namespace v3d::utils;
using namespace v3d::vfs;
using namespace v3d::entity;
using namespace v3d::messaging;
using namespace v3d::scene;
using namespace v3d::graphics;

typedef IVPart::Dependency Dependency;

#undef CreateFile
#undef DeleteFile
%}

// wrap std::string with java.lang.String
%include "std_string.i"

// wrap c++ enums to java 1.5 enums
%include "enums.swg"

//-----------------------------------------------------------------------------

namespace v3d {
}

%pragma(java) modulecode=%{
	static {
		try {
			System.loadLibrary("ScriptingDLL");
			Initialize();
		}
		catch(Exception e) {
			System.err.println("Could not load ScriptingDLL");
			System.err.println(e);
		}
	}
%}

%javaexception("java.lang.Exception") Initialize {
	try {
		$action
	}
	catch(VException& e) {
		jclass clazz = jenv->FindClass("java/lang/RuntimeException");
		std::stringstream msg;
		msg << "[" << e.GetErrorFile() << ":" << e.GetErrorLine()
			<< "] " << e.GetErrorString();
		std::string msgString = msg.str();
		jenv->ThrowNew(clazz, msgString.c_str());
		return $null;
	}
	catch(...) {
		jclass clazz = jenv->FindClass("java/lang/RuntimeException");
		jenv->ThrowNew(clazz, "Unknown exception occured");
		return $null;
	}
}

%javaexception("java.lang.RuntimeException") v3d::vfs::IVFileSystem::MountFromXML {
	try {
		$action
	}
	catch(VException& e) {
		jclass clazz = jenv->FindClass("java/lang/Exception");
		std::stringstream msg;
		msg << "[" << e.GetErrorFile() << ":" << e.GetErrorLine()
			<< "] " << e.GetErrorString();
		std::string msgString = msg.str();
		jenv->ThrowNew(clazz, msgString.c_str());
		return $null;
	}
}

//-----------------------------------------------------------------------------
// editor utils
%include "VView.h"

//-----------------------------------------------------------------------------
// core types

%include "../../API/V3d/Core/VTypes.h"
%include "../../API/V3d/Core/VException.h"

%rename(Next) v3d::VRangeIterator::operator++();
%ignore v3d::VRangeIterator::operator++(int);
%rename(Equals) v3d::VRangeIterator::operator==;
%ignore v3d::VRangeIterator::operator!=;
%rename(SetTo) v3d::VRangeIterator::operator=;
%rename(Get) v3d::VRangeIterator::operator*;
%ignore v3d::VRangeIterator::operator->;
%include "VRangeIter.h"
%rename(Next) v3d::VRangeIterator<const std::string>::operator++;

%template(VStringIter) v3d::VRangeIterator<const std::string>;

// bind VStringValue and instantiate the Get<T> function for some common types
%include "../../API/V3dLib/Utils/VStringValue.h"
%extend v3d::utils::VStringValue {
	%template(ToString) Get<std::string>;
	%template(ToInt) Get<int>;
	%template(ToFloat) Get<float>;
};

%rename(Assign) v3d::VString::operator=;
%rename(toString) v3d::VString::operator const char*;
%ignore v3d::VString::operator<;
%ignore v3d::VString::operator!=;
%ignore operator+(const vchar* in_pcChar, const VString& in_VStr);
%ignore operator+(const VString& in_VStr, const vchar* in_pcChar);
%ignore operator==(const VString& left, const VString& right);
%ignore operator!=(const VString& left, const VString& right);
%include "../../API/V3d/Core/Wrappers/VString.h"

%rename(Assign) v3d::VSharedPtr::operator=;
%include "VSharedPtr.h"
//%include "../../API/V3d/Core/SmartPtr/VSharedPtr.h"
%include "../../API/V3d/Core/SmartPtr/VGuards.h"

//-----------------------------------------------------------------------------
// utils

%rename(Assign) v3d::utils::VFourCC::operator==;
%ignore v3d::utils::VFourCC::operator!=;
%ignore v3d::utils::VFourCC::operator<;
%rename(toString) v3d::utils::VFourCC::AsStdString;
%include "../../API/V3dLib/Utils/VFourCC.h"

//-----------------------------------------------------------------------------
// property manager
%include "../../API/V3dLib/Property/VPropertyManager.h"

//-----------------------------------------------------------------------------
// virtual file system

%include "../../API/V3d/VFS/VFlags.h"
%include "../../API/V3d/VFS/IVAccessRights.h"
%include "../../API/V3d/VFS/VAccessRightsFlags.h"
%include "../../API/V3d/VFS/IVStream.h"
%include "../../API/V3d/VFS/IVOfflineStream.h"
%include "../../API/V3d/VFS/IVBufferStream.h"
%include "../../API/V3d/VFS/IVFileSysObject.h"
%template(VBufferStreamPtr) v3d::VSharedPtr<v3d::vfs::IVBufferStream>;
%include "../../API/V3d/VFS/IVFile.h"
%template(VFileIterator) v3d::VRangeIterator<v3d::vfs::IVFile>;
%template(VDirectoryIterator) v3d::VRangeIterator<v3d::vfs::IVDirectory>;
%ignore v3d::vfs::IVDirectory::Files() const;
%ignore v3d::vfs::IVDirectory::SubDirs() const;
%include "../../API/V3d/VFS/IVDirectory.h"
%include "../../API/V3d/VFS/IVLegalOperations.h"
%include "../../API/V3d/VFS/IVFileSystem.h"

//-----------------------------------------------------------------------------
// resource system
%template(VResourceIterator) v3d::VRangeIterator<v3d::resource::VResource>;
%ignore v3d::resource::VResource::ChildIterator() const;
%include "../../API/V3d/Resource/VResource.h"
%include "../../API/V3d/Resource/VResourceId.h"
%ignore v3d::resource::IVResourceManager::RegisterResourceType;
%include "../../API/V3d/Resource/IVResourceManager.h"

// xml service
//-----------------------------------------------------------------------------
%template(VXMLAttributeIterator) v3d::VRangeIterator<v3d::xml::IVXMLAttribute>;
%template(VXMLNodeIterator) v3d::VRangeIterator<v3d::xml::IVXMLNode>;
%include "../../API/V3d/XML/IVXMLNode.h"
%include "../../API/V3d/XML/IVXMLAttribute.h"
%include "../../API/V3d/XML/IVXMLComment.h"
%ignore v3d::xml::IVXMLElement::GetFirstAttribute;
%ignore v3d::xml::IVXMLElement::NextAttribute;
%ignore v3d::xml::IVXMLElement::VisitChildren;
%include "../../API/V3d/XML/IVXMLElement.h"
%include "../../API/V3d/XML/IVXMLText.h"

%ignore v3d::xml::IVXMLService::CreateXMLWriter;
%ignore v3d::xml::IVXMLService::Visit;
%template(VXMLElementPtr) v3d::VSharedPtr<v3d::xml::IVXMLElement>;
%include "../../API/V3d/XML/IVXMLService.h"

// messaging
//-----------------------------------------------------------------------------

%include "../../API/V3d/Messaging/VMessage.h"
%include "../../API/V3d/Messaging/VProtocol.h"

// graphics
//-----------------------------------------------------------------------------
#define V3D_DEPRECATED
%include "../../API/V3d/Graphics/IVDevice.h"

// entity system
//-----------------------------------------------------------------------------

%template(VEntityPtr) v3d::VSharedPtr<v3d::entity::VEntity>;
%template(VPartPtr) v3d::VSharedPtr<v3d::entity::IVPart>;
%template(VEntityIterator) v3d::VRangeIterator<v3d::entity::VEntity>;
%template(VPartIterator) v3d::VRangeIterator<v3d::entity::IVPart>;
%include "../../API/V3d/Entity/IVPart.h"
%include "../../API/V3d/Entity/VEntity.h"

%javaexception("Exception") v3d::entity::IVSceneParser::ParsePart {
	try {
		$action
	}
	catch(VException& e) {
		jclass clazz = jenv->FindClass("java/lang/RuntimeException");
		std::string msgString = e.ToString();
		jenv->ThrowNew(clazz, msgString.c_str());
		return $null;
	}
	catch(...) {
		jclass clazz = jenv->FindClass("java/lang/RuntimeException");
		jenv->ThrowNew(clazz, "Unknown exception occured");
		return $null;
	}
}

%template(VShootingPtr) v3d::VSharedPtr<v3d::scene::IVShooting>;
%template(VSceneManagerPtr) v3d::VSharedPtr<v3d::scene::IVScene>;
%include "../../API/V3d/Scene/IVShooting.h"
%include "../../API/V3d/Scene/IVScene.h"

%ignore v3d::entity::IVSceneParser::Register;
%ignore v3d::entity::IVSceneParser::Unregister;
%include "../../API/V3d/Entity/IVSceneParser.h"

//-----------------------------------------------------------------------------
%include "TestLib.h"

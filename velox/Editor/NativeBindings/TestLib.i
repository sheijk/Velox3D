/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

%module(directors="1") v3d
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
using namespace v3d::math;
using namespace v3d::input;
using namespace v3d::editor;

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

/*
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
*/

// add this code to every generated function (?)
%javaexception("java.lang.RuntimeException") {
	try {
//		std::cout << "calling a c++ function" << std::endl;
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


%include "Core.i"
%include "Editor.i"
%include "Math.i"
%include "Utils.i"
%include "VFS.i"
%include "Resource.i"
%include "XML.i"
%include "Messaging.i"
%include "Graphics.i"
%include "Tags.i"
%include "Entity.i"
%include "Scene.i"

%include "../../API/V3d/Input/IVInputManager.h"
//-----------------------------------------------------------------------------
%include "TestLib.h"


/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/Core/Modules/VModuleBase.h>

//-----------------------------------------------------------------------------
#include "VirtualFileSystem/VStreamFactory.h"
#include "VirtualFileSystem/VSimpleVfs.h"
#include "VirtualFileSystem/VDataProviderPool.h"
#include "VirtualFileSystem/VFileDataProvider.h"
#include "VirtualFileSystem/VTempDataProvider.h"

#include "ConfigFiles/VConfigProvider.h"
#include "UpdateManager/VUpdateManager.h"
#include "SystemManager/VSystemManager.h"

#include <V3d/Property/VPropertyManager.h>

// thank you, windows.h -- it's a feature, not a bug :P -ins
#undef NO_ERROR

#include "Resource/VResourceManager.h"
#include "Resource/Types/VImageResourceType.h"
#include "Resource/Types/VTextureStateResType.h"
#include "Resource/Types/VGLVertexStreamResType.h"
#include "Resource/Types/VFileNameResType.h"
#include "Resource/Types/VImported3DSResourceType.h"
#include "Resource/Types/VMeshResourceType.h"
#include "Resource/Types/VMaterialResourceType.h"
#include "Resource/Types/VMeshGeneratorResType.h"
#include "Resource/Types/VOffscreenDeviceResType.h"
#include "Resource/Types/VPBufferTextureResType.h"
#include "Resource/Types/VTextFileResType.h"
#include "Resource/Types/VXMLModelResourceType.h"

#include "ImageService/VImageFactory.h"
#include "ImageService/VDevILLoader.h"
#include "ImageService/VDevILSaver.h"
#include "ImageService/VImageManipulator.h"

#include "WindowService/VWindowManagerWin32.h"

#include "Graphics/OpenGL/VGraphicsService.h"

#include "Error/VErrorConsoleListener.h"
#include "Error/VErrorService.h"
#include <v3d/Utils/VAllFilter.h>

#include <V3d/Entity/VEntityManager.h>

#include "Entity/VEntitySerializationService.h"
//#include "Entity/Parsers/VSceneModelParser.h"

#include <V3d/Tags/VTagRegistry.h>

#include <V3d/Utils/VRegisterGuard.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::vfs;
using namespace v3d::config;
using namespace v3d::updater;
using namespace v3d::system;
using namespace v3d::image;
using namespace v3d::window;
using namespace v3d::error;
using v3d::utils::VAllFilter;
using namespace v3d::property;
using namespace v3d::entity;
using namespace v3d::resource;
using namespace v3d::graphics;
//-----------------------------------------------------------------------------

class VVeloxModules : public v3d::VModuleBase
{
	// vfs
	VSharedPtr<VStreamFactory> g_pStreamFac;
	VSharedPtr<VSimpleVfs> g_pFileSys;
	VSharedPtr<VDataProviderPool> g_pDataProvPool;
	VSharedPtr<VFileDataProvider> g_pFileDataProv;
	VSharedPtr<VTempDataProvider> g_pTempDataProv;

	// config
	VSharedPtr<VConfigProvider> g_pConfigProvider;

	// resources
	VSharedPtr<IVResourceManager> g_pResourceManager;

	// updater
	VSharedPtr<VUpdateManager> g_pUpdater;

	// system
	VSharedPtr<system::VSystemManager> g_pSystemManager;
	VSharedPtr<graphics::VGraphicsService> g_pGraphicsService;

	// image
	VSharedPtr<VImageFactory> g_pImageFactory;
	VSharedPtr<IVImageLoader> g_pDevILLoader;
	VSharedPtr<IVImageSaver>  g_pDevILSaver;
	VSharedPtr<IVImageManipulator> g_pImageManipulator;
	

	// window
	VSharedPtr<VWindowManagerWin32> g_pWindowManagerWin;

	// error
	VSharedPtr<VErrorService> g_pErrorService;
	VSharedPtr<VErrorConsoleListener> g_pConsoleListener;

	// property
	VSharedPtr<VPropertyManager> g_pPropertyManager;

	// entity
	VSharedPtr<VEntityManager> g_pEntityManager;

	VSharedPtr<VEntitySerializationService> g_pEntitySerializer;
	//VSharedPtr<VSceneModelParser> g_pSceneModelParser;

	VSharedPtr<tags::VTagRegistry> g_pTagRegistry;

public:
	VVeloxModules()
	{
	}

	virtual void Initialize();
	virtual void Shutdown();
};

const char* v3d::GetModuleName()
{
	return "services";
}

namespace {
	VVeloxModules g_VeloxModules;
}
//-----------------------------------------------------------------------------
void VVeloxModules::Initialize()
{
	// vfs
	g_pStreamFac.Assign(new VStreamFactory("vfs.strfact"));
	g_pDataProvPool.Assign(new VDataProviderPool("vfs.dpp"));
	g_pFileDataProv.Assign(new VFileDataProvider());
	g_pDataProvPool->RegisterDataProvider(g_pFileDataProv.Get());
	g_pFileSys.Assign(new VSimpleVfs("vfs.fs", "vfs.xml"));
	g_pTempDataProv.Assign(new VTempDataProvider());

	// misc
	g_pConfigProvider.Assign(new VConfigProvider("config.provider"));
	g_pUpdater.Assign(new VUpdateManager("updater.service"));
	g_pSystemManager.Assign(new system::VSystemManager("system.service"));

	// resource manager
	g_pResourceManager.Assign(new VResourceManager("resource.manager"));
	// create and add some resource types
	g_pResourceManager->RegisterResourceType(
		VSharedPtr<IVResourceType>(new VImageResourceType()));
	g_pResourceManager->RegisterResourceType(
		VSharedPtr<IVResourceType>(new VTextureStateResType()));
	g_pResourceManager->RegisterResourceType(
		VSharedPtr<IVResourceType>(new VGLVertexStreamResType()));
	g_pResourceManager->RegisterResourceType(
		VSharedPtr<IVResourceType>(new VFileNameResType()));
	g_pResourceManager->RegisterResourceType(SharedPtr(new VXMLModelResourceType()));

	g_pResourceManager->RegisterResourceType(
		VSharedPtr<IVResourceType>(new VOffscreenDeviceResType()));

	g_pResourceManager->RegisterResourceType(
		VSharedPtr<IVResourceType>(new VPBufferTextureResType()));

	g_pResourceManager->RegisterResourceType(
		VSharedPtr<IVResourceType>(new utils::VImported3DSResourceType()));

	g_pResourceManager->RegisterResourceType(
		VSharedPtr<IVResourceType>(new graphics::VMeshResourceType()));
	
	g_pResourceManager->RegisterResourceType(
		VSharedPtr<IVResourceType>(new graphics::VMaterialResourceType()));

	g_pResourceManager->RegisterResourceType(SharedPtr(new VMeshGeneratorResType()));

	g_pResourceManager->RegisterResourceType(SharedPtr(new VTextFileResType()));

	// image
	g_pImageFactory.Assign(new VImageFactory());
	g_pDevILLoader.Assign(new VDevILLoader());
	g_pDevILSaver.Assign(new VDevILSaver());
	g_pImageManipulator.Assign(new VImageManipulator());

	// window
	g_pWindowManagerWin.Assign(new VWindowManagerWin32());

	g_pGraphicsService.Assign(new VGraphicsService());

	// error
	// create log devices
	g_pConsoleListener.Assign( new VErrorConsoleListener() );

	// create service object
	g_pErrorService.Assign( new VErrorService() );

	// register standard listener
	//TODO: hack entfernen
	g_pErrorService->RegisterListener( g_pConsoleListener.Get(), new VAllFilter()  );

	// property service
	g_pPropertyManager.Assign(new VPropertyManager("property.manager"));

	// entity service
	g_pEntityManager.Assign(new VEntityManager());

	g_pEntitySerializer.Assign(new VEntitySerializationService());
	//g_pSceneModelParser.Assign(new VSceneModelParser());
	//g_pSceneParser->Register(&*g_pSceneModelParser);

	g_pTagRegistry.Assign(new tags::VTagRegistry());

	utils::VRegisterGuardBase::RegisterAll();
}

void VVeloxModules::Shutdown()
{
	utils::VRegisterGuardBase::UnregisterAll();

	g_pTagRegistry.Release();

	// entity
	//g_pSceneParser->Unregister(g_pSceneModelParser->GetType());
	//g_pSceneModelParser.Release();
	g_pEntitySerializer.Release();

	g_pEntityManager.Release();

	// property
	g_pPropertyManager.Release();

	// error
	g_pErrorService->UnregisterListener( g_pConsoleListener.Get() );
	g_pConsoleListener.Release();
	g_pErrorService.Release();

    g_pGraphicsService.Release();

	// window
	g_pWindowManagerWin.Release();

	// image
	g_pImageFactory.Release();

	// resource
	g_pResourceManager.Release();

	// misc
	g_pUpdater.Release();
	g_pConfigProvider.Release();
	g_pSystemManager.Release();

	// vfs
	g_pFileSys.Release();
	g_pStreamFac.Release();
}


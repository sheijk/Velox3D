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

#include <V3dLib/Property/VPropertyManager.h>

// thank you, windows.h -- it's a feature, not a bug :P -ins
#undef NO_ERROR

#include "Resource/VResourceManager.h"
#include "Resource/Types/VImageResourceType.h"
#include "Resource/Types/VTextureStateResType.h"
#include "Resource/Types/VGLVertexStreamResType.h"
#include "Resource/Types/VFileNameResType.h"

#include "ImageService/VImageFactory.h"
#include "ImageService/VDevILLoader.h"
#include "ImageService/VDevILSaver.h"
#include "ImageService/VImageManipulator.h"

#include "WindowService/VWindowManagerWin32.h"

#include "Error/VErrorConsoleListener.h"
#include "Error/VErrorService.h"
#include <v3d/Utils/VAllFilter.h>

#include <V3d/Entity/VEntityManager.h>
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
	VPointer<VStreamFactory>::AutoPtr g_pStreamFac;
	VPointer<VSimpleVfs>::AutoPtr g_pFileSys;
	VPointer<VDataProviderPool>::AutoPtr g_pDataProvPool;
	VPointer<VFileDataProvider>::AutoPtr g_pFileDataProv;
	VPointer<VTempDataProvider>::AutoPtr g_pTempDataProv;

	// config
	VPointer<VConfigProvider>::AutoPtr g_pConfigProvider;

	// resources
	VPointer<IVResourceManager>::AutoPtr g_pResourceManager;

	// updater
	VPointer<VUpdateManager>::AutoPtr g_pUpdater;

	// system
	VPointer<system::VSystemManager>::AutoPtr g_pSystemManager;

	// image
	VPointer<VImageFactory>::AutoPtr g_pImageFactory;
	VPointer<IVImageLoader>::AutoPtr g_pDevILLoader;
	VPointer<IVImageSaver>::AutoPtr  g_pDevILSaver;
	VPointer<IVImageManipulator>::AutoPtr g_pImageManipulator;
	

	// window
	VPointer<VWindowManagerWin32>::AutoPtr g_pWindowManagerWin;

	// error
	VPointer<VErrorService>::AutoPtr g_pErrorService;
	VPointer<VErrorConsoleListener>::AutoPtr g_pConsoleListener;

	// property
	VPointer<VPropertyManager>::AutoPtr g_pPropertyManager;

	// entity
	VPointer<VEntityManager>::AutoPtr g_pEntityManager;

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

	// image
	g_pImageFactory.Assign(new VImageFactory());
	g_pDevILLoader.Assign(new VDevILLoader());
	g_pDevILSaver.Assign(new VDevILSaver());
	g_pImageManipulator.Assign(new VImageManipulator());

	// window
	g_pWindowManagerWin.Assign(new VWindowManagerWin32());

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
}

void VVeloxModules::Shutdown()
{
	// entity
	g_pEntityManager.Release();

	// property
	g_pPropertyManager.Release();

	// error
	//unregister debug loggers
	g_pErrorService->UnregisterListener( g_pConsoleListener.Get() );

	// delete debug loggers
	g_pConsoleListener.Release();

	// delete and unregister service object
	g_pErrorService.Release();

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

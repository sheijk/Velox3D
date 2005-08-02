#include <V3dLib/Property/VPropertyManager.h>
#include <V3d/Resource.h>


#include <V3d/XML.h>

#include <V3dLib/Utils/VFourCC.h>

#include <V3d/Vfs.h>

#include <V3d/Entity.h>
#include <V3d/Entity/IVSceneParser.h>
#include <V3d/Messaging/VProtocol.h>

#include <string>
#include <V3d/OpenGL.h>
#include <windows.h>
#include <GL/glfw.h>

#include "VView.h"

void Initialize();
void Shutdown();

namespace v3d {
	void PrintLn(const char*);
}

v3d::property::VPropertyManager* GetPropertyManager();
v3d::resource::IVResourceManager* GetResourceManager();
v3d::xml::IVXMLService* GetXMLService();
v3d::vfs::IVFileSystem* GetFileSystem();

std::string ToString(v3d::utils::VStringValue* val);

v3d::xml::IVXMLElement* CreateXMLElement(v3d::VStringParam in_strName);

v3d::VSharedPtr<v3d::entity::IVPart> CreatePart(
	v3d::xml::IVXMLElement* in_pElement);

v3d::entity::VEntity* CreateEntity();

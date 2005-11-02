#include <V3dLib/Property/VPropertyManager.h>
#include <V3d/Resource.h>

#include <V3d/Math/VMatrixOps.h>
#include <V3d/Math/TransformationOps.h>

#include <V3d/XML.h>

#include <V3dLib/Utils/VFourCC.h>

#include <V3dLib/Graphics/Misc/VCamera.h>

#include <V3d/Vfs.h>

#include <V3d/Entity.h>
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
v3d::entity::IVEntitySerializationService* GetEntitySerializationService();

std::string ToString(v3d::utils::VStringValue* val);

v3d::xml::IVXMLElement* CreateXMLElement(v3d::VStringParam in_strName);

v3d::scene::IVShooting* CreateShooting(v3d::graphics::IVDevice* in_pDevice);

bool replaceCGFXSource(v3d::resource::VResource* in_pResource, const std::string& in_strSource);

void setTextFile(v3d::resource::VResource* in_pResource, const std::string& in_strSource);

class VPartAndId {
public:
	v3d::VSharedPtr<v3d::entity::IVPart> GetPart() const
	{
		return part;
	}

	void SetPart(const v3d::VSharedPtr<v3d::entity::IVPart>& in_Part)
	{
		part = in_Part;
	}

	std::string GetId() const
	{
		return id;
	}

	void SetId(const std::string& in_Id)
	{
		id = in_Id;
	}

private:
	v3d::VSharedPtr<v3d::entity::IVPart> part;
	std::string id;
};

VPartAndId CreatePart(v3d::xml::IVXMLElement* in_pElement);

v3d::entity::VEntity* CreateEntity();

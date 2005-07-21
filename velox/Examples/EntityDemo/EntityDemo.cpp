#include <V3d/Core.h>
#include <V3d/Entity/VEntityManager.h>

#include "VDataPart.h"
#include "VSetterPart.h"
#include "VReaderPart.h"
#include "VHierarchyPart.h"

#include <V3d/Resource.h>

#include <string>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::entity;
using v3d::utils::VFourCC;
using std::string;

/**
 * Rudimentary demo of the entity system.
 *
 * @author sheijk
 */
class VEntityDemoApp : public VVeloxApp
{
public:
	virtual vint Main(std::vector<std::string> args);
};

class Blub
{
public:
	Blub(vint v) : val(v)
	{}

	vint GetVal() const { return val; }

private:
	vint val;
};

V3D_TYPEINFO(Blub);
V3D_TYPEINFO(int);

class BlubType : public resource::IVResourceType
{
	std::vector<VTypeInfo> m_CreatedTypes;
public:
	BlubType() 
	{
		m_CreatedTypes.push_back(GetTypeInfo<Blub>());
	}

	virtual VRangeIterator<VTypeInfo> CreatedTypes()
	{
		return CreateIterator(m_CreatedTypes.begin(), m_CreatedTypes.end());
	}

	virtual VTypeInfo GetTypeId() const
	{
		return GetTypeInfo<Blub>();
	}

	virtual vbool Generate(resource::VResource* in_pResource, VTypeInfo)
	{
		resource::VResourceDataPtr<const vint> pIntData = in_pResource->GetData<vint>();

        Blub* pBlub = new Blub(*pIntData);
		in_pResource->AddData(pBlub);

		return true;
	}
};

/**
 * This example demonstratetes sharing of data between multiple subsystems
 * The reader and setter communicate by using the data part without knowing
 * about each other. In a real application the setter and reader part will
 * need to add/remove themselves to/from their subsystems when (De)Activate
 * will be called.
 *
 * This can be used for decoupling of subsystems. For example a position part
 * holding a Vector3f position could be written to by the physics system and be
 * read by the graphics system. A sound part might easily be attached reading
 * the position as well without affecting any existing system. It could even
 * be used to compose new entity types in an editor. The physics system might
 * be replaced by an animation system for ingame cinematics without any changes
 * to other parts of the engine, etc.
 *
 * @author sheijk
 */
vint VEntityDemoApp::Main(std::vector<std::string> args)
{
	VEntity ent;
	VSettingPart* pSetter = 0;
	VReaderPart* pReader = 0;

	// add parts to entity
	{
		VEntity::PartPtr pDataPart(new VDataPart(5));
		ent.AddPart(VFourCC("data"), pDataPart);

		pSetter = new VSettingPart();
		VEntity::PartPtr pSettingPart(pSetter);
		ent.AddPart(VFourCC("sett"), pSettingPart);

		pReader = new VReaderPart();
		VEntity::PartPtr pReadingPart(pReader);
		ent.AddPart(VFourCC("read"), pReadingPart);

		VEntity::PartPtr pTestPart(new VHierarchyPart("root"));
		ent.AddPart(VFourCC("hyra"), pTestPart);
	}

	VSharedPtr<VEntity> pChild(new VEntity());
	ent.AddChild(pChild);

	{
		// demonstrates how to get the 'parent' part (in VHierarchyPart.h)
		VEntity::PartPtr pChildPart(new VHierarchyPart("child"));
		pChild->AddPart(VFourCC("hyra"), pChildPart);
	}

	ent.Activate();

	pSetter->SetValue(101);
	pReader->PrintValue();

	pSetter->SetValue(53);
	pReader->PrintValue();

	ent.Deactivate();

	//---
	// test/demonstrate the resource manager
	using namespace resource;

	VResourceManagerPtr pResourceManager;

	pResourceManager->CreateResource("/dir0/dir1/dir2/dir3");
	pResourceManager->CreateResource("/dira/dirb/dirc/dird/");
	pResourceManager->CreateResource("/dir0/dir1/dir2a/dirc");

	VResourceId res = pResourceManager->GetResourceByName("/dir0/dir1");
	res->AddData(new int(5));
	//res->AddData(new VEntity());

	pResourceManager->DumpResourceInfo();

	VResourceDataPtr<const int> pResInt = res->GetData<int>();
	//VResourceDataPtr<const VEntity> pResEntity = res->GetData<VEntity>();

	V3D_ASSERT(*pResInt == 5);

	VSharedPtr<BlubType> pBlubType(new BlubType());
	pResourceManager->RegisterResourceType(pBlubType);

	VResourceDataPtr<const Blub> pBlub = res->GetData<Blub>();

	V3D_ASSERT(pBlub->GetVal() == 5);

	//pResourceManager->DumpResourceInfo();
	
	return 0;
}

//-----------------------------------------------------------------------------
namespace {
	VEntityDemoApp g_theApp;
}

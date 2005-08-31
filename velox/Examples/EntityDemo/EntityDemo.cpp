#include <V3d/Core.h>
#include <V3d/Entity/VEntityManager.h>

#include "VDataPart.h"
#include "VSetterPart.h"
#include "VReaderPart.h"
#include "VManagerPart.h"
#include "VInvalidPart.h"

#include <V3d/Resource.h>

#include <string>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::entity;
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

/* TODO: create resource example
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
*/

VSharedPtr<VEntity> CreateDemoEntity(vint in_nValue)
{
	typedef VSharedPtr<IVPart> PartPtr;

	VSharedPtr<VEntity> pEntity(new VEntity());

	pEntity->AddPart(VDataPart::GetDefaultId(), PartPtr(new VDataPart(in_nValue)));
	pEntity->AddPart(VReaderPart::GetDefaultId(), PartPtr(new VReaderPart()));
	//pEntity->AddPart(VSettingPart::GetDefaultId(), PartPtr(new VSettingPart()));

	return pEntity;
}

/**
 * This example demonstratetes sharing of data between multiple subsystems
 * The reader and setter communicate by using the data part without knowing
 * about each other. In a real application the setter and reader part will
 * need to add/remove themselves to/from their subsystems when (De)Activate
 * will be called. Apart from data sharing scene organisation is demonstrated:
 * the reader parts will register themselves to a manager part which can then
 * operate on the readers. Graphics, physics, .. systems will work like that by
 * providing manager parts in the root of the entity scene graph to which the
 * related objects will register automatically
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
	vout << "Demonstrating simple case" << vendl << vendl << vendl;

	VEntity root;
	VSharedPtr<VManagerPart> pManager(new VManagerPart());
	VSharedPtr<VSettingPart> pSettingPart(new VSettingPart());

	// we can add childs before the manager will be added and they will
	// still get correctly connected
	for(vint id = -3; id < 0; ++id)
	{
		root.AddChild(CreateDemoEntity(id));
	}

	root.AddPart(VManagerPart::GetDefaultId(), pManager);

	for(vint id = 1; id < 5; ++id)
	{
		root.AddChild(CreateDemoEntity(id));
	}

	// add a part whose value we will change
	{
		VSharedPtr<VEntity> pEntity = CreateDemoEntity(1000);
		root.AddChild(pEntity);
		pEntity->AddPart(VSettingPart::GetDefaultId(), pSettingPart);
	}

	// add an entity with an invalid part, which will not be activated
	{
		VSharedPtr<VEntity> pInvalid = CreateDemoEntity(-666);
		pInvalid->AddPart("invd", VEntity::PartPtr(new VInvalidPart()));
		root.AddChild(pInvalid);
	}

	// activate the whole scene and all entities
	root.Activate();

	vout << "\n\n\nScene is now active\n\n\n";

	// change value of the settable part
	pSettingPart->SetValue(9999);

	// deactivate the whole scene
    root.Deactivate();

	vout << "\n\n\nScene is now inactive\n\n\n";

	//VEntity ent;
	//VSettingPart* pSetter = 0;
	//VReaderPart* pReader = 0;

	//// add parts to entity
	//{
	//	VEntity::PartPtr pDataPart(new VDataPart(5));
	//	ent.AddPart(VFourCC("data"), pDataPart);

	//	pSetter = new VSettingPart();
	//	VEntity::PartPtr pSettingPart(pSetter);
	//	ent.AddPart(VFourCC("sett"), pSettingPart);

	//	pReader = new VReaderPart();
	//	VEntity::PartPtr pReadingPart(pReader);
	//	ent.AddPart(VFourCC("read"), pReadingPart);

	//	VEntity::PartPtr pTestPart(new VHierarchyPart("root"));
	//	ent.AddPart(VFourCC("hyra"), pTestPart);
	//}

	//VSharedPtr<VEntity> pChild(new VEntity());
	//ent.AddChild(pChild);

	//{
	//	// demonstrates how to get the 'parent' part (in VHierarchyPart.h)
	//	VEntity::PartPtr pChildPart(new VHierarchyPart("child"));
	//	pChild->AddPart(VFourCC("hyra"), pChildPart);
	//}

	//ent.Activate();

	//pSetter->SetValue(101);
	//pReader->PrintValue();

	//pSetter->SetValue(53);
	//pReader->PrintValue();

	//ent.Deactivate();

	/*
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
	*/

	return 0;
}

//-----------------------------------------------------------------------------
namespace {
	VEntityDemoApp g_theApp;
}

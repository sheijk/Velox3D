#include <V3d/Core.h>
#include <V3d/Entity/VEntityManager.h>

#include "VDataPart.h"
#include "VSetterPart.h"
#include "VReaderPart.h"

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d;
using namespace v3d::entity;
using v3d::utils::VFourCC;

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
	}

	ent.Activate();

	pSetter->SetValue(101);
	pReader->PrintValue();

	pSetter->SetValue(53);
	pReader->PrintValue();

	ent.Deactivate();
	
	return 0;
}

//-----------------------------------------------------------------------------
namespace {
	VEntityDemoApp g_theApp;
}

//TODO: add file creation date to file guard
#ifndef V3D_VPHYSICMANAGERPART_2005_08_31_H
#define V3D_VPHYSICMANAGERPART_2005_08_31_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Entity/VUnconnectedPart.h>
#include <V3dLib/Physics/VPhysicWorld.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace physics  {
//-----------------------------------------------------------------------------
using namespace v3d; 

/**
//TODO: insert documentation here
 */
class VPhysicManagerPart : public entity::VUnconnectedPart
{
public:
	VPhysicManagerPart();
	virtual ~VPhysicManagerPart();

	/** 
	* When called, the part has to register itself to it's subsystem 
	*/
	void Activate();

	/**
	* When called, the part has to unregister itself from it's subsystem
	*/
	void Deactivate();

	void Update();

	VPhysicWorld& GetPhysicWorld();

	static std::string GetDefaultId();

private:


	VPhysicWorld m_PhysicWorld;


};

//-----------------------------------------------------------------------------
}} // namespace v3d::physics
//-----------------------------------------------------------------------------
#endif // V3D_VPHYSICMANAGERPART_2005_08_31_H

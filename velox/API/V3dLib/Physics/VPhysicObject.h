#ifndef V3D_PHYSICOBJECT_05_11_04_H
#define V3D_PHYSICOBJECT_05_11_04_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <list>

//-----------------------------------------------------------------------------
namespace v3d {
namespace physics{
//-----------------------------------------------------------------------------
class VPhysicState;

class VPhysicObject
{
public:


	VPhysicObject();
	virtual ~VPhysicObject();

	void AddState(VPhysicState* in_State);
	void DeleteState(VPhysicState* in_State);

protected:

	virtual void Apply();

	std::list<VPhysicState*> m_StaticStateList;
	std::list<VPhysicState*> m_DynamicStateList;

};


//-----------------------------------------------------------------------------
} // namespace physics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_PHYSICOBJECT_05_11_04_H

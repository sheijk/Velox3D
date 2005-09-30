#ifndef V3D_VUPDATEABLEPART_H
#define V3D_VUPDATEABLEPART_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3dLib/Math.h>
#include <V3d/Entity/VPartBase.h>
#include <V3d/Entity.h>

#include <list>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
* A Update Interface for SceneGraph Animation
*
* @author lars
*/
class IVUpdateablePart : public VPartBase
{
public:

	IVUpdateablePart() {};
	virtual ~IVUpdateablePart() {};

	/** Update the Animation Part */
	virtual void Update(vfloat32 in_Seconds) = 0;

	static std::string GetDefaultId() { return "sgiu"; };
private:
};

/**
* add all IVUpdateablePart in a list and update the list 
*
* @author lars
*/
class VUpdateManagerPart : public VPartBase
{
public:

	VUpdateManagerPart();
	virtual ~VUpdateManagerPart();

	/** Update all the Animation Part */
	void Update(vfloat32 in_Seconds);

	/** 
	* When called, the part registers itself to it's parent and
	* activates its children
	*/
	virtual void Activate();

	/**
	* When called, the part unregisters itself from it's parent and
	* deactivates its children
	*/
	virtual void Deactivate();

	/** Register all IVUpdateableParts */
	void Register(IVUpdateablePart* in_pChild);

	/** Unregister all IVUpdateableParts */
	void Unregister(IVUpdateablePart* in_pChild);

	static std::string GetDefaultId();
private:
	std::list<IVUpdateablePart*> m_pChilds;
};
//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------

#endif // V3D_VUPDATEABLEPART_H
#ifndef V3D_VENTITY_2004_10_09_H
#define V3D_VENTITY_2004_10_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Entity/VEntityExceptions.h>
#include <V3d/Entity/IVPart.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>

#include <map>
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VEntityHelper;

/**
 * An entity is a container of entity parts. It owns it's parts once they are added.
 * Parts are told about each other when they are added.
 *
 * @author sheijk
 */
class VEntity
{
public:
	typedef VSharedPtr<VEntity> EntityPtr;
	typedef VSharedPtr<IVPart> PartPtr;

	VEntity();
	virtual ~VEntity();

	/** Will activate all parts */
    void Activate();

	/** Will deactivate all parts */
	void Deactivate();
	
	vbool IsActive() const;

	/** Adds a part to the entity. Entity will delete part */
	void AddPart(const utils::VFourCC& in_Id, PartPtr in_pPart);

	void AddChild(EntityPtr in_pEntity);
	void RemoveChild(EntityPtr in_pEntity);

	VRangeIterator<VEntity> ChildIterator();
	VRangeIterator<IVPart> PartIterator();

private:
	typedef std::map<utils::VFourCC, PartPtr> PartContainer;
	typedef std::vector<EntityPtr> EntityContainer;

	VEntity(const VEntity&);
	void operator=(const VEntity&);

	void ReconnectAllParts();
	void ConnectPart(PartPtr in_pPart, utils::VFourCC in_Id);

	PartContainer m_Parts;
	vbool m_bActivated;

	VEntity* m_pParent;
	EntityContainer m_Entities;

	// put util functions in helper class to keep changes local to VEntity.cpp
	friend class ::v3d::entity::VEntityHelper;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VENTITY_2004_10_09_H

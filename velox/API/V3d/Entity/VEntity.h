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
 * The entity system provides a way for independent subsystems which need to 
 * interact in some way to share data without knowing about each other. Thus 
 * coupling between subsystems is reduced which makes it easier to exchange 
 * them when needed and for intance replace parts of Velox's default systems 
 * by application specific ones. Another benefit is the construction of 
 * dynamically combined object in a game editor by artists etc.
 *
 * The entity manager operates on the level of game objects called 'entities'. 
 * An entity is a collection of one or more 'parts'. Parts contain data of 
 * their subsystems and may provide interfaces to access them. The parts of an 
 * entity are independent from each other but may also access each other 
 * through unique names.
 *
 * Interaction between subsystems which don't know about each other happens 
 * through jointly used parts. For example a position part might be written to 
 * by the physics system and be read by the graphics system for display.
 *
 * Use an entity directly, instead
 *
 * @see v3d::entity::IVPart
 *
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
	void AddPart(const std::string& in_Id, PartPtr in_pPart);

	/** Adds a part using it's  */
	void AddPart(VSharedPtr<IVPart> in_pPart);

	/** Removes the part with the given id */
	void RemovePart(const std::string& in_Id);

	void AddChild(EntityPtr in_pEntity);
	void RemoveChild(EntityPtr in_pEntity);

	VRangeIterator<VEntity> ChildIterator();
	VRangeIterator<IVPart> PartIterator();

	std::string GetName() const;
	void SetName(const std::string& in_strName);

	template<typename PartType>
	PartType* GetPart();
private:
	typedef std::map<std::string, PartPtr> PartContainer;
	typedef std::vector<EntityPtr> EntityContainer;

	VEntity(const VEntity&);
	void operator=(const VEntity&);

	IVPart* GetPartById(const std::string& in_Id);

	void UnconnectAllParts();
	void ReconnectAllParts();
	void ConnectPart(IVPart* in_pPart, const std::string& in_Id);
	void UnconnectPart(IVPart* in_pPart, const std::string& in_Id);

	/* deactivate if any dependency of a part is not fulfilled */
	void CheckDependencies();

	std::string m_strName;

	PartContainer m_Parts;
	vbool m_bActivated;

	VEntity* m_pParent;
	EntityContainer m_Entities;

	// put util functions in helper class to keep changes local to VEntity.cpp
	friend class ::v3d::entity::VEntityHelper;
};

//-----------------------------------------------------------------------------

template<typename PartType>
PartType* VEntity::GetPart()
{
	IVPart* part = GetPartById(GetTypeInfo<PartType>().GetName());
	if( part != 0 && part->IsOfType<PartType>() )
	{
		return part->Convert<PartType>();
	}
	else
	{
		return 0;
	}
}

//template<typename PartType>
//void VEntity::AddPart(VSharedPtr<PartType> in_pPart)
//{
//	// the part's class neeed a "static std::string GetDefaultId()" method
//	AddPart(
//	//AddPart(PartType::GetDefaultId(), in_pPart);
//}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VENTITY_2004_10_09_H

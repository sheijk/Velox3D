#ifndef V3D_VENTITYMANAGER_2004_10_09_H
#define V3D_VENTITYMANAGER_2004_10_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Core/VNamedObject.h>
#include <V3d/Entity/VEntity.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>
#include <V3d/Core/VObjectRegistry.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

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
 * @see v3d::entity::VEntity
 * @see v3d::entity::IVPart
 *
 * @author sheijk
 */
class VEntityManager : public VNamedObject
{
public:
	typedef VPointer<VEntity>::SharedPtr EntityPtr;

	VEntityManager();
	virtual ~VEntityManager();

    virtual void Add(EntityPtr in_pEntity);
	virtual void Remove(EntityPtr in_pEntity);

private:
	typedef std::vector<EntityPtr> EntityContainer;

	EntityContainer m_Entities;
};

typedef VEntityManager IVEntityManager;

typedef VServicePtr<IVEntityManager> VEntityManagerPtr;

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
template<>
inline v3d::entity::IVEntityManager* v3d::QueryService<v3d::entity::IVEntityManager>()
{
	return QueryObject<v3d::entity::IVEntityManager>("entity.manager");
}
//-----------------------------------------------------------------------------
#endif // V3D_VENTITYMANAGER_2004_10_09_H

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
 * @author sheijk
 */
V3D_DEPRECATED class VEntityManager : public VNamedObject
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

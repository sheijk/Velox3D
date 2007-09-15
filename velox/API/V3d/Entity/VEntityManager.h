/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VENTITYMANAGER_2004_10_09_H
#define V3D_VENTITYMANAGER_2004_10_09_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VNamedObject.h>
#include <V3d/Entity/VEntity.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>
#include <V3d/Core/VObjectRegistry.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d
{
namespace entity
{
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * @author sheijk
 */
#ifdef V3D_MSVC //no __attribute__((dep)) for class keyword in gcc
V3D_DEPRECATED class VEntityManager : public VNamedObject
#else
class VEntityManager : public VNamedObject
#endif
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
}
template<> inline entity::IVEntityManager* QueryService<entity::IVEntityManager>()
{
	return QueryObject<entity::IVEntityManager>("entity.manager");
}
} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VENTITYMANAGER_2004_10_09_H

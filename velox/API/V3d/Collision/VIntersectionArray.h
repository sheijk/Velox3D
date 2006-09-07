/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VINTERSECTIONARRAY_H
#define V3D_VINTERSECTIONARRAY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Math.h>
#include <V3d/Entity.h>

#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace collision {
//-----------------------------------------------------------------------------
using namespace v3d;

class VIntersectionArray
{
	typedef struct {
		entity::VEntity* pEntity;
		math::VVector3f Position;
		vuint Count;
	} Intersection;
public:

	VIntersectionArray(entity::VEntity* in_pEntity, math::VVector3f in_Position);
	virtual ~VIntersectionArray();

	entity::VEntity* GetEntity(vuint in_Count) const;
	
	math::VVector3f GetPosition(vuint in_Count) const;
	
	template<class T>
	T GetPart(T& t, vuint in_Count) const;

	vuint GetCount() const;

private:

	std::list<Intersection*> m_pArray;
	vuint                      m_iCount;
};

//-----------------------------------------------------------------------------
} // namespace collision
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VINTERSECTIONARRAY_H

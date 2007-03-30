/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Collision/VIntersectionArray.h>
//-----------------------------------------------------------------------------
#include <V3d/Core.h>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace collision {
//-----------------------------------------------------------------------------

VIntersectionArray::VIntersectionArray(entity::VEntity* in_pEntity, 
									   math::VVector3f in_Position)
{
	Intersection* pIntersection = 0;
	pIntersection->pEntity = in_pEntity;
	pIntersection->Position = in_Position;
	for(m_iCount = 0; m_iCount < m_pArray.size(); ++m_iCount) 
	{
		pIntersection->Count = m_iCount;
	}

	m_pArray.push_back(pIntersection);
}

VIntersectionArray::~VIntersectionArray()
{
	m_pArray.clear();
}

entity::VEntity* VIntersectionArray::GetEntity(vuint in_Count) const
{
	for(std::list<Intersection*>::const_iterator iter = m_pArray.begin(); 
		iter != m_pArray.end(); 
		++iter)
	{
		if((*iter)->Count == in_Count)
			return (*iter)->pEntity;
	}

	// programming error.. why doesn't this path return anything? --sheijk
	V3D_ASSERT(false);
}

math::VVector3f VIntersectionArray::GetPosition(vuint in_Count) const
{
	for(std::list<Intersection*>::const_iterator iter = m_pArray.begin(); 
		iter != m_pArray.end(); 
		++iter)
	{
		if((*iter)->Count == in_Count)
			return (*iter)->Position;
	}

	// programming error.. why doesn't this path return anything? --sheijk
	V3D_ASSERT(false);
}

template <class T>
T VIntersectionArray::GetPart(T& t, vuint in_Count) const
{
	for(std::list<Intersection*>::const_iterator iter = m_pArray.begin(); 
		iter != m_pArray.end(); 
		++iter)
	{
		if((*iter)->Count == in_Count)
			return (*iter)->pEntity;
	}	
}

vuint VIntersectionArray::GetCount() const
{
	return m_iCount;
}

//-----------------------------------------------------------------------------
} // namespace collision
} // namespace v3d
//-----------------------------------------------------------------------------

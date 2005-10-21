#include "V3dLib/Collision/VIntersectionArray.h"
//-----------------------------------------------------------------------------
#include <V3d/Core.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace collision {
//-----------------------------------------------------------------------------

VIntersectionArray::VIntersectionArray(entity::VEntity* in_pEntity, 
									   VVector3f in_Position)
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
}

VVector3f VIntersectionArray::GetPosition(vuint in_Count) const
{
	for(std::list<Intersection*>::const_iterator iter = m_pArray.begin(); 
		iter != m_pArray.end(); 
		++iter)
	{
		if((*iter)->Count == in_Count)
			return (*iter)->Position;
	}
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
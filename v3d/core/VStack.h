/*
 * Velox3D
 *
 *
 * VStack.h
 *
 * History:		taken from old p3d code from "schlumpf" ;)
 *
 * 
 *
 */

#ifndef V3D_VSTACK_H
#define V3D_VSTACK_H

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Core/VArray.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 *	The Stack class represents a last-in-first-out (LIFO) stack of objects. It extends class 
 *	Array with four operations that allow a vector to be treated as a stack. The usual push 
 *	and pop operations are provided, as well as a method to peek at the top item on the stack 
 *	and a method to search the stack for an item and discover how far it is from the top. 
 *
 *	@version	1.0	08/24/01
 *	@author		Reinhold Früsmer
 */
//##ModelId=3B92B03B0340
template<class TType>
class VStack : public VArray<TType>
{
public:
	
	/**
	 *	Returns the object at the top of this stack without removing it from the stack.
	 */
	//##ModelId=3B92B03B034B
	inline TType Peek()
	{
		return m_pData[m_iNumElements - 1];
	}

	/**
	 *	Removes the object at the top of this stack and returns that object as the value 
	 *	of this function.
	 */
	//##ModelId=3B92B03B034C
	inline TType Pop()
	{
		m_iNumElements--;
		return m_pData[m_iNumElements];
	}

	/**
	 *	Pushes the specified item onto the top of this stack.
	 */
	//##ModelId=3B92B03B034D
	inline void Push(TType tElement)
	{
		Add(tElement);
	}

	/**
	 *	Returns the 1-based position where an object is on this stack. If the element occurs 
	 *	as an item in this stack, this method returns the distance from the top of the stack 
	 *	of the occurrence nearest the top of the stack; the topmost item on the stack is 
	 *	considered to be at distance 1. 
	 */
	//##ModelId=3B92B03B034F
	inline int Search(TType tElement)
	{
		int iLastIndex = GetLastIndexOf(tElement);
		
		return m_iNumElements - iLastIndex;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TSTACK_H

/*
 * Velox3D
 *
 *
 * VArray.h
 *
 * History:		taken from old p3d code from "schlumpf" ;)
 *
 * 
 *
 */

#ifndef V3D_VARRAY_H
#define V3D_VARRAY_H

#include <Core/VCoreLib.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 *	The VArray template class implements a growable array of objects. Like an array, it
 *	contains components that can be accessed using an integer iIndex. However, the size of 
 *	a Array can grow or shrink as needed to accommodate adding and removing items after 
 *	the Array has been created.
 *
 *  @author		Reinhold Früsmer
 *	@version	1.0	08/24/01
 */
//##ModelId=3B92B03C00FA
template<class TType>
class VArray
{
public:

	/**
	 *	Constructs an empty array.
	 */
	//##ModelId=3B92B03C00FC
	VArray()
	{
		m_pData			= 0;
		m_iNumElements	= 0;
		m_iMaxElements	= 0;
	}

	/**
	 *	Constructs an empty array with the specified initial capacity.
	 *
	 *	@param iSize The initial capacity of the array.
	 */
	//##ModelId=3B92B03C0104
	VArray(vint iSize)
	{
		// check param
		P3DASSERT(iSize >= 0);

		m_pData			= new TType[iSize];
		m_iNumElements	= 0;
		m_iMaxElements	= iSize;
	}

	/**
	 *	Destructor.
	 */
	//##ModelId=3B92B03C0106
	~VArray()
	{
		if (m_pData)
			delete [] m_pData;
	}

	/**
	 *	Inserts the specified element at the end of this array.
	 *	
	 *	@param tElement Element to be appended to this array.
	 */
	//##ModelId=3B92B03C0107
	void Add(TType tElement)
	{
		// Adjust size if necessary.
		if (m_iNumElements >= m_iMaxElements)
			SetSize((m_iNumElements + 1) * 2);
		
		// Copy the element.
		m_pData[m_iNumElements] = tElement;
		m_iNumElements++;
	}

	/**
	 *	Inserts the specified element at the specified position in this array. If the iIndex
	 *
	 *	@param iIndex	iIndexat which the specified element is to be inserted. This method
	 *					does not append an element if the given iIndex equals the element count.
	 *	@param element Element to be inserted.
	 */
	//##ModelId=3B92B03C0109
	void InsertAt(vint iIndex, TType tElement)
	{
		// check params
		V3DASSERT((iIndex >= 0) && (iIndex < m_iNumElements));

		// Adjust size if necessary.
		if (m_iNumElements >= m_iMaxElements)
		{
			SetSize((m_iNumElements + 1) * 2);
		}

		// Provide some room for the new element.
		memcpy(&m_pData[iIndex + 1], &m_pData[iIndex], (m_iNumElements - iIndex) * sizeof(TType));

		// Copy the element.
		m_pData[iIndex] = tElement;
		m_iNumElements++;
	}

	/**
	 *	Appends all of the elements in the specified array to the end of this array. 
	 *
	 *	@param pArray The array to be appended.
	 */
	//##ModelId=3B92B03C010C
	void Add(const VArray<TType>* pArray)
	{
		// Adjust size if necessary.
		if ((m_iNumElements + pArray->GetSize()) >= m_iMaxElements)
			SetSize(m_iNumElements + pArray->GetSize());

		// Copy the elements.
		memcpy(&m_pData[m_iNumElements], pArray->m_pData, pArray->GetSize() * sizeof(TType));
		m_iNumElements += pArray->GetSize();
	}
	
	/**
	 *	Inserts all of the elements in the specified array into this array, starting at 
	 *	the specified position.
	 *
	 *	@param iIndex	iIndexat which to insert the first element from the specified array.
	 *	@param pArray	The array to be inserted.
	 */
	//##ModelId=3B92B03C010E
	void InsertAt(vint iIndex, const VArray<TType>* pArray)
	{
		// check params
		P3DASSERT(pArray != NULL);
		P3DASSERT((iIndex >= 0) && (iIndex < m_iNumElements));

		// Adjust size if necessary.
		if ((m_iNumElements + pArray->GetSize()) >= m_iMaxElements)
			SetSize(m_iNumElements + pArray->GetSize() * 2);

		// Provide some room for the new elements.
		if (m_iNumElements - iIndex > 0)
			memcpy(&m_pData[iIndex + pArray->GetSize()], &m_pData[iIndex],
            pArray->GetSize() * sizeof(TType));

		// Copy the elements.
		memcpy(&m_pData[iIndex], pArray->m_pData, pArray->GetSize() * sizeof(TType));
		m_iNumElements += pArray->GetSize();
	}

	/**
	 *	Removes all of the elements from this array.
	 */
	//##ModelId=3B92B03C0111
	void RemoveAll()
	{
		if (m_pData)
		{
			delete [] m_pData;
			m_pData = 0;
			m_iNumElements = 0;
			m_iMaxElements = 0;
		}
	}	

	/**
	 *	Increases the capacity of this array instance, if necessary, to ensure that it
	 *	hold at least the number of elements specified by the minimum capacity argument.
	 *
	 *	@param iSize The desired minimum capacity.
	 */
	//##ModelId=3B92B03C0112
	void SetSize(vint iSize)
	{
		if (iSize > m_iMaxElements)
		{
			// Create a new buffer with the same content.
			TType* pNewBuffer = new TType[iSize];
			memcpy(pNewBuffer, m_pData, m_iNumElements * sizeof(TType));
			
			// Release the old buffer.
			if (m_pData)
				delete [] m_pData;

			m_pData			= pNewBuffer;
			m_iMaxElements	= iSize;
		}
		else if (iSize < m_iMaxElements)
		{
			Trim();
		}
	}

	/**
	 *	Returns the number of elements in this list.
	 */
	//##ModelId=3B92B03C0114
	inline vint GetSize() const
	{
		return m_iNumElements;
	}

	/**
	 *	Returns the element at the specified position in this array.
	 *
	 *	@param iIndex The iIndex of the element to return.
	 *
	 *	@return	The element at the specified position in this array.
	 */
	//##ModelId=3B92B03C0116
	inline TType GetAt(vint iIndex)
	{
		P3DASSERT((iIndex >= 0) && (iIndex < m_iNumElements));

		return m_pData[iIndex];
	}

	/**
	 *	Searches for the first occurence of the given argument.
	 *
	 *	@param tElement		An object.
	 *	@param iStartPos	Optional: Zero-based iIndex specifying the positon to start the lookup.
	 *
	 *	@return The index of the first occurrence of the argument in this list;
	 *			returns -1 if the object was not found.
	 */
	//##ModelId=3B92B03C0118
	vint GetIndexOf(TType tElement, vint iStartPos = 0)
	{
		for (vint iCnt = iStartPos; iCnt < m_iNumElements; iCnt++)
		{
			if (tElement == m_pData[iCnt])
				return iCnt;
		}

		return -1;
	}

	/**
	 *	Returns true if this array contains the specified element.
	 */
	//##ModelId=3B92B03C011B
	bool Contains(TType tElement)
	{
		return (GetIndexOf(tElement) != -1);
	}

	/**
	 *	Tests if this array has no elements.
	 *
	 *	@return true if this list has no elements, otherwise false.
	 */
	//##ModelId=3B92B03C011D
	inline bool IsEmpty()
	{
		return (m_iNumElements == 0);
	}

	/**
	 *	Returns the iIndex of the last occurrence of the specified object in this array.
	 *
	 *	@param tElement		The desired element.
	 *	@param iStartPos	Optional: Zero-based iIndex specifying the positon to start the lookup.
	 *
	 *	@return The iIndex of the last occurrence of the specified object in this list; 
	 *			returns -1 if the object is not found.
	 */
	//##ModelId=3B92B03C011E
	vint GetLastIndexOf(TType tElement, vint iStartPos = -1)
	{
		if (iStartPos = -1)
			iStartPos = m_iNumElements - 1;

		for (vint iCnt = iStartPos; iCnt >= 0; --iCnt)
		{
			if (tElement == m_pData[iCnt])
				return iCnt;
		}

		return -1;
	}

	/**
	 *	Removes the element at the specified position in this array.
	 *
	 *	@param	iIndex The iIndex of the element to be removed.
	 */ 
	//##ModelId=3B92B03C0121
	void RemoveAt(vint iIndex, vint iCount = 1)
	{
		P3DASSERT((iIndex >= 0) && (iIndex + iCount <= m_iNumElements));

		memcpy(&m_pData[iIndex], &m_pData[iIndex + iCount], 
			(m_iNumElements - iIndex - iCount) * sizeof(TType));
		m_iNumElements = m_iNumElements - iCount;
	}

	/**
	 *	Replaces the element at the specified position in this array with the 
	 *	specified element.
	 *
	 *	@param iIndex  Index of the element to replace.
	 *	@param tElement Element to be stored at the specified position.
	 */
	//##ModelId=3B92B03C0124
	inline void SetAt(vint iIndex, TType tElement)
	{
		P3DASSERT((iIndex >= 0) && (iIndex < m_iNumElements));
		
		m_pData[iIndex] = tElement;
	}

	/**
	 *	Returns an array containing all of the elements in this array, allowing for 
	 *	direct access to the elements in this Array.
	 *
	 *	@return An array containing all of the elements in this Array.
	 */
	//##ModelId=3B92B03C0127
	inline TType* GetElements()
	{
		return m_pData;
	}

	/**
	 *	Trims the capacity of this array instance to be the array's current size.
	 */
	//##ModelId=3B92B03C0128
	void Trim()
	{
		if (m_iNumElements < m_iMaxElements)
		{
			// Create a new buffer with the same content.
			TType* pNewBuffer = new TType[m_iNumElements];
			memcpy(pNewBuffer, m_pData, m_iNumElements * sizeof(TType));
			
			// Release the old buffer.
			if (m_pData)
				delete [] m_pData;

			m_pData			= pNewBuffer;
			m_iMaxElements	= m_iNumElements;
		}
	}

protected:
	/** The actual elements of this array. */
	//##ModelId=3B92B03C0129
	TType* m_pData;

	/** Current number of elements. */
	//##ModelId=3B92B03C012A
	vint m_iNumElements;

	/** Allocated size. */
	//##ModelId=3B92B03C012B
	vint m_iMaxElements;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

#endif
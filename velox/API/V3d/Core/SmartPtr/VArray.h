//TODO: correct file guard
#ifndef V3D_VARRAY_H
#define V3D_VARRAY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>

#include <algorithm>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

template<typename T>
class VArray
{
	typename VArrayPtr<T>::AutoPtr m_pData;
	size_t m_nSize;
	
public:
	// stl container conventions
	typedef T* iterator;
	typedef const T* const_iterator;
	
	VArray()
	{
		m_nSize = 0;
	}

	size_t GetSize() const
	{
		return m_nSize;
	}

	/** resize, copy old elements, new elements = in_Default */
	void Resize(size_t in_nNewSize, const T& in_Default = T())
	{
		typename VArrayPtr<T>::AutoPtr pNew;
		size_t i;

		pNew = new T[in_nNewSize];

		// copy old values
		for(i = 0; i < std::min(in_nNewSize, m_nSize); ++i)
		{
			pNew[i] = m_pData[i];
		}

		// set new elements to default value
		for( ; i < in_nNewSize; ++i)
		{
			pNew[i] = in_Default;
		}

		m_pData = pNew;
		m_nSize = in_nNewSize;
	}

	/** resize to 0 */
	void Clear()
	{
		m_pData.Release();
		m_nSize = 0;
	}

	/** get address of first element */
	T* GetAddress(int in_nIndex = 0)
	{
		return (m_pData.Get() + in_nIndex);
	}

	/** get address of first element, const version */
	//const T* GetAddress() const
	//{
	//	return m_pData.Get();
	//}

	T& operator[](int in_nIndex)
	{
		return m_pData[in_nIndex];
	}

	const T& operator[](int in_nIndex) const
	{
		return m_pData[in_nIndex];
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_/*filename*/_H

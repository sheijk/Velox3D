/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VAUTOPTR_2006_04_19_H
#define V3D_VAUTOPTR_2006_04_19_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

template<typename T>
class VAutoPtr;

// workaround: class Foo<T1> can't access private members of Foo<T2>
class VAutoPtrBase
{
protected:
	template<typename T>
	void ChangePtr(VAutoPtr<T>& autoptr, T* newptr);
};

template<typename T>
class VAutoPtr : private VAutoPtrBase
{
public:
	VAutoPtr() { m_pObject = 0; }
	explicit VAutoPtr(T* in_pObject) { m_pObject = in_pObject; }

	template<typename T2>
	VAutoPtr(VAutoPtr<T2>& in_Other)
	{
		T2* otherType = 0;
		T* thisType = otherType;

		m_pObject = in_Other.Get();
		ChangePtr(in_Other, (T2*)0);
	}

	void operator=(VAutoPtr& in_Other)
	{
		m_pObject = in_Other.m_pObject;
		in_Other.m_pObject = 0;
	}

	~VAutoPtr()
	{
		if( m_pObject != 0 )
		{
			delete m_pObject;
			m_pObject = 0;
		}
	}

	T* Get() const { return m_pObject; }
	T* operator->() const { return m_pObject; }
	T& operator*() const { return m_pObject; }

	T* DropOwnership()
	{
		T* t = m_pObject;
		m_pObject = NULL;
		return t;
	}

private:
	friend class VAutoPtrBase;

	T* m_pObject;
};

template<typename T>
VAutoPtr<T> AutoPtr(T* in_pObject)
{
	return VAutoPtr<T>(in_pObject);
}

template<typename T>
vbool operator==(const VAutoPtr<T>& l, const VAutoPtr<T>& r)
{
	return l.Get() == r.Get();
}

template<typename T>
vbool operator!=(const VAutoPtr<T>& l, const VAutoPtr<T>& r)
{
	return l.Get() != r.Get();
}

template<typename T>
vbool operator==(const VAutoPtr<T>& l, const T* r)
{
	return l.Get() == r;
}

template<typename T>
vbool operator==(const T* l, const VAutoPtr<T>& r)
{
	return l == r.Get();
}

template<typename T>
vbool operator!=(const VAutoPtr<T>& l, const T* r)
{
	return l.Get() != r;
}

template<typename T>
vbool operator!=(const T* l, const VAutoPtr<T>& r)
{
	return l != r.Get();
}

template<typename T>
void VAutoPtrBase::ChangePtr(VAutoPtr<T>& autoptr, T* newptr)
{
	autoptr.m_pObject = newptr;
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VAUTOPTR_2006_04_19_H


/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSHAREDPTR_2004_10_16_H
#define V3D_VSHAREDPTR_2004_10_16_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <boost/smart_ptr.hpp>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * A reference counting smart pointer class. Counts the references to an object
 * an deletes it as soon as no shared pointer references the object anymore
 * Use this class directly as a replacement for VPointer<T>::SharedPtr
 *
 * @author sheijk
 */
template<typename T>
class VSharedPtr
{
	friend class VSharedPtrFriend;

	boost::shared_ptr<T> m_BoostPtr;

public:
	// some typedefs provided by all velox smart pointers
	typedef T* Pointer;
	typedef T Value;
	typedef T& Reference;

	/** 
	 * Releases the subject. If no other pointers refer to it it will be 
	 * deleted immediately. If more shared pointers reference it, it's 
	 * reference count will be decreased. The shared pointer points to 0
	 * after calling Release()
	 */
	void Release();

	/**
	 * Assigns an object to the shared pointer. If another object was 
	 * referenced before, it will be released. Note that the object assigned
	 * will be deleted automatically by the shared pointer. Thus do not delete
	 * it manually after assigning it to a shared pointer
	 */
	void Assign(T* in_pSubject);

	/**
	 * Drops the owner ship of the subject. The smart pointer will be set to
	 * zero. The user has to delete the subject manually after using
	 * DropOwnership. The function may only be called when exactly one shared
	 * pointer refers to the subject. Only use it when you know exactly what
	 * you are doing - this function is an evil hack(tm)
	 */
	//T* DropOwnership();

	/**
	 * Returns a pure c pointer-to-const-object to the object referenced
	 */
	T* Get() const;

	/**
	 * Assigns itself to the same subject like in_Other. Derived must be derived
	 * from T. Will increase the subjects reference count by one. Any old
	 * previously referenced subject will be released
	 */
	template<typename Derived>
	void Clone(const VSharedPtr<Derived>& in_Other);

	VSharedPtr();

	/** see Clone */
	template<typename Derived>
	VSharedPtr(const VSharedPtr<Derived>& in_Other);

	/** see Clone */
	VSharedPtr(const VSharedPtr& in_Other);

	/** see Assign */
	explicit VSharedPtr(T* in_pSubject);

	/** Will release a subject if assigned */
	~VSharedPtr();

	/** see Clone */
	template<typename Derived>
	void operator=(const VSharedPtr<Derived>& in_Other);

	/** see Clone */
	void operator=(const VSharedPtr& in_Other);

	T& operator*() const;
	T* operator->() const;
};

class VSharedPtrFriend
{
	VSharedPtrFriend(int) {}

public:
	template<typename T>
	static const boost::shared_ptr<T>& GetInternalPtr(const VSharedPtr<T>& ptr)
	{
		return ptr.m_BoostPtr;
	}

	template<typename T>
	static boost::shared_ptr<T>& GetInternalPtr(VSharedPtr<T>& ptr)
	{
		return ptr.m_BoostPtr;
	}
};

template<typename T, typename T2>
vbool operator==(const VSharedPtr<T>& left, const VSharedPtr<T2>& right);

template<typename T, typename T2>
vbool operator!=(const VSharedPtr<T>& left, const VSharedPtr<T2>& right);

//-----------------------------------------------------------------------------
#include "VSharedPtr.inl"
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSHAREDPTR_2004_10_16_H


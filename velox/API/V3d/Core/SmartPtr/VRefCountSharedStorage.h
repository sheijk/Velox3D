#ifndef V3D_VREFCOUNTSHAREDSTORAGE_H
#define V3D_VREFCOUNTSHAREDSTORAGE_H
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * Helper Class for VRefCountPol
 * keeps track of the number of references to a pointer, and will automatically
 * delete it and itself if no more references are needed
 */
template<class StoragePolicy>
class VRefCountSharedStorage
{
public:
	typedef VRefCountSharedStorage<StoragePolicy> MyType;

private:
	mutable int m_nRefCount;
	StoragePolicy m_Storage;

	/** object may only be constructed via CreateNew */
	VRefCountSharedStorage();

	/** no copy constructor */
	VRefCountSharedStorage(const MyType&);
	/** no assignment operator */
	void operator=(const MyType&);

	/** deleting prohibited. object deletes itself through Release() */
	~VRefCountSharedStorage();

public:
	/** create a new shared storage which points to in_Subject */
	static MyType* CreateNew(typename StoragePolicy::TargetType in_Subject)
	{
		VRefCountSharedStorage<StoragePolicy>* pInstance 
			= new VRefCountSharedStorage<StoragePolicy>();

		// assign subject
		pInstance->m_Storage.Set(in_Subject);
		pInstance->m_nRefCount = 1;

		return pInstance;
	}

	/** decrease ref count by one. self delets on zero */
	virtual void Release();

	/** inreases ref count by one */
	void AddRef();

	/** returns the subject */
	typename StoragePolicy::TargetType Get() const
	{
		return m_Storage.Get();
	}
};

//-----------------------------------------------------------------------------
#include "VRefCountSharedStorage.inl"

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VREFCOUNTSHAREDSTORAGE_H

#ifndef V3D_VSMARTPTR_H
#define V3D_VSMARTPTR_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

	/**
	 * Class for smart pointers.
	 * Dervives most of it's interface from BehaviorPol
	 */
	template<
		typename T, 
		typename BehaviorPol
	> 
	class VSmartPtrBase : public BehaviorPol
	{
	private:
		typedef VSmartPtrBase<T, BehaviorPol> MyType;

	public:
		//typedef T* PointerType;
		typedef typename BehaviorPol::PointerType PointerType;
		typedef typename BehaviorPol::RefType RefType;
		typedef typename BehaviorPol::ValueType ValueType;

		VSmartPtrBase()
		{
		}

		// access functions/operators
		~VSmartPtrBase()
		{
			Release();
		}

		PointerType operator->() const
		{
			return Get();
		}

		RefType operator*() const
		{
			return *Get();
		}

	};

	template<
		typename T,
		typename BehaviorPol
	>
	class VSmartPtr : public VSmartPtrBase<T, BehaviorPol>
	{
		typedef VSmartPtr<T, BehaviorPol> SmartPointerType;

	public:
		VSmartPtr() {};

		VSmartPtr(const SmartPointerType& in_Other)
		{
			Clone(in_Other);
		}

		VSmartPtr(PointerType in_pVal)
		{
			Assign(in_pVal);
		}

		void operator=(PointerType in_pNewTarget)
		{
			Assign(in_pNewTarget);
		}

		void operator=(const SmartPointerType& in_Other)
		{
			Clone(in_Other);
		}
	};

	template<
		typename T,
		typename BehaviorPol
	>
	class VSmartPtrMutable : public VSmartPtrBase<T, BehaviorPol>
	{
		typedef VSmartPtrMutable<T, BehaviorPol> SmartPointerType;

	public:
		VSmartPtrMutable() {};

		VSmartPtrMutable(SmartPointerType& in_Other)
		{
			Clone(in_Other);
		}

		VSmartPtrMutable(PointerType in_pVal)
		{
			Assign(in_pVal);
		}

		void operator=(PointerType in_pVal)
		{
			Assign(in_pVal);
		}

		void operator=(SmartPointerType& in_Other)
		{
			Clone(in_Other);
		}
	};

	// operators for smart pointers

	// operator!=
	template<
		typename T,
		typename BehaviorPol
	>
	vbool operator!=(
	const T* pT, 
	const VSmartPtrBase<T, BehaviorPol>& pSP)
	{
		return pT != pSP.Get();
	}

	template<
		typename T,
		typename BehaviorPol
	>
	vbool operator!=(
		const VSmartPtrBase<T, BehaviorPol>& pSP,
		const T* pT)
	{
		return pT != pSP.Get();
	}

	template<
		typename T,
		typename BehaviorPol
	>
	vbool operator!=(
		const VSmartPtrBase<T, BehaviorPol>& pSP1,
		const VSmartPtrBase<T, BehaviorPol>& pSP2)
	{
		return pSP1.Get() != pSP2.Get();
	}

	// operator==

	template<
		typename T,
		typename BehaviorPol
	>
	vbool operator==(
		const VSmartPtrBase<T, BehaviorPol>& pSP,
		const T* pT)
	{
		return pT == pSP.Get();
	}

	template<
		typename T,
		typename BehaviorPol
	>
	vbool operator==(
		const T* pT, 
		const VSmartPtrBase<T, BehaviorPol>& pSP)
	{
		return pT == pSP.Get();
	}

	template<
		typename T,
		typename BehaviorPol
	>
	vbool operator==(
	const VSmartPtrBase<T, BehaviorPol>& pSP1,
	const VSmartPtrBase<T, BehaviorPol>& pSP2)
	{
		return pSP1.Get() == pSP2.Get();
	}
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSMARTPTR_H

#ifndef V3D_VSMARTPTR_H
#define V3D_VSMARTPTR_H
//-----------------------------------------------------------------------------
//#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
	typedef bool vbool; //TODO: remove

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
		typedef typename BehaviorPol::Pointer Pointer;
		typedef typename BehaviorPol::Reference Reference;
		typedef typename BehaviorPol::Value Value;

		VSmartPtrBase()
		{
		}

		// access functions/operators
		~VSmartPtrBase()
		{
			Release();
		}

		Pointer operator->() const
		{
			return Get();
		}

		Reference operator*() const
		{
			return *Get();
		}
		
		operator Pointer()
		{
			return Get();
		}

		operator const Pointer() const
		{
			return Get();
		}

		// make release, get and assign accessible
		using BehaviorPol::Release;
		using BehaviorPol::Get;
		using BehaviorPol::Assign;
		using BehaviorPol::IsEqual;
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

		explicit VSmartPtr(Pointer in_pVal)
		{
			Assign(in_pVal);
		}

		//void operator=(Pointer in_pNewTarget)
		//{
		//	Assign(in_pNewTarget);
		//}

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

		explicit VSmartPtrMutable(Pointer in_pVal)
		{
			Assign(in_pVal);
		}

		//void operator=(Pointer in_pVal)
		//{
		//	Assign(in_pVal);
		//}

		void operator=(SmartPointerType& in_Other)
		{
			Clone(in_Other);
		}
	};

	// operators for smart pointers

	// operator!=
	//template<
	//	typename T,
	//	typename BehaviorPol
	//>
	//vbool operator!=(
	//	const T* pT, 
	//	const VSmartPtrBase<T, BehaviorPol>& pSP)
	//{
	//	return pT != pSP.Get();
	//}

	//template<
	//	typename T,
	//	typename BehaviorPol
	//>
	//vbool operator!=(
	//	const VSmartPtrBase<T, BehaviorPol>& pSP,
	//	const T* pT)
	//{
	//	return pT != pSP.Get();
	//}

	//template<
	//	typename T,
	//	typename BehaviorPol
	//>
	//vbool operator!=(
	//	const VSmartPtrBase<T, BehaviorPol>& pSP1,
	//	const VSmartPtrBase<T, BehaviorPol>& pSP2)
	//{
	//	return ! pSP1.IsEqual(pSP2);
	//}

	//// operator==

	//template<
	//	typename T,
	//	typename BehaviorPol
	//>
	//vbool operator==(
	//	const VSmartPtrBase<T, BehaviorPol>& pSP,
	//	const T* pT)
	//{
	//	return pT == pSP.Get();
	//}

	//template<
	//	typename T,
	//	typename BehaviorPol
	//>
	//vbool operator==(
	//	const T* pT, 
	//	const VSmartPtrBase<T, BehaviorPol>& pSP)
	//{
	//	return pT == pSP.Get();
	//}

	//template<
	//	typename T,
	//	typename BehaviorPol
	//>
	//vbool operator==(
	//const VSmartPtrBase<T, BehaviorPol>& pSP1,
	//const VSmartPtrBase<T, BehaviorPol>& pSP2)
	//{
	//	return pSP1.IsEqual(pSP2);
	//}
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSMARTPTR_H

#ifndef V3D_VITERATORBASES_H
#define V3D_VITERATORBASES_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/IVIteratorPol.h>

#include <memory>

//-----------------------------------------------------------------------------
namespace v3d {
namespace iterutil {
//-----------------------------------------------------------------------------

/**
 * shortcut for inserting the standard iterator typedefs in 
 * every class
 */
#define V3D_ITERTYPEDEFS \
	typedef T Value; typedef T* Pointer; typedef T& Reference;\
	typedef const T ConstValue; typedef const T* ConstPointer;\
	typedef const T& ConstReference;\
	typedef typename Parent::DifferenceType DifferenceType;

	//-----------------------------------------------------------------------------
	// iterator utility classes

	template<typename T, typename SmartPointer>
	class VIteratorBase
	{
		typedef IVIteratorPol<T> IterImplType;

		/** a pointer to the iterator implementation class */
		SmartPointer m_pIterImpl;
	protected:
		typedef IterImplType* IterPointer;

		/** assigns a new iterator implementation */
		void Assign(IterPointer pIterImpl)
		{
			m_pIterImpl = pIterImpl;
		}

		/** returns the object the iterator points to */
		T* GetTarget() const
		{
			return m_pIterImpl->Get();
		}

		/** returns a pointer to the iterator */
		IterImplType* GetIter() const
		{
			return &(*m_pIterImpl);
		}

		VIteratorBase()
		{
		}

		VIteratorBase(const VIteratorBase& o) : 
			m_pIterImpl(o.GetIter()->CreateCopy())
		{
		}

		VIteratorBase& operator=(const VIteratorBase& o)
		{
			m_pIterImpl = o.GetIter()->CreateCopy();

			return *this;
		}

	public:
		typedef T Value;
		typedef T* Pointer;
		typedef T& Reference;

		typedef const T ConstValue;
		typedef const T* ConstPointer;
		typedef const T& ConstReference;

		typedef vint DifferenceType;
	};

	/**
	* some default types for iterators
	*/
	template<typename T>
	struct VIteratorDefault
	{
		//TODO: AutoPtr verwenden
		//TODO: als Default fuer SmartPtr nehmen
		typedef IVIteratorPol<T>* SmartPtr;
	};

	/**
	* Provides compare operators
	*/
	template<typename T, typename Parent>
	struct VEqCompIterInterface : public Parent
	{
		bool operator==(const VEqCompIterInterface& o) const
		{
			return GetIter()->IsEqual(*(o.GetIter()));
		}

		bool operator!=(const VEqCompIterInterface& o) const
		{
			return ! operator==(o);
		}
	};

	/**
	* provides read only access ( x = *it geht, aber nicht *it = x )
	*/
	template<typename T, typename Parent>
	struct VReadOnlyIterInterface : public Parent
	{
		V3D_ITERTYPEDEFS;

		ConstReference operator*() const
		{
			return *GetTarget();
		}

		Pointer operator->() const
		{
			return GetTarget();
		}
	};

	/**
	* provides write only access ( *it = x geht, aber nicht x = *it )
	*/
	template<typename T, typename Parent>
	struct VWriteOnlyIterInterface : public Parent
	{
		V3D_ITERTYPEDEFS;

		const VWriteOnlyIterInterface& operator*() const 
		{ 
			return *this; 
		}
		
		void operator=(const T& val) const 
		{ 
			*GetTarget() = val; 
		}
	};

	/**
	* provides access to non const value
	*/
	template<typename T, typename Parent>
	struct VMutableIterInterface : public Parent
	{
		V3D_ITERTYPEDEFS;

		Reference operator*() const
		{
			return *GetTarget();
		}

		Pointer operator->() const
		{
			return GetTarget();
		}
	};

	/**
	* proceed to successor
	*/
	template<typename T, typename RetType, typename Parent>
	struct VProceedIterInterface : public Parent
	{
		V3D_ITERTYPEDEFS;

		RetType& operator++()
		{
			GetIter()->Proceed();

			return (RetType&)*this;
		}

		RetType operator++(int)
		{
			// create a new iter with a copy of the iter impl
			RetType old(GetIter()->CreateCopy());

			GetIter()->Proceed();

			return old;
		}
	};

	/**
	* back to predecessor
	*/
	template<typename T, typename RetType, typename Parent>
	struct VMoveBackIterInterface : public Parent
	{
		V3D_ITERTYPEDEFS;

		RetType& operator--()
		{
			GetIter()->MoveBack();

			return (RetType&)*this;
		}

		RetType operator--(int)
		{
			RetType old(GetIter()->CreateCopy());

			GetIter()->MoveBack();

			return old;
		}
	};

	/**
	* random movement (for random access iterators)
	*/
	template<typename T, typename RetType, typename Parent>
	struct VRandomMoveIterInterface : public Parent
	{
		V3D_ITERTYPEDEFS;

		// subscripting
		Reference operator[](int n) 
		{
			return *(GetTarget() + n);
		}

		// addition + substraction
		RetType operator+(int dist) const
		{
			RetType res(GetIter()->CreateCopy());
			res += dist;
			return res;
		}

		RetType operator-(int dist) const
		{
			RetType res(GetIter()->CreateCopy());
			res -= dist;
			return res;
		}

		// substracting two iterators
		DifferenceType operator-(const RetType& sub) const
		{
			return (DifferenceType)(GetTarget() - sub.GetTarget());
		}

		//RetType& operator+(const RetType&) const;
		//RetType& operator-(const RetType&) const;

		RetType& operator+=(int dist)
		{
			GetIter()->MoveBy(dist);
			return (RetType&)*this;
		}

		RetType& operator-=(int dist)
		{
			GetIter()->MoveBy(- dist);
			return (RetType&)*this;
		}

		//RetType& operator+=(const RetType&);
		//RetType& operator-=(const RetType&);

		// ordering
		bool operator<(const RetType& o) const 
		{
			return GetTarget() < o.GetTarget();
		}

		bool operator>(const RetType& o) const 
		{
			return GetTarget() > o.GetTarget();
		}

		bool operator<=(const RetType& o) const 
		{
			return GetTarget() <= o.GetTarget();
		}

		bool operator>=(const RetType& o) const
		{
			return GetTarget() >= o.GetTarget();
		}
	};


#undef V3D_ITERTYPEDEFS
//-----------------------------------------------------------------------------
} // namespace iterutil
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VITERATORBASES_H

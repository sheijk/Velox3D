#ifndef V3D_IVITERATORPOL_H
#define V3D_IVITERATORPOL_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

	V3D_DECLARE_EXCEPTION(VUnsupportedIterOperation, VException);
/**
 * Interface for an iterator. Conatins methods for iterating forward and 
 * backward through a collection, getting the value it currently points at and 
 * checking whether it has reached the end of the collection.
 * Should be interface compatible with STL Iterators for use with STL template
 * algorithms
 * @author sheijk
 */
	template<typename TargetType>
	class IVIteratorPol
	{
	public:
		typedef typename TargetType Value;
		typedef typename TargetType* Pointer;

		virtual ~IVIteratorPol() {};

		// overload these functions to implement a custom iterator

		/** test for equality */
		virtual vbool IsEqual(const IVIteratorPol& in_Other) const = 0;

		/**
		* Comparison:
		* @return < 0 smaller than other, 0 equal, > 0 bigger than other
		*/
		virtual vint Compare(const IVIteratorPol& in_Other) const = 0;

		/** creates a copy of itself */
		virtual IVIteratorPol* CreateCopy() const = 0;

		/** move n elements forward or backward */
		virtual void MoveBy(int in_nDistance) = 0;

		/** returns a pointer to the element it points to */
		virtual Pointer Get() const = 0;
	};


//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVITERATORPOL_H

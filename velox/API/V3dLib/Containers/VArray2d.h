#ifndef V3D_VARRAY2D_H
#define V3D_VARRAY2D_H
//---------------------------------------------------------------------------
#undef min
#undef max

#include <algorithm>
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { 
//-----------------------------------------------------------------------------

/**
 * A 2d array class
 *
 * Example:
 *    - typedef VArray2d< std::string, unsigned vint > StringTable
 *    StringTable table;
 *    table.Resize( 10, 5 );
 *    table.SetElement( 3, 4, "bla" );
 *    table.Resize( 4, 7, StringTable::KeepData );
 *    if( table.GetElement(3,4) != "bla" ) MeldeBug();
 *
 * @author sheijk
 */
template <class TElement, class TIndex> class VArray2d
{
protected:
   // size of array
   TIndex m_Width;
   TIndex m_Height;

   // reallocate memory for new size. data will be lost
   vbool SetSize(TIndex width, TIndex height);

   // povinter to the elements
   TElement* m_pElements;

public:
	/** type of an element */
	typedef TElement ElementType;
	
	/** type of an index */
	typedef TIndex IndexType;

	/** 
	 * operation to be done when resizing
	 * KeepData keeps existing values of elements still inside bound after
	 * resize.
	 * FillZero constructs all values using their default c'tor
	 * Nothing does not intialize the elements
	 */
	enum ResizeFlags { KeepData, FillZero, Nothing };

	VArray2d();
	VArray2d(const VArray2d<TElement,TIndex>& cSourceArray);
	~VArray2d();

	void operator=(const VArray2d<TElement,TIndex>& source);

	/**
	 * Sets an element to a new value. If (x,y) is outside bounds nothing
	 * will be done
	 */
	inline void SetElement(const TIndex x, const TIndex y, const TElement val);

	/**
	 * Returns the value of the elements at pos (x,y)
	 */
	inline TElement GetElement(const TIndex x, const TIndex y) const;

	inline ElementType& operator()(IndexType x, IndexType y);
	inline const ElementType& operator()(IndexType x, IndexType y) const;

	/** get the array width */
	inline TIndex GetWidth() const;

	/** get the array height */
	inline TIndex GetHeight() const;

	/**
	 * Resize the array. flags determines how new values are initialized
	 *
	 * @param width new width
	 * @param height new height
	 * @param flags Set to FillZero to initialize all elements with 0 (their
	 * default c'tor. Nothing will not initialize the data. KeepData will
	 * copy positions inside both the old and new bounds to the new array
	 *
	 * @return true if array could be resized
	 */
	vbool Resize(const TIndex width, const TIndex height, const ResizeFlags flags = FillZero);

	/**
	 * Copy data from an other array.
	 *
	 * @return true on success
	 */
	vbool Copy(const VArray2d<TElement,TIndex>& source);

	/**
	 * Returns a pointer to the first element. All elements lie linearly
	 * at the returned array address in row major order
	 */
	TElement* GetRawData();
};
//---------------------------------------------------------------------------

template <class TElement, class TIndex> VArray2d<TElement, TIndex>::
   VArray2d()
      :  m_pElements( 0 ),
         m_Width( 0 ),
         m_Height( 0 )
{
}

template <class TElement, class TIndex> VArray2d<TElement, TIndex>::
   ~VArray2d()
{
   // release memory
   if( m_pElements != 0 )
   {
      delete[] m_pElements;
   }
   m_Width = 0;
   m_Height = 0;
}

template <class TElement, class TIndex> VArray2d<TElement, TIndex>::
   VArray2d(const VArray2d<TElement,TIndex>& cSourceArray)
      :  m_pElements( 0 ),
         m_Width( 0 ),
         m_Height( 0 )
{
   // call standard constructor
   VArray2d<TElement,TIndex>();

   if( !Copy( cSourceArray ) )
   {
      SetSize( 0, 0 );
   }
}

template <class TElement, class TIndex> void VArray2d<TElement, TIndex>::
   operator=(const VArray2d<TElement,TIndex>& source)
{
   Copy( source );
}

template <class TElement, class TIndex> vbool VArray2d<TElement, TIndex>::
   Copy(const VArray2d<TElement,TIndex>& source)
{
   vuint x,y;

   // set size
   if( SetSize( source.GetWidth(), source.GetHeight() ) == false )
      return false;

   // copy data
   for( x = 0; x < m_Width; x++ )
    for( y = 0; y < m_Height; y++ )
   {
      *(m_pElements+y*m_Width+x) = *(source.m_pElements+y*m_Width+x);
   }

   return true;
}

/****************************************************************************
return array height
****************************************************************************/
template <class TElement, class TIndex> TIndex VArray2d<TElement, TIndex>::
   GetHeight() const
{
   return m_Height;
}

/****************************************************************************
return array width
****************************************************************************/
template <class TElement, class TIndex> TIndex VArray2d<TElement, TIndex>::
   GetWidth() const
{
   return m_Width;
}


/****************************************************************************
make the array a new size.
KeepData: array will be initialized with zeros, old data will be copied
Nothing: nothing will happen, memory stays uninitialized
FillZero: memory will be filled with zeros
****************************************************************************/
template <class TElement, class TIndex> vbool VArray2d<TElement, TIndex>::
   Resize(const TIndex width, const TIndex height, const ResizeFlags flags)
{
   vbool ret = false;
   vint x=0 ,y=0 , h=0 , w=0;
   VArray2d<TElement, TIndex>* bak;

   // backup old data
   if( flags == KeepData )
   {
      bak = new VArray2d();
      bak->Copy( *this );
   }

   ret = SetSize( width, height );

   if( flags == FillZero  )
   {
      for(y = 0; y < m_Height; y++)
       for(x = 0; x < m_Width; x++)
         SetElement( x, y, TElement() );
   }
   // if old data shall be saved, copy old data
   else if( flags == KeepData )
   {

      // avoid copying beyond end of data
      h = std::min( m_Height, bak->m_Height );
      w = std::min( m_Width, bak->m_Width );

      // copy elements, initialize unused elements with 0
      for(y = 0; y < h; y++)
      {
         for(x = 0; x < w; x++)
         {
            SetElement(x,y, bak->GetElement(x,y) );
         }
         for(x = w; x < m_Width; x++)
            SetElement(x,y, TElement());
      }

      for(y = h; y < m_Height; y++)
       for(x = 0; x < m_Width; x++)
         SetElement( x,y, TElement() );

      delete bak;
   }

   return ret;
}

/****************************************************************************
reallocate memory for new size
****************************************************************************/
template <class TElement, class TIndex> vbool VArray2d<TElement, TIndex>::
   SetSize(const TIndex width, const TIndex height)
{
   // deallocate memory
   if( m_pElements != 0 )
   {
      delete[] m_pElements;
   }
   m_Width = 0;
   m_Height = 0;

   m_pElements = new TElement[width*height];
   if( m_pElements == 0 ) return false;
   m_Width = width;
   m_Height = height;

   return true;
}

template <class TElement, class TIndex> void VArray2d<TElement, TIndex>::
   SetElement(const TIndex x, const TIndex y, const TElement val)
{
	V3D_ASSERT(x >= 0 && x < m_Width);
	V3D_ASSERT(y >= 0 && y < m_Height);

   *(m_pElements+y*m_Width+x) = val;
}

template <class TElement, class TIndex> TElement VArray2d<TElement, TIndex>::
   GetElement(const TIndex x, const TIndex y) const
{
	V3D_ASSERT(x >= 0 && x < m_Width);
	V3D_ASSERT(y >= 0 && y < m_Height);

	return *(m_pElements+y*m_Width+x);
}

template <class TElement, class TIndex> TElement*  VArray2d<TElement, TIndex>::
   GetRawData()
{
   return m_pElements;
}

template <class TElement, class TIndex>
TElement& VArray2d<TElement, TIndex>::operator()(TIndex x, TIndex y)
{
	V3D_ASSERT(x >= 0 && x < m_Width);
	V3D_ASSERT(y >= 0 && y < m_Height);

	return m_pElements[y*m_Width+x];
}

template <class TElement, class TIndex>
const TElement& VArray2d<TElement, TIndex>::operator()(TIndex x, TIndex y) const
{
	V3D_ASSERT(x >= 0 && x < m_Width);
	V3D_ASSERT(y >= 0 && y < m_Height);

	return m_pElements[y*m_Width+x];
}

/*
to copy for new functions
template <class TElement, class TIndex> VArray2d<TElement, TIndex>::
{
}
*/

//-----------------------------------------------------------------------------
} // namespace v3d
//---------------------------------------------------------------------------
#endif

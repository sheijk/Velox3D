#ifndef V3D_VARRAY2D_H
#define V3D_VARRAY2D_H
//---------------------------------------------------------------------------
#include <algorithm>
#include <Core/VTypes.h>

//
// *** VArray2d<element_type,index_type> ***
//
// Synopsis:
//    - a 2d array
//
// Description:
//    - element_type is the type of an element
//    index_type is the type of an index for accessing an element
//
// Example:
//    - typedef VArray2d< std::string, unsigned vint > StringTable
//    StringTable table;
//    table.Resize( 10, 5 );
//    table.SetElement( 3, 4, "bla" );
//    table.Resize( 4, 7, StringTable::eKeepData );
//    if( table.GetElement(3,4) != "bla" ) MeldeBug();
//

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
   typedef TElement element_type;
   typedef TIndex index_type;

   VArray2d();
   VArray2d(const VArray2d<TElement,TIndex>& cSourceArray);
   ~VArray2d();

   void operator=(const VArray2d<TElement,TIndex>& source);

   // *** SetElement ***
   // Synopsis:
   //    - sets an element, only for positions that are in range
   // Inputs:
   //    - const index_type x, y : position
   //    const element_type val : new value of the element
   inline void SetElement(const TIndex x, const TIndex y, const TElement val);

   // *** GetElement ***
   // Synopsis:
   //    - returns the value of an element
   // Inputs:
   //    - const x, y: position
   // Returns:
   //    - element_type: the element at pos x,y
   inline TElement GetElement(const TIndex x, const TIndex y) const;

   // *** GetWidth ***
   // Synopsis:
   //    - returns the width of the array
   inline TIndex GetWidth() const;

   // *** GetHeight ***
   // Synopsis: returns the height of the array
   inline TIndex GetHeight() const;

   enum EResizeFlags { eKeepData, eFillZero, eNothing };

   // *** Resize ***
   // Synopsis:
   //    - resize the array
   // Inputs:
   //    - index_type width: the new width
   //    index_type height: the new height
   //    EResizeFlags flags: options, eKeepData for keeping elements that are
   //    both in old and new array bounds, eFillZero for all elements set to 0,
   //    and eNothing for uninitialized elements. default = eFillZero
   // Outputs:
   //    - vbool: true if resize was successful, else false
   vbool Resize(const TIndex width, const TIndex height, const EResizeFlags flags = eFillZero);

   // *** Copy ***
   // Synopsis:
   //    - copy from another array
   // Inputs:
   //    - const VArray2d<element_type, index_type>& source: the array to be
   //    copied
   // Returns:
   //    - vbool: true if successful
   vbool Copy(const VArray2d<TElement,TIndex>& source);

   // *** GetRawData ***
   // Synopsis:
   //    - returns a povinter to element 0, warning: evil ! but might be useful
   //    elements are guaranteed to be in order after element 0
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
eKeepData: array will be initialized with zeros, old data will be copied
eNothing: nothing will happen, memory stays uninitialized
eFillZero: memory will be filled with zeros
****************************************************************************/
template <class TElement, class TIndex> vbool VArray2d<TElement, TIndex>::
   Resize(const TIndex width, const TIndex height, const EResizeFlags flags)
{
   vbool ret = false;
   vint x=0 ,y=0 , h=0 , w=0;
   VArray2d<TElement, TIndex>* bak;

   // backup old data
   if( flags == eKeepData )
   {
      bak = new VArray2d();
      bak->Copy( *this );
   }

   ret = SetSize( width, height );

   if( flags == eFillZero  )
   {
      for(y = 0; y < m_Height; y++)
       for(x = 0; x < m_Width; x++)
         SetElement( x, y, 0 );
   }
   // if old data shall be saved, copy old data
   else if( flags == eKeepData )
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
            SetElement(x,y, 0 );
      }
      for(y = h; y < m_Height; y++)
       for(x = 0; x < m_Width; x++)
         SetElement( x,y,0 );

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
   if( x >= m_Width || y >= m_Height || x < 0 || y < 0 ) return;

   *(m_pElements+y*m_Width+x) = val;
}

template <class TElement, class TIndex> TElement VArray2d<TElement, TIndex>::
   GetElement(const TIndex x, const TIndex y) const
{
   if( x >= m_Width || y >= m_Height || x < 0 || y < 0 ) return 0;

   return *(m_pElements+y*m_Width+x);
}

template <class TElement, class TIndex> TElement*  VArray2d<TElement, TIndex>::
   GetRawData()
{
   return m_pElements;
}

/*
to copy for new functions
template <class TElement, class TIndex> VArray2d<TElement, TIndex>::
{
}
*/

//---------------------------------------------------------------------------
#endif

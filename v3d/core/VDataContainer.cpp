#include <Core/VDataContainer.h>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/****************************************************************************
****************************************************************************/
VDataContainer::VDataContainer() :
   m_Texts( "", "!init" ),
   m_Bools( "", false ),
   m_Numbers( "", 0 )
{
}

/****************************************************************************
****************************************************************************/
VDataContainer::~VDataContainer()
{
}

/****************************************************************************
returns number of text options
****************************************************************************/
vuint VDataContainer::TextCount() const
{
   return m_Texts.Count();
}

vuint VDataContainer::BoolCount() const
{
   return m_Bools.Count();
}

vuint VDataContainer::NumberCount() const
{
   return m_Numbers.Count();
}

/****************************************************************************
returns id of text option number nNumber
****************************************************************************/
VDataContainer::DataId VDataContainer::GetTextId( vuint nNumber ) const
{
   return m_Texts.GetKey( nNumber );
}

VDataContainer::DataId VDataContainer::GetBoolId( vuint nNumber ) const
{
   return m_Bools.GetKey( nNumber );
}

VDataContainer::DataId VDataContainer::GetNumberId( vuint nNumber ) const
{
   return m_Numbers.GetKey( nNumber );
}

/****************************************************************************
set text option 'id'
****************************************************************************/
void VDataContainer::SetText( VDataContainer::DataId id, std::string strVal )
{
   m_Texts.Set( id, strVal );
}

void VDataContainer::SetBool( VDataContainer::DataId id, vbool bVal )
{
   m_Bools.Set( id, bVal );
}

void VDataContainer::SetNumber( DataId id, int nVal )
{
   m_Numbers.Set( id, nVal );
}

/****************************************************************************
get string option 'id', "" if it does not exist
****************************************************************************/
std::string VDataContainer::GetText( VDataContainer::DataId id ) const
{
   return m_Texts.Get( id );
}

bool VDataContainer::GetBool( VDataContainer::DataId id ) const
{
   return m_Bools.Get( id );
}

int VDataContainer::GetNumber( DataId id ) const
{
   return m_Numbers.Get( id );
}

/****************************************************************************
adds option 'Id', if pStr == 0 store it internally
****************************************************************************/
vbool VDataContainer::AddText( VDataContainer::DataId id, std::string* pStr )
{
   // if id does not exist yet
   if( GetType( id ) == eNone )
   {
      // add the text
      return m_Texts.Add( id, "!init", pStr );
   }
   return false;
}

vbool VDataContainer::AddBool( VDataContainer::DataId id, vbool* pBool )
{
   // if id does not exist yet
   if( GetType( id ) == eNone )
   {
      // add the bool
      return m_Bools.Add( id, false, pBool );
   }
   else return false;
}

vbool VDataContainer::AddNumber( DataId id, vint* pNumber )
{
   // if id does not exist yet
   if( GetType( id ) == eNone )
   {
      // add the bool
      return m_Numbers.Add( id, 0, pNumber );
   }
   else return false;
}


/****************************************************************************
return the type of a data element
****************************************************************************/
VDataContainer::EDataType VDataContainer::GetType( DataId id ) const
{
   // if a text with id exists
   if( m_Texts.Exists( id ) ) return eText;
   // if a bool with key=id exists
   else if( m_Bools.Exists( id ) ) return eBool;
   // if no option with key=id exists
   else return eNone;
}

/****************************************************************************
removes all data
****************************************************************************/
void VDataContainer::Clear()
{
   m_Texts.Clear();
   m_Bools.Clear();
}

/****************************************************************************
the = operator, guess what it does...
****************************************************************************/
void VDataContainer::operator=( const VDataContainer& cont )
{
   m_Texts = cont.m_Texts;
   m_Bools = cont.m_Bools;
   m_Numbers = cont.m_Numbers;
}

//---------------------------------------------------------------------------

 
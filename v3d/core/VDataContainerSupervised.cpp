#include <Core/VDataContainerSupervised.h>
//---------------------------------------------------------------------------
#include <string>

#pragma hdrstop
using namespace std;
//---------------------------------------------------------------------------
VDataContainerSupervised::VDataContainerSupervised(SupervisorFunc pFunc) :
   VDataContainer(),
   m_pSupervisorFunc( pFunc )
{
}

void VDataContainerSupervised::SetText(DataId id, std::string strVal)
{
   // save old value
   string strOld = GetText( id );

   // if nothing has been changed we're done
   if( strOld == strVal ) return;

   // change data
   VDataContainer::SetText( id, strVal );

   // if supervising function is not set, we're done
   if( m_pSupervisorFunc == 0 ) return;

   // if change is disallowed
   if( m_pSupervisorFunc( this, id ) == false )
   {
      // undo it
      VDataContainer::SetText( id, strOld );
   }
}

void VDataContainerSupervised::SetBool(DataId id, vbool bVal)
{
   // save old value
   vbool bOld = GetBool(id);

   // if nothing has been changed we're done
   if( bOld == bVal ) return;

   // change data
   VDataContainer::SetBool( id, bVal );

   // if supervising function is not set, we're done
   if( m_pSupervisorFunc == 0 ) return;

   // if change is disallowed
   if( m_pSupervisorFunc( this, id ) == false )
   {
      // undo it
      VDataContainer::SetBool( id, bOld );
   }
}

void VDataContainerSupervised::SetNumber(DataId id, vint nVal)
{
   // save old value
   vint nOld = GetNumber( id );

   // if nothing has been changed we're done
   if( nOld == nVal ) return;

   // change data
   VDataContainer::SetNumber( id, nVal );

   // if supervising function is not set, we're done
   if( m_pSupervisorFunc == 0 ) return;

   // if change is disallowed
   if( m_pSupervisorFunc( this, id ) == false )
   {
      // undo it
      VDataContainer::SetNumber( id, nOld );
   }
}

//---------------------------------------------------------------------------


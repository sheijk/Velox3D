#ifndef V3D_VMAPCONTAINER_H
#define V3D_VMAPCONTAINER_H

#pragma warning(disable: 4786)

#include <map>
#include <list>
#include <Core/VTypes.h>


//
// *** VMapContainer<TKey type, TValue type> ***
//
// Synopsis:
//    - maps TKey and TValue
//
// Description:
//    - tool class for CDataContainer
//    
//
//	  - create a new TKey storing a TValue using Add
//      if a pointer is give to Add, the data will
//	    be stored in the external variable
//      the pointer points at. otherwise an internal TValue
//	    will be created

template<class TKey, class TValue>
class VMapContainer
{
public:

	// *** VMapContainer ***
	// Synopsis:
	//    - valid constructor
	// Inputs:
	//    - TKey/TValue to be initialized with
	// Returns:
	//    - none

	VMapContainer( TKey ktDefaultTKey, TValue ktDefaultTValue );

	

	// *** VMapContainer ***
	// Synopsis:
	//    - valid constructor, sets default TKey and TValue
	// Inputs:
	//    - none
	// Returns:
	//    - none

	VMapContainer();

	// *** Clear ***
	// Synopsis:
	//    - clears the map
	// Inputs:
	//    - none
	// Returns:
	//    - none

	void Clear();

	// *** Count ***
	// Synopsis:
	//    - counts the pairs
	// Inputs:
	//    - none
	// Returns:
	//    - number of TKey/TValue pairs

	vuint Count() const;

	// *** GetTKey ***
	// Synopsis:
	//    - gets a spefic TKey
	// Inputs:
	//    - element number
	// Returns:
	//    - TKey of the nNumer-th element

	TKey GetKey( vuint nNumber ) const;

	// *** Set ***
	// Synopsis:
	//    - sets a TValue
	// Inputs:
	//    - TKey to map with TValue
	// Returns:
	//    - none

	void Set( TKey ktTKey, TValue vtTValue );

	// *** Get ***
	// Synopsis:
	//    - gets the coresponding TValue
	// Inputs:
	//    - the TKey thats connected to TValue
	// Returns:
	//    - TValue matching the TKey


	TValue Get( TKey ktTKey ) const;

	// *** Exists ***
	// Synopsis:
	//    - returns true if TKey ktTKey exists
	// Inputs:
	//    - TKey to look for
	// Returns:
	//    - true if TKey ktTKey exists

	vbool Exists( TKey ktTKey ) const;

	// *** Add ***
	// Synopsis:
    //    - adds a TKey and sets it to vtInitVal
	//		if pValAddr is 0 the TValue will be stored internally,
	//		otherwise it'll be stored at the given address (currently ignored)
	// Inputs:
	//    - TKey and TValue to be add
	// Returns:
	//    - true if operation was successfull

	vbool Add( TKey ktTKey, TValue vtInitVal, TValue* pValAddr );

//	void operator=( const VMapContainer& mapcont );

	TKey m_DefaultTKey;
	TValue m_DefaultTValue;

private:

	typedef std::list< TValue > TValueList;
	typedef std::map< TKey, TValue* > TKeyTValueRefMap;

	TValueList m_Data;
	TKeyTValueRefMap m_Refs;
};










template< class TKey, class TValue >
VMapContainer< TKey, TValue >::VMapContainer()
{
}

/****************************************************************************
valid constructor, sets default TKey and TValue
****************************************************************************/
template< class TKey, class TValue >
VMapContainer<TKey, TValue>::VMapContainer(TKey ktDefaultTKey, TValue ktDefaultTValue):
m_DefaultTValue( ktDefaultTValue ),
m_DefaultTKey( ktDefaultTKey )
{
}

/****************************************************************************
return number of TKey/TValue pairs
****************************************************************************/
template< class TKey, class TValue >
vuint VMapContainer< TKey, TValue >::Count() const
{
	return m_Refs.size();
}

/****************************************************************************
returns the TKey of the nNumer-th element
****************************************************************************/
template< class TKey, class TValue >
TKey VMapContainer< TKey, TValue >::GetKey( vuint nNumber ) const
{
	// if nNumber is valid
	if( nNumber < Count() )
	{
		// get the nNumber-th element
		TKeyTValueRefMap::const_iterator it = m_Refs.begin();
		std::advance( it, nNumber );

		// return it's TKey
		return it->first;
	}
	// else return empty TValue
	else return m_DefaultTKey;
}

/****************************************************************************
sets a TValue
****************************************************************************/
template< class TKey, class TValue >
void VMapContainer< TKey, TValue >::Set( TKey ktTKey, TValue vtTValue )
{
	// search TKey
	TKeyTValueRefMap::iterator it = m_Refs.find( ktTKey );

	// if id exist
	if( it != m_Refs.end() )
	{
		// change it
		*(it->second) = vtTValue;
	}
}

/****************************************************************************
returns a TValue
****************************************************************************/
template< class TKey, class TValue >
TValue VMapContainer< TKey, TValue >::Get( TKey ktTKey ) const
{
	// search for TKey
	TKeyTValueRefMap::const_iterator it = m_Refs.find( ktTKey );

	// if it exist
	if( it != m_Refs.end() )
	{
		// return TValue
		return *(it->second);
	}
	// if it doesn't exist
	else
	{
		// return default
		return m_DefaultTValue;
	}
}

/****************************************************************************
returns true if TKey ktTKey exists
****************************************************************************/
template< class TKey, class TValue >
vbool VMapContainer< TKey, TValue >::Exists( TKey ktTKey ) const
{
	return ( m_Refs.find( ktTKey ) != m_Refs.end() );
}

/****************************************************************************
adds a TKey and sets it to vtInitVal
if pValAddr is 0 the TValue will be stored internally, otherwise it'll be
stored at the given address (currently ignored)
****************************************************************************/
template< class TKey, class TValue >
vbool VMapContainer< TKey, TValue >::Add( TKey ktTKey, TValue vtInitVal, TValue* pValAddr )
{
	// check if TKey already exists
	if( m_Refs.find( ktTKey ) != m_Refs.end() )
	{
		// if yes, abort
		return false;
	}
	// if it doesn't exist yet
	else
	{
		// if external address is 0
		if( pValAddr == 0 )
		{
			// add a TValue to store the data
			m_Data.push_front( vtInitVal );

			// set pointer to newly added TValue
			pValAddr = & ( *m_Data.begin() );
		}

		// add a pointer pointing to the data
		m_Refs.insert( TKeyTValueRefMap::value_type( ktTKey, pValAddr ) );
		return true;
	}
}

template< class TKey, class TValue >
void VMapContainer< TKey, TValue >::Clear()
{
	// delete data
	m_Data.erase( m_Data.begin(), m_Data.end() );

	// delete pointers
	m_Refs.erase( m_Refs.begin(), m_Refs.end() );
}

/*
template< class TKey, class TValue >
void VMapContainer< TKey, TValue >::operator=( const VMapContainer& mapcont )
{
	Clear();

	// copy internal TValues
	m_Data.insert( m_Data.begin(), mapcont.m_Data.begin(), mapcont.m_Data.end() );

	// copy pointers
//	m_Refs.insert( mapcont.m_Refs.begin(), mapcont.m_Refs.end() );
}*/

#endif

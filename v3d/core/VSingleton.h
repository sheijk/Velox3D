#ifndef V3D_VSINGLETON_H
#define V3D_VSINGLETON_H

#include <Core/VTypes.h>

//
// *** VSingleton ***
//
// Synopsis:
//    - This template class should be the base for all singletons in the engine project.
//
// Description:
//    - The make inallowed access to subclasses impossible, you should declare the dtor and ctor as private
//		and the declare a specialized version of the singleton template as a friend.
//
template <class T> class VSingleton
{
protected :

	VSingleton(void)
	{
	}

	~VSingleton(void)
	{
	}
	
	static T* ms_pInstance;

public :

	//
	// *** CreateInstance ***
	//
	// Synopsis:
	//    - Call this static function to get access to the singleton-object of the type of the subclass. 
	//
	// Returns:
	//    - T*: A pointer to the singleton object.
	//
	// Example: 
	//    - VClass* pClass = VClass::CreateInstance();
	//
	static T* CreateInstance(void)
	{
		if (ms_pInstance == NULL)
		{
			ms_pInstance = new T;
		}

		return ms_pInstance;
	}

	//
	// *** HasInstance ***
	//
	// Synopsis:
	//    - Call this function to check if an instance of the singleton-type has already been created.
	//
	// Returns:
	//    - vbool: 'true' if VSingleton::CreateInstance has been called previously, false otherwise.
	//
	// Example: 
	//    - VClass* pClass = VClass::CreateInstance();
	//		vbool bInitialized = VClass::HasInstance();
	//
	static vbool HasInstance(void)
	{
		return (ms_pInstance != NULL);
	}

	//
	// *** ReleaseInstance ***
	//
	// Synopsis:
	//    - Releases the memory allocated for a previously initialized singleton-object. Be sure to call
	//		this at shutdown for every singleton-subclass.
	//
	// Example: 
	//    - VClass* pClass = VClass::CreateInstance();
	//		pClass->DoSomething();
	//		VClass::ReleaseInstance();
	//
	static void ReleaseInstance(void)
	{
		if (ms_pInstance != NULL)
		{
			delete ms_pInstance;
			ms_pInstance = NULL;
		}
	}
};

template <class T> T* VSingleton<T>::ms_pInstance = NULL;

#endif
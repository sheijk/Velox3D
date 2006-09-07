/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVLOGDEVICE_H
#define V3D_IVLOGDEVICE_H

#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Error/VLogModeEnum.h>

namespace v3d {
namespace error {

//TODO: VStringParam/VStringRetVal benutzen

/**
 * Interface for log device. 
 * @author AcrylSword
 * @version 1.0
 */
class IVLogDevice
{
protected:
	
	/**
	 * Called by the \a Error Service when it gets a message
	 * @param in_Message The Message
	 * @param in_LogMode A member of the LogMode enumeration
	 */
	virtual void OnMessage( const VString& in_Message, LogMode in_LogMode )=0;
	
	/**
	 * Called by the Error Service to begin a progressbar
     */	
	virtual void OnProgressbarBegin()=0;

	/** Called by the error service to update the progressbar
	 * @param in_fIndex Index value between 0.0f and 1.0f
	 * fIndex should be between 0.0f and 1.0f. Other values are clamped.
	 */
    virtual void OnProgressbarUpdate( const vfloat32 in_fIndex)=0;


	/** 
	 * Called by VDebugLogger to end the progressbar
     */
	virtual void	OnProgressbarEnd()=0;


	/** 
	 * Called by the error service when a new state is added
	 * @param in_StateName The name of the state
	 * @param in_Text The text of the state
     * \a StateName is used as an identifier in all three state functions.
	 */
	virtual void	OnStateCreate( const VString& in_StateName, const VString& in_Text ) =0;

	/** 
	 * Called by the error service to update a state
	 * @param in_StateName The name of the state
	 * @param in_Text The text of the state
	 * \a StateName is used as an identifier in all three state functions
	 */
    virtual void	OnStateUpdate( const VString& in_StateName, const VString& in_Text ) =0;


	/** 
	 * Called by VDebugLogger to update a state
	 * @param in_StateName The name of the state used to be deleted
	 * \a StateName is used as an identifier in all three state functions
     */
    virtual void	OnStateDelete( const VString& in_StateName ) =0;

public:
	friend class	VErrorService;
	
	/** 
	 * Default constructor
     *
	 */
					IVLogDevice() {};


	/** 
	 * Virtual destructor
     */
	virtual			~IVLogDevice(){};
};

} // error
} // v3d
#endif


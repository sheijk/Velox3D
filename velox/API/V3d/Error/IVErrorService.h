#ifndef V3D_IVERRORSERVICE_H
#define V3D_IVERRORSERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VNamedObject.h>
#include <v3d/Error/IVLogDevice.h>
#include <v3d/Error/VLogModeEnum.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------

/**
 * The error service. Contains useful stuff for error logging
 * @author AcrylSword
 * @version 3.0
 */
class IVErrorService : public VNamedObject
{
public:
	IVErrorService(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent)
	{
	}

	/**
	 * This method registers an error::IVLogDevice object to the error service. If sucessful it will imidently
	 * start to log. 
	 * @param in_pLogDevice Pointer to the object that should be registerd
	 * @return Returns true on sucess, false if the registration failed
	 */
	virtual vbool RegisterLogDevice( IVLogDevice* in_pLogDevice ) = 0;
	
	/**
	 * This method unregisters an error:IVLogDevice object. 	
	 * Be sure to call UnregisterLogDevice for every registered log device.
	 * @param in_pLogDevice Pointer to the object that should be unregisterd
	 */
	virtual void UnregisterLogDevice( IVLogDevice* in_pLogDevice ) = 0;

	/**
	 * Prints a simple debug message
	 * @param in_Message The debug message
	 * @param in_LogMode A member of the LogMode enumeration describing the way the message should be displayed
	 */
	//TODO: VStringParam/VStringRetVal benutzen
	virtual void Message( const VString& in_Message, LogMode in_LogMode = Ok ) = 0;
	
	virtual void BeginProgressbar() = 0;
	virtual void UpdateProgressbar( const vfloat32 in_fIndex ) = 0;
	virtual void EndProgressbar() = 0;

	virtual void CreateState( const VString& in_StateName, const VString& in_Text ) = 0;
	virtual void UpdateState( const VString& in_StateName, const VString& in_Text ) = 0;
	virtual void DeleteState( const VString& in_StateName ) = 0;
};

//-----------------------------------------------------------------------------
} // error
} // v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVERRORSERVICE_H
#ifndef V3D_IVERRORSERVICE_H
#define V3D_IVERRORSERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//#include <v3d/Core/SmartPtr/VGuards.h>
#include <v3d/Core/VNamedObject.h>
#include <v3d/Error/VMessageTypeEnum.h>
#include <v3d/Error/IVErrorListener.h>
#include <v3d/Error/IVErrorStream.h>
#include <v3d/Error/IVErrorFilter.h>
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
	typedef VPointer<IVErrorStream>::SharedPtr ErrorStreamPtr;

	/**
	 * This method creates an IVErrorStream
	 * @param in_strName Name of the error stream
	 * @return SharedPointer of the error stream
	 */
	virtual ErrorStreamPtr CreateErrorStream( VStringParam in_strName ) = 0;

	/**
	 * This method returns a global error stream
	 * @return SharedPointer
	 */ 
	virtual ErrorStreamPtr GetGlobalErrorStream() = 0;

	/**
	 * This method registers an error::IVListener object to the error service. If sucessful it will imidently
	 * start to log. 
	 * @param in_pLogDevice Pointer to the object that should be registerd
	 * @return Returns true on sucess, false if the registration failed
	 */
	virtual vbool RegisterListener( IVErrorListener* in_pListerner, IVErrorFilter* in_pFilter ) = 0;
	
	/**
	 * This method unregisters an error:IVListener object. 	
	 * Be sure to call UnregisterLogDevice for every registered log device.
	 * @param in_pLogDevice Pointer to the object that should be unregisterd
	 */
	virtual void UnregisterListener( IVErrorListener* in_pListener ) = 0;
	
};

//-----------------------------------------------------------------------------
} // error
} // v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVERRORSERVICE_H
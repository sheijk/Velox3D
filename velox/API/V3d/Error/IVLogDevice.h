#ifndef V3D_IVLOGDEVICE_H
#define V3D_IVLOGDEVICE_H

#include <v3d/Core/VCoreLib.h>
#include <v3d/Error/VLogModeEnum.h>
#include <v3d/Core/Wrappers/VString.h>

namespace v3d {
namespace error {

class IVLogDevice
{
protected:

	virtual void	OnMessage( const VString& Message, LogMode LogMode )=0;
	
	virtual void	OnProgressbarBegin()=0;
	virtual void	OnProgressbarUpdate( const vfloat32 fIndex)=0;
	virtual void	OnProgressbarEnd()=0;

	virtual void	OnStateCreate( const VString& StateName, const VString& StateText ) =0;
	virtual void	OnStateUpdate( const VString& StateName, const VString& StateText ) =0;
	virtual void	OnStateDelete( const VString& StateName ) =0;

public:
	friend class	VErrorService;
	

					IVLogDevice() {};
	virtual			~IVLogDevice(){};
};

} // error
} // v3d
#endif

/*! \class VILogDevice
	\brief Interface for a logging device

*/

/*! \enum VILogDevice::eLogMode
	\brief Different types of message logging.
*/

/*! \var VILogDevice::eLogMode VILogDevice::V3D_OK
	\brief OK, no error message
*/

/*! \var VILogDevice::eLogMode VILogDevice::V3D_WARNING
	\brief WARNING, no error message, but maybe a hint for a future error
*/

/*! \var VILogDevice::eLogMode VILogDevice::V3D_ERROR
	\brief ERROR, a error message
*/

/*! \fn	virtual void VILogDevice::OnMessage(const std::string& Message, const eLogMode LogMode )
	\brief Called by \a VDebugLogger when it gets a message
	\param Message The Message
	\param LogMode A member of the eLogMode enumeration

	Implement this function in a way your LogDevice should react on a message.
*/

/*! \fn virtual void VILogDevice::OnProgressbarBegin()
	\brief Called by \a VDebugLogger to begin the progressbar

	Implement this function in a way your LogDevice should react on the begin of
	the progressbar.
*/

/*!	\fn virtual void VILogDevice::OnProgressbarUpdate(const vfloat32 fIndex);
	\brief Called by \a VDebugLogger to update the progressbar
	\param fIndex Index value between 0.0f and 1.0f

	fIndex should be between 0.0f and 1.0f. Other values are clamped.
	Implement this function in a way your LogDevice should react on the update of the 
	progressbar.
*/

/*! \fn virtual void VILogDevice::OnProgressbarEnd()
	\brief Called by VDebugLogger to end the progressbar
*/

/*! \fn virtual void VILogDevice::OnStateAdd( const std::string& StateName, const std::string& StateText );
	\brief Called by VDebugLogger when a new state is added
	\param StateName The name of the state
	\param StateText The text of the state

	\a StateName is used as an identifier in all three state functions.
	Implement this function in a way your LogDevice should add a new state.
*/

/*! \fn virtual void VILogDevice::OnStateUpdate( const std::string& StateName, const std::string& StateText )
	\brief Called by VDebugLogger to update a state
	\param StateName The name of the state
	\param StateText The text of the state

	\a StateName is used as an identifier in all three state functions
	Implement this function in a way your LogDevice should update a state.
*/

/*! \fn virtual void	VILogDevice::OnStateDelete( const std::string& StateName )
	\brief Called by VDebugLogger to update a state
	\param StateName The name of the state used to be deleted

	\a StateName is used as an identifier in all three state functions
	Implement this function in a way your LogDevice should delete a state.
*/

/*! \fn virtual void	VILogDevice::OnInfoText( const vuint Index, const std::string& Text )
	\brief Called by VDebugLogger to have some small info text
	\param Index A index value between 0 and 7
	\param Text The text

	This function can be used to have some info text that change rapidly.
	Implement this function in a way your LogDevice should handle small info texts.
*/

//	friend class	VDebugLogger;

/*! \fn VILogDevice::VILogDevice()
	\brief Default constructor

	The default constructor does nothing
*/

/*! \fn virtual VILogDevice::~VILogDevice()
	\brief Virtual destructor

*/

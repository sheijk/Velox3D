#ifndef V3D_VFILELOGGER_H
#define V3D_VFILELOGGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Error/IVLogDevice.h>

//-----------------------------------------------------------------------------
namespace v3d {
	namespace error {
//-----------------------------------------------------------------------------

/**
 * A simple file logger. logs all data into a file
 * @author AcrylSword
 * @version 1.0
 */
class VFileLogger :	public IVLogDevice
{
public:
	void	OnMessage(const VString& in_Msg, LogMode in_LogMode );

	void	OnProgressbarBegin();
	void	OnProgressbarUpdate(const vfloat32 in_fIndex);
	void	OnProgressbarEnd();

	void	OnStateCreate( const VString& in_StateName, const VString& in_Text );
	void	OnStateUpdate( const VString& in_StateName, const VString& in_Text );
	void	OnStateDelete( const VString& in_StateName );
};

//-----------------------------------------------------------------------------
}// error
}// v3d
//-----------------------------------------------------------------------------
#endif
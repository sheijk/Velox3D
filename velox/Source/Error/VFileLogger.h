#ifndef V3D_VFILELOGGER_H
#define V3D_VFILELOGGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Error/IVErrorListener.h>
#include <fstream>

//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------

/**
 * A simple file logger. logs all data into a file
 * @author AcrylSword
 * @version 1.0
 */
class VFileLogger :	public IVErrorListener
{
public:
			VFileLogger( VStringParam in_strFileName );
			~VFileLogger();

	void OnMessage( VStringParam in_strStreamName, 
					VStringParam in_strMessage,
					VMessageType in_MessageType,
					VStringParam in_strFile,
					vuint in_nLine );

	void	OnProgressbarBegin();
	void	OnProgressbarUpdate(const vfloat32 in_fIndex);
	void	OnProgressbarEnd();

	void	OnStateUpdate( VStringParam in_strStreamName, VStringParam in_strText );

protected:

	VFileLogger() {};
	std::ofstream m_File;
	
};

//-----------------------------------------------------------------------------
}// error
}// v3d
//-----------------------------------------------------------------------------
#endif
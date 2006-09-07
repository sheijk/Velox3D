/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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

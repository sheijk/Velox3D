/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDEBUGMONITOR_H
#define V3D_VDEBUGMONITOR_H
//-----------------------------------------------------------------------------
#include <windows.h>
#include <v3d/Core/VCoreLib.h>
#include <v3d/Error/IVErrorListener.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace error {
//-----------------------------------------------------------------------------

class VDebugMonitor : public IVErrorListener
{
public:
			VDebugMonitor();
			~VDebugMonitor();

protected:
	void	OnMessage(VStringParam in_Message, VMessageType in_MessageType );
	
	void	OnProgressbarBegin();
	void	OnProgressbarUpdate(const vfloat32 in_fIndex);
	void	OnProgressbarEnd();

	void	OnStateUpdate( VStringParam in_Text );
	
	void	SetDebugLevel( const vuint in_iLevel );

	HWND	m_DebugMonitorHWND;
	vbool	m_bIsAvaible;
	COPYDATASTRUCT m_MyCopyData;
};

//-----------------------------------------------------------------------------
} // error
} // v3d;
//-----------------------------------------------------------------------------
#endif



/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVWINDOWFRAME_H
#define V3D_IVWINDOWFRAME_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Window/IVWxConnector.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

//TODO: move to v3d/window/wx/
class IVWindowFrame
{
public:
	
	/* Shows the window frame if the given param is true */
	virtual void ShowFrame(vbool in_Param) = 0;

	/* Registers the window to the wx connector */
	virtual void Register()
	{

		IVWxConnector* WinConnect;
		WinConnect = QueryObject<IVWxConnector>("wx.connector");
		WinConnect->Register(this);
	};


	virtual ~IVWindowFrame(){};
};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVWINDOWFRAME_H


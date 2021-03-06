/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCONSOLESERVICE_H
#define V3D_VCONSOLESERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Error/IVErrorService.h>
#include <V3d/Console/IVConsoleService.h>
#include <v3d/Updater/IVUpdateable.h>
//-----------------------------------------------------------------------------
#pragma warning( disable : 4267 )
#include <wx/wx.h>
#pragma warning( default : 4267 )

#include "VConsoleFrame.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------


class VConsoleService : public IVConsoleService
{
public:
	VConsoleService();
	virtual ~VConsoleService();
	virtual void Flush() {};
	virtual void Write(VStringParam in_strString);

	virtual CommandConnection RegisterCommandListener(const CommandSlot& slot);

private:
	error::IVErrorService& GetErrorService();
	VConsoleFrame* m_pFrame;
};

//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCONSOLESERVICE_H


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
//-----------------------------------------------------------------------------

#include "VConsoleFrame.h"
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------


class VConsoleService : public IVConsoleSerivce
{
public:
	VConsoleService();
	virtual ~VConsoleService();
	virtual void Flush() {};
	virtual void Write(VStringParam in_strString);

private:
	error::IVErrorService& GetErrorService();
	VConsoleFrame* m_pFrame;
};

//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCONSOLESERVICE_H

//TODO: correct file guard
#ifndef V3D_VCONSOLESERVICE_H
#define V3D_VCONSOLESERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Error/IVErrorService.h>
#include <V3d/Console/IVConsoleService.h>
#include <wx/wx.h>
//-----------------------------------------------------------------------------

#include "VConsoleWindow.h"
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------


class VConsoleService : public v3d::console::IVConsoleSerivce
{
public:
	VConsoleService();
	virtual void Update();
	virtual ~VConsoleService();
	virtual void Flush() {};
	virtual void Write(VStringParam in_strString);

private:
	error::IVErrorService* ErrorService;
};

//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCONSOLESERVICE_H

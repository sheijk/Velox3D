//TODO: correct file guard
#ifndef V3D_VCONSOLESERVICE_H
#define V3D_VCONSOLESERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Error/IVErrorService.h>
#include <V3d/Console/IVConsoleService.h>
#include <v3d/Updater/IVUpdateable.h>
#include <wx/wx.h>
//-----------------------------------------------------------------------------

#include "VConsoleWindow.h"
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------


class VConsoleService 
	: public IVConsoleSerivce, 
	  public v3d::updater::IVUpdateable
{
public:
	VConsoleService();
	virtual void Update();
	virtual ~VConsoleService();
	virtual void Flush() {};
	virtual void Write(VStringParam in_strString);

	virtual void Update(float in_fSeconds);
	virtual void Activate();
	virtual void Deactivate();
private:
	error::IVErrorService& GetErrorService();
};

//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCONSOLESERVICE_H

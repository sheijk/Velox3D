/**
 * Implementation of the Interface IVWindowManager.
 * Use this interface to work with the managers
 */

#ifndef V3D_IVWINDOWMANAGER_H
#define V3D_IVWINDOWMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Window/IVWindow.h>
#include <V3d/Core/SmartPtr/VGuards.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------
class IVWindowManager
{
public:

	typedef VPointer<IVWindow>::SharedPtr IVWindowPtr;

	virtual IVWindowPtr CreateWindow(VStringParam in_pName) = 0;
	virtual ~IVWindowManager() {};

};
	

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVWINDOWMANAGER_H

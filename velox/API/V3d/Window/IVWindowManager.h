#ifndef V3D_IVWINDOWMANAGER_H
#define V3D_IVWINDOWMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Window/IVWindow.h>
#include <V3d/Core/SmartPtr/VGuards.h>
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VServicePtr.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------

/**
 * Implementation of the Interface IVWindowManager.
 * Use this interface to work with the managers
 */
class IVWindowManager
{
public:

	typedef VPointer<IVWindow>::SharedPtr IVWindowPtr;

	/* Returns a pointer to the window created by this manager */
	virtual IVWindowPtr QueryWindow(VStringParam in_pName) = 0;
	
	virtual ~IVWindowManager() {};

};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
template<>
inline v3d::window::IVWindowManager* v3d::QueryService<v3d::window::IVWindowManager>()
{
	return QueryObject<v3d::window::IVWindowManager>("window.manager");
}
//-----------------------------------------------------------------------------
#endif // V3D_IVWINDOWMANAGER_H

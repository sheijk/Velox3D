#ifndef V3D_VWINDOWMANAGERBASE_H
#define V3D_VWINDOWMANAGERBASE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Window/IVWindow.h>
#include <v3d/Window/IVWindowManager.h>
#include <v3d/Core/VNamedObject.h>
//-----------------------------------------------------------------------------
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window{
//-----------------------------------------------------------------------------

/**
 * Defines all default behavoir of a window manger
 */
//TODO weak oop fix
class VWindowManagerBase : public IVWindowManager, public VNamedObject
{

public:

	VWindowManagerBase();
	virtual ~VWindowManagerBase();

protected:

	/**
	 * Holds a list to all created windows	
	 */
	std::list<IVWindow*> m_WindowList;

	vuint m_iNumWindows;
	vuint GetNumberOfWindows();
};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VWINDOWMANAGERBASE_H

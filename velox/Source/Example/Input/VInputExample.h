#ifndef V3D_VINPUTEXAMPLE_09_02_2004_H
#define V3D_VINPUTEXAMPLE_09_02_2004_H
//-----------------------------------------------------------------------------
#include <v3d/Core/IVApplication.h>
#include <v3d/Core/VNamedObject.h>
#include <V3d/Console/IVConsoleService.h>
#include <v3d/Input/IVInputManager.h>

//#include <V3dLib/BoostSignals.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
namespace example {
//-----------------------------------------------------------------------------
/**
 * An example input application.
 */
class VInputExample : public IVApplication, public VNamedObject
{
public:
	VInputExample(VStringParam in_strName) : VNamedObject(in_strName,0) {;};
//	virtual ~VInputExample();

	virtual int Main();
};

//-----------------------------------------------------------------------------
} // namespace example
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VINPUTEXAMPLE_09_02_2004_H
#ifndef V3D_IVBUTTON_H
#define V3D_IVBUTTON_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/**
 * Interface for any input controller button
 * @author AcrylSword
 * @version 1.0
 */
class IVButton
{
public:
	
	virtual					~IVButton() {};
	
	virtual VStringRetVal	GetName() = 0;
	virtual vbool			IsDown() = 0;
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d

//-----------------------------------------------------------------------------
#endif // V3D_IVBUTTON_H

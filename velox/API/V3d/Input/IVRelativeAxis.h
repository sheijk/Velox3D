#ifndef V3D_IVRelativeAxis_H
#define V3D_IVRelativeAxis_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/* The interface for an input controller axis that returns relative coordinate
* @author AcrylSword
* @version 1.0
*/

class IVRelativeAxis
{
public:
	
	virtual					~IVRelativeAxis() {};

	virtual VStringRetVal	GetName() = 0;
	virtual vfloat32		GetLastMovement() = 0;
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVRELATIVEAXIS_H

#ifndef V3D_IVRELATIVEAXIS_09_02_2004_H
#define V3D_IVRELATIVEAXIS_09_02_2004_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/* The interface for an input controller axis that returns relative coordinate
* @author sheijk
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
#endif // V3D_IVRELATIVEAXIS_09_02_2004_H

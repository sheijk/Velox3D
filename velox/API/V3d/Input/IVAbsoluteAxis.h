#ifndef V3D_IVABSOLUTEAXIS_09_02_2004_H
#define V3D_IVABSOLUTEAXIS_09_02_2004_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
/* The interface for an input controller axis that returns absolute coordinates
 * @author sheijk
 * @version 1.0
 */
class IVAbsoluteAxis
{
public:
	
	virtual					~IVAbsoluteAxis() {};

	virtual VStringRetVal	GetName()				= 0;
	virtual vfloat32		GetPosition()			= 0;
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVABSOLUTEAXIS_09_02_2004_H
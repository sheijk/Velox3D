#ifndef V3D_IVTIMER_H
#define V3D_IVTIMER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace updater{
//-----------------------------------------------------------------------------

/**
 * The interface for all timer implementations
 */
class IVTimer
{
public:

	/* Updates the timer each frame */
	virtual void Update(vfloat32 in_fSeconds) = 0;

	/* returns the last frame duration */
	virtual vfloat64 GetFrameDuration() = 0;
    
	/* Multiply each movement with this frame */
	//virtual vfloat32 GetSpeedFactor() = 0;
};

//-----------------------------------------------------------------------------
} // namespace updater
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVTIMER_H

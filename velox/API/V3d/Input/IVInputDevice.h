#ifndef V3D_IVINPUTDEVICE_H
#define V3D_IVINPUTDEVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VIterator.h>
#include <v3d/Input/IVButton.h>
#include <v3d/Input/IVRelativeAxis.h>
#include <v3d/Input/IVAbsoluteAxis.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------

/**
 * Interface for an attached input controller
 * @author sheijk
 * @version 1.0
 */

class IVInputDevice
{
public:
	typedef VForwardIterator<IVButton>			ButtonIterator;
	typedef VForwardIterator<IVRelativeAxis> RelativeAxisIterator;
	typedef VForwardIterator<IVAbsoluteAxis> AbsoluteAxisIterator;
    
	virtual							~IVInputDevice() {};

	virtual VStringRetVal			GetName() = 0;

	virtual ButtonIterator			ButtonBegin() = 0;
	virtual ButtonIterator			ButtonEnd() = 0;

	virtual AbsoluteAxisIterator	AbsoluteAxisBegin() = 0;
	virtual AbsoluteAxisIterator	AbsoluteAxisEnd() = 0;

	virtual RelativeAxisIterator	RelativeAxisBegin() = 0;
	virtual RelativeAxisIterator	RelativeAxisEnd() = 0;
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDEVICE_H

#ifndef V3D_VIOException_H
#define V3D_VIOException_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Base exception class for all virtual file system exceptions
 */
class VIOException : public VException
{
public:
	VIOException(
		VStringParam errorMsg, 
		VStringParam fileName, 
		vuint lineNumber)
		: VException(errorMsg, fileName, lineNumber) {};

	virtual ~VIOException() {};
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VIOException_H

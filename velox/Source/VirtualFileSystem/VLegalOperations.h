#ifndef V3D_VLEGALOPERATIONS_H
#define V3D_VLEGALOPERATIONS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVLegalOperations.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Simply implements the IVLegalOperations interface
 * Legal operations are set using the constructor
 */
class VLegalOperations : public IVLegalOperations
{
private:
	vbool m_bAllowRead;
	vbool m_bAllowWrite;
	vbool m_bAllowPositioning;
	vbool m_bAllowGetPosition;

public:
	VLegalOperations(vbool read, vbool write, vbool setpos, vbool getpos);

	virtual vbool AllowRead() const;
	virtual vbool AllowWrite() const;
	virtual vbool AllowPositioning() const;
	virtual vbool AllowGetPosition() const;
};


//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VLEGALOPERATIONS_H
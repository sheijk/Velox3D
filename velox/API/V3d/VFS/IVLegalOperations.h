#ifndef V3D_IVLEGALOPERATION_H
#define V3D_IVLEGALOPERATION_H
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Information about the access rights of a stream
 */
class IVLegalOperations
{
public:
	virtual ~IVLegalOperations() {};

	virtual vbool AllowRead() const = 0;
	virtual vbool AllowWrite() const = 0;
	virtual vbool AllowPositioning() const = 0;
	virtual vbool AllowGetPosition() const = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVLEGALOPERATION_H


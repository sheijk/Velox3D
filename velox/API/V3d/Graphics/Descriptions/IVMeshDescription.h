#ifndef IVMESHDESCRIPTION_H
#define IVMESHDESCRIPTION_H
//-------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/Descriptions/VTriangle.h>
#include <v3d/Core/Wrappers/VIterator.h>

//-------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-------------------------------------------------------------------------

/**
 * A class which contains geometry data (vertices and faces). Provides only read
 * access to geometry
 */
class IVMeshDescription
{
public:
	typedef VBidirectionalIterator<const VTriangle> TriangleIterator;

	virtual TriangleIterator TriangleBegin() const = 0;
	virtual TriangleIterator TriangleEnd() const = 0;
};

//-------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-------------------------------------------------------------------------
#endif // IVMESHDESCRIPTION_H
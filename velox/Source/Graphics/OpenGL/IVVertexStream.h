#ifndef V3D_IVVERTEXSTREAM_2005_02_03_H
#define V3D_IVVERTEXSTREAM_2005_02_03_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * An OpenGL vertex stream. Provides a way to bind vertex data to be sent to
 * OpenGL
 * 
 * @author sheijk
 */
class IVVertexStream
{
public:
	enum DataTypes
	{
		Coordinates	= 1,
		Colors		= 2,
		Indices		= 4,
		TexCoords	= 8,
	};

	virtual ~IVVertexStream() {};

	virtual vbool Bind(DataTypes in_StreamTypes) const = 0;
	virtual void UnbindAll() const = 0;
};

inline IVVertexStream::DataTypes operator|(
	IVVertexStream::DataTypes l, IVVertexStream::DataTypes r)
{
	return IVVertexStream::DataTypes(int(l) | int(r));
}
//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_IVVERTEXSTREAM_2005_02_03_H

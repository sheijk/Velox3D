#ifndef V3D_IVSTRINGSTREAM_H
#define V3D_IVSTRINGSTREAM_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <sstream>
//-----------------------------------------------------------------------------
namespace v3d {
namespace util {
//-----------------------------------------------------------------------------
class IVStringStream
{
public:
	virtual void Write( VStringParam in_strString ) = 0;
	virtual void Flush() = 0;
};

/*
template <typename Stream, typename T> Stream& operator<<( Stream& in_Stream, T in_Val)
{
	std::ostringstream oStream;
	oStream << std::flush << in_Val;
	in_Stream.Write( oStream.str().c_str() );
	oStream.str("");
	return in_Stream;
}
*/

template <typename T> IVStringStream& operator<<(IVStringStream& in_Stream, T in_Val)
	{
	std::ostringstream oStream;
	oStream << std::flush << in_Val;
	in_Stream.Write( oStream.str().c_str() );
	oStream.str("");
	return in_Stream;
	}


// manipulator
inline IVStringStream& Flush( IVStringStream& in_Stream )
{
	in_Stream.Flush();
	return in_Stream;
}
//-----------------------------------------------------------------------------
} // namespace util
} // namespace v3d
#endif // V3D_IVSTRINGSTREAM_H
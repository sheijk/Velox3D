/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVSTRINGSTREAM_H
#define V3D_IVSTRINGSTREAM_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <sstream>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
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
} // namespace utils
} // namespace v3d
#endif // V3D_IVSTRINGSTREAM_H

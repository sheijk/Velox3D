#ifndef V3D_RACERUTILS_2004_10_12_H
#define V3D_RACERUTILS_2004_10_12_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------

// some useful functions (candidates for beeing moved to the velox lib)

IVStream::ByteCount GetSize(IVStream& in_Stream)
{
	V3D_ASSERT(in_Stream.GetLegalOps()->AllowPositioning());
	V3D_ASSERT(in_Stream.GetLegalOps()->AllowGetPosition());

	const IVStream::ByteCount originalPosition = in_Stream.GetPos();
	in_Stream.SetPos(IVStream::End, 0);
	const IVStream::ByteCount size = in_Stream.GetPos();
	in_Stream.SetPos(IVStream::Begin, originalPosition);

	return size;
}
//-----------------------------------------------------------------------------
#endif // V3D_RACERUTILS_2004_10_12_H

/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSTREAMOPS_H
#define V3D_VSTREAMOPS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/VFS/IVStream.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/VFS/VIOException.h>

#include <cstring>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------
/**
 * Streaming operations for IVStream
 * stream << data;
 */

	// write operators
	inline IVStream& operator<<(IVStream& stream, const vint8 val)
	{
		stream.Write(&val, sizeof(val));
		return stream;
	}

	inline IVStream& operator<<(IVStream& stream, const vuint8 val)
	{
		stream.Write(&val, sizeof(val));
		return stream;
	}

	inline IVStream& operator<<(IVStream& stream, const vint16 val)
	{
		stream.Write(&val, sizeof(val));
		return stream;
	}

	inline IVStream& operator<<(IVStream& stream, const vuint16 val)
	{
		stream.Write(&val, sizeof(val));
		return stream;
	}

	inline IVStream& operator<<(IVStream& stream, const vint32 val)
	{
		stream.Write(&val, sizeof(val));
		return stream;
	}

	inline IVStream& operator<<(IVStream& stream, const vuint32 val)
	{
		stream.Write(&val, sizeof(val));
		return stream;
	}

	inline IVStream& operator<<(IVStream& stream, const vint64 val)
	{
		stream.Write(&val, sizeof(val));
		return stream;
	}

	inline IVStream& operator<<(IVStream& stream, const vuint64 val)
	{
		stream.Write(&val, sizeof(val));
		return stream;
	}

	inline IVStream& operator<<(IVStream& stream, const vfloat32 val)
	{
		stream.Write(&val, sizeof(val));
		return stream;
	}

	inline IVStream& operator<<(IVStream& stream, const vfloat64 val)
	{
		stream.Write(&val, sizeof(val));
		return stream;
	}

	inline IVStream& operator<<(IVStream& stream, const vbool val)
	{
		stream.Write(&val, sizeof(val));
		return stream;
	}

	inline IVStream& operator<<(IVStream& stream, const VString& txt)
	{
		stream.Write(txt.AsCString(), txt.Length());
		return stream;
	}

	inline IVStream& operator<<(IVStream& stream, const char* txt)
	{
		stream.Write(txt, (IVStream::ByteCount)std::strlen(txt));
		return stream;
	}

	// read operators

	inline IVStream& operator>>(IVStream& stream, vint8& val)
	{
		if( stream.Read(&val, sizeof(val)) != sizeof(val) )
		{
			V3D_THROW(VIOException, "could not >> vint from IVStream");
		}
		return stream;
	}

	inline IVStream& operator>>(IVStream& stream, vuint8& val)
	{
		if( stream.Read(&val, sizeof(val)) != sizeof(val) )
		{
			V3D_THROW(VIOException, "could not >> vint from IVStream");
		}
		return stream;
	}

	inline IVStream& operator>>(IVStream& stream, vint16& val)
	{
		if( stream.Read(&val, sizeof(val)) != sizeof(val) )
		{
			V3D_THROW(VIOException, "could not >> vint from IVStream");
		}
		return stream;
	}

	inline IVStream& operator>>(IVStream& stream, vuint16& val)
	{
		if( stream.Read(&val, sizeof(val)) != sizeof(val) )
		{
			V3D_THROW(VIOException, "could not >> vint from IVStream");
		}
		return stream;
	}

	inline IVStream& operator>>(IVStream& stream, vint32& val)
	{
		if( stream.Read(&val, sizeof(val)) != sizeof(val) )
		{
			V3D_THROW(VIOException, "could not >> vint from IVStream");
		}
		return stream;
	}

	inline IVStream& operator>>(IVStream& stream, vuint32& val)
	{
		if( stream.Read(&val, sizeof(val)) != sizeof(val) )
		{
			V3D_THROW(VIOException, "could not >> vint from IVStream");
		}
		return stream;
	}

	inline IVStream& operator>>(IVStream& stream, vint64& val)
	{
		if( stream.Read(&val, sizeof(val)) != sizeof(val) )
		{
			V3D_THROW(VIOException, "could not >> vint from IVStream");
		}
		return stream;
	}

	inline IVStream& operator>>(IVStream& stream, vuint64& val)
	{
		if( stream.Read(&val, sizeof(val)) != sizeof(val) )
		{
			V3D_THROW(VIOException, "could not >> vint from IVStream");
		}
		return stream;
	}

	inline IVStream& operator>>(IVStream& stream, vfloat32& val)
	{
		if( stream.Read(&val, sizeof(val)) != sizeof(val) )
		{
			V3D_THROW(VIOException, "could not >> vint from IVStream");
		}
		return stream;
	}

	inline IVStream& operator>>(IVStream& stream, vfloat64& val)
	{
		if( stream.Read(&val, sizeof(val)) != sizeof(val) )
		{
			V3D_THROW(VIOException, "could not >> vint from IVStream");
		}
		return stream;
	}

	inline IVStream& operator>>(IVStream& stream, vbool& val)
	{
		if( stream.Read(&val, sizeof(val)) != sizeof(val) )
		{
			V3D_THROW(VIOException, "could not >> vint from IVStream");
		}
		return stream;
	}

//-----------------------------------------------------------------------------
} // namspace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTREAMOPS_H


/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//TODO: correct file guard
#ifndef V3D_IVStreamFactory_H
#define V3D_IVStreamFactory_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/VFS/IVBufferStream.h>
#include <V3d/VFS/VFlags.h>
#include <V3d/Core/VNamedObject.h>
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * A factory for streams. Used for seperating the creation of streams
 * from the rest of the file system.
 */
class IVStreamFactory : public VNamedObject
{
public:
	/** c'tor, registers the factory to the object registry */
	IVStreamFactory(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent) {};

	virtual ~IVStreamFactory() {};

	/** pointer type for returnging file streams */
	typedef VPointer<IVBufferStream>::SharedPtr FileStreamPtr;

	/** pointer type for returning offline streams */
	typedef VPointer<IVOfflineStream>::SharedPtr OfflineStreamPtr;

	/** pointer type for streams */
	typedef VPointer<IVStream>::SharedPtr StreamPtr;

	/** creates a stream which directly accesses files */
	virtual FileStreamPtr CreateFileStream(
		VStringParam in_strName, 
		VCreationFlags in_OpenMode,
		VAccessModeFlags in_Access) = 0;

	/** creates a stream which automatically reserves as much data as is
		required in memory */
	virtual StreamPtr CreateMemoryStream(
		IVStream::ByteCount in_nInitialSize = 0) = 0;
};

//-----------------------------------------------------------------------------
} // namespace vfs
//-----------------------------------------------------------------------------
template<>
inline v3d::vfs::IVStreamFactory* QueryService<v3d::vfs::IVStreamFactory>()
{
	return QueryObject<v3d::vfs::IVStreamFactory>("vfs.strfact");
}
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#endif // V3D_IVStreamFactory_H


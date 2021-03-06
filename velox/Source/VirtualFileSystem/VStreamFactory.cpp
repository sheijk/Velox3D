/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VStreamFactory.h"
//-----------------------------------------------------------------------------
#include "VFileStream.h"
#include "VMemoryStream.h"
#include "VBufferStreamGuard.h"
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VStreamFactory::VStreamFactory(VStringParam in_strName) :
	IVStreamFactory(in_strName, 0)
{
}

/**
 * d'tor
 */
VStreamFactory::~VStreamFactory()
{
}

IVStreamFactory::FileStreamPtr VStreamFactory::CreateFileStream(
	VStringParam in_strName, 
	VCreationFlags in_OpenMode,
	VAccessModeFlags in_Access)
{
	VFileStream* pFileStream
		= new VFileStream(in_strName, in_Access, in_OpenMode);

	// add access right guard
	VBufferStreamGuard* pGuard = new VBufferStreamGuard(pFileStream);

	return FileStreamPtr(pGuard);
}

//TODO: exception werfen wenn 0 zurueck gegeben wuerde

IVStreamFactory::StreamPtr VStreamFactory::CreateMemoryStream(
	IVStream::ByteCount in_nInitialSize)
{
	VMemoryStream* pMemoryStream
		= new VMemoryStream(in_nInitialSize);

	//VStreamToOfflineStreamWrapper* pWrapStream
	//	= new VStreamToOfflineStreamWrapper(pMemoryStream);

	return StreamPtr(pMemoryStream);
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------


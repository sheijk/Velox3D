#include "VStreamFactory.h"
//-----------------------------------------------------------------------------
#include "VFileStream.h"
#include "VMemoryStream.h"
#include "VStreamToOfflineStreamWrapper.h"

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

IVStreamFactory::OfflineStreamPtr VStreamFactory::CreateFileStream(
	VStringParam in_strName, 
	VCreationFlags in_OpenMode,
	VAccessModeFlags in_Access)
{
	VFileStream* pFileStream
		= new VFileStream(in_strName, in_Access, in_OpenMode);

	return OfflineStreamPtr(pFileStream);
}

IVStreamFactory::OfflineStreamPtr VStreamFactory::CreateMemoryStream(
	IVStream::ByteCount in_nInitialSize)
{
	VMemoryStream* pMemoryStream
		= new VMemoryStream(in_nInitialSize);

	VStreamToOfflineStreamWrapper* pWrapStream
		= new VStreamToOfflineStreamWrapper(pMemoryStream);

	return OfflineStreamPtr(pWrapStream);
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------

#include "VStreamFactory.h"
//-----------------------------------------------------------------------------
#include "VFileStream.h"

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

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------

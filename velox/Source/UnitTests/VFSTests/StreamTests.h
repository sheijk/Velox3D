//TODO: correct file guard
#ifndef V3D_STREAMTESTS_H
#define V3D_STREAMTESTS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>


namespace v3d 
{ 
	namespace vfs 
	{
		class IVStream;
		class IVOfflineStream;
	}
}
//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------
class IVUnitTest;

void TestStreamRW(IVUnitTest* in_pTest, vfs::IVStream* in_pStream);

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_STREAMTESTS_H

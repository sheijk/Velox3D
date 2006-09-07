/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

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


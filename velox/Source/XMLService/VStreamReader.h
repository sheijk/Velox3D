#ifndef V3D_VSTREAMREADER_H
#define V3D_VSTREAMREADER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Vfs/IVStream.h>
#include <V3d/Core/VException.h>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------
//using namespace v3d::vfs;

/**
* VStreamReader reads out a stream and creates an buffer
* @author insane
* @version 1.0
*/

class VStreamReader
{
public:
	typedef VException VXMLException;
	typedef std::list<char*> CharList;

	enum SizeofBuffer { BufferSize = 1024 };
	
	~VStreamReader();
	VStreamReader(vfs::IVStream* in_pStream);
	void* GetStreamBuffer();
	
	
	private:
	
	 vchar *m_Buffer;
};

//-----------------------------------------------------------------------------
} // v3d
} // xml
//-----------------------------------------------------------------------------
#endif // V3D_VSTREAMREADER_H

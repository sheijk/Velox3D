#ifndef V3D_VSTREAMREADER_H
#define V3D_VSTREAMREADER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Vfs/IVStream.h>
#include <V3d/Core/VException.h>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace util {
namespace importer {
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

	enum SizeofBuffer { BufferSize = 32768 }; //TODO cached to 3mb. files can get big
	
	~VStreamReader();
	VStreamReader(vfs::IVStream* in_pStream);
	void* GetStreamBuffer();
	vulong GetSizeOfBuffer();
	
	
	private:
	
	 vchar *m_Buffer;
	 vulong iSizeOfBuffer;
	 vulong iSizeOfBufferElements;
};

//-----------------------------------------------------------------------------
} // namespace importer
} // v3d
} // util
//-----------------------------------------------------------------------------
#endif // V3D_VSTREAMREADER_H

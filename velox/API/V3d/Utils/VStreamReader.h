#ifndef V3D_VSTREAMREADER_H
#define V3D_VSTREAMREADER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Vfs/IVStream.h>
#include <V3d/Core/VException.h>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
//-----------------------------------------------------------------------------

/**
 * VStreamReader reads out a stream and creates a buffer
 * @author ins
 */
class VStreamReader
{
public:
	typedef VException VXMLException;
	typedef std::list<char*> CharList;

	enum SizeofBuffer { BufferSize = 32768 }; 
		
	~VStreamReader();
	VStreamReader(vfs::IVStream* in_pStream);

	void* GetStreamBuffer();
	vulong GetSizeOfBuffer() const;

	void CopyToString(std::string* in_pString) const;
	
private:
	vchar *m_Buffer;
	vulong iSizeOfBuffer;
	vulong iSizeOfBufferElements;
};

//-----------------------------------------------------------------------------
} // v3d
} // util
//-----------------------------------------------------------------------------
#endif // V3D_VSTREAMREADER_H

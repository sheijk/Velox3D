#ifndef V3D_VBUFFERMANAGER_H
#define V3D_VBUFFERMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVDevice.h>

#include <list>
#include <algorithm>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Takes care of a list of VBuffer<..>* elements and guarantees deletion
 * when removing
 *
 * @author sheijk
 */
template<typename BufferType>
class VBufferManager
{
	typedef std::list<BufferType*> BufferList;

	BufferList m_Buffers;
public:
	typedef BufferType Buffer;

	VBufferManager() {}
	~VBufferManager()
	{
		// delete all buffers
		while( ! m_Buffers.empty() )
		{
			Delete(m_Buffers.front());
		}
	}

	void Add(Buffer* in_pBuffer)
	{
		m_Buffers.push_back(in_pBuffer);
	}

	void Delete(Buffer*& in_pBuffer)
	{
		BufferList::iterator it = 
			std::find(m_Buffers.begin(), m_Buffers.end(), in_pBuffer);
		
        if( it != m_Buffers.end() )
		{
			m_Buffers.erase(it);
			delete in_pBuffer;
			in_pBuffer = 0;
		}
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBUFFERMANAGER_H

/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VBUFFERMANAGER_H
#define V3D_VBUFFERMANAGER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVDevice.h>

#include <map>
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
	//typedef std::list<BufferType*> BufferList;
	typedef std::map<BufferType*, vuint> BufferList;

	BufferList m_Buffers;
public:
	typedef BufferType Buffer;

	VBufferManager() {}
	~VBufferManager()
	{
		// delete all buffers
		//while( ! m_Buffers.empty() )
		//{
		//	Delete(m_Buffers.front());
		//}
	}

	vuint GetBufferCount() const
	{
		return vuint(m_Buffers.size());
	}

	Buffer* GetBuffer(vuint in_nIndex) const
	{
		BufferList::const_iterator it = m_Buffers.begin();
		std::advance(it, in_nIndex);

		return it->first;
	}

	vuint GetReferenceCount(Buffer* in_Buffer)
	{
		BufferList::iterator it = m_Buffers.find(in_Buffer);

		if( it != m_Buffers.end() )
		{
			return it->second;
		}
		else
		{
			return 0;
		}
	}

	void Add(Buffer* in_pBuffer)
	{
		// find buffer
		BufferList::iterator bufferIter = m_Buffers.find(in_pBuffer);

		// if it is not contained, yet
		if( bufferIter == m_Buffers.end() )
		{
			// add it
			bufferIter = (m_Buffers.insert(BufferList::value_type(in_pBuffer, 0))).first;
		}

		// increase ref count
		bufferIter->second++;
	}

	void Delete(Buffer*& in_pBuffer)
	{
		// find buffer
		BufferList::iterator it = m_Buffers.find(in_pBuffer);
		//BufferList::iterator it = 
		//	std::find(m_Buffers.begin(), m_Buffers.end(), in_pBuffer);
		
        if( it != m_Buffers.end() )
		{
			// decrease reference count
			it->second--;

			// if ref count is zero, delete buffer
			if( it->second <= 0 )
			{
				delete in_pBuffer;
				m_Buffers.erase(it);
				in_pBuffer = 0;
			}
		}
	}

	vbool Contains(const Buffer* in_pBuffer);
};

//-----------------------------------------------------------------------------
//TODO: move to inline file
template<typename BufferType>
vbool VBufferManager<BufferType>::Contains(const Buffer* in_pBuffer)
{
	// sorry for this crap.. but find(in_pBuffer) does not accept a constant
	// buffer.. (possibly an vc stl bug?)
	for(
		BufferList::iterator it = m_Buffers.begin();
		it != m_Buffers.end();
		++it
		)
	{
		if( it->first == in_pBuffer )
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBUFFERMANAGER_H


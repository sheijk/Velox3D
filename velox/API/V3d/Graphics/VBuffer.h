#ifndef V3D_VBUFFER_H
#define V3D_VBUFFER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/** needed for VMeshDescription in some cases */
class VBufferBase
{
public:
	enum CopyMode
	{
		CopyData,
		DropData
	};

};

template<typename T>
struct IVBuffer : public VBufferBase
{
	/**
	 * returns the address of the first element. all elements have to be
	 * aligned linearly starting at this address (like an array)
	 */
	virtual T* GetDataAddress() = 0;
};

/**
 * An array like minmalistic container. Used for the graphics device
 * Owns it's memory region and deletes it on destruction
 *
 * @author sheijk
 */
template<typename DataType>
class VBuffer : public IVBuffer<DataType>
{
	/** the buffer's content */
	DataType* m_pBuffer;

	/** it's size */
	vuint m_nSize;

	// no copying
	void operator=(const VBuffer&);
	VBuffer(const VBuffer&);

public:
	/**
	 * Takes ownership of the given memory region
	 */
	VBuffer(DataType* in_pBuffer, vuint in_nSize)
	{
		m_pBuffer = in_pBuffer;
		m_nSize = in_nSize;
	}

	/**
	 * Delete's its assosiated memory region
	 */
	~VBuffer()
	{
		delete m_pBuffer;
		m_pBuffer = 0;
		m_nSize = 0;
	}

	/**
	 * Creates another buffer containing the same data like the existing one
	 * Buffers do not share memory, thus either the memory is copied or the
	 * source buffer looses it's memory
	 *
	 * @param in_Mode CopyData copies, DropData transfers ownership
	 */
	VBuffer<DataType>* CreateCopy(CopyMode in_Mode)
	{
		if( in_Mode == DropData )
		{
			VBuffer* buffer = new VBuffer(m_pBuffer, m_nSize);

			// loose data
			m_pBuffer = 0;
			m_nSize = 0;

			return buffer;
		}
		else
		{
			// copy data
            DataType* pNewData = new DataType[m_nSize];
			memcpy(pNewData, m_pBuffer, m_nSize * sizeof(DataType));

			return new VBuffer(pNewData, m_nSize);
		}
	}

	/**
	 * @return the number of elements of the buffer
	 */
	vuint GetSize() const
	{
		return m_nSize;
	}

	/**
	 * Accessor. Get the in_nIndex-th element. No bounds checking is done
	 *
	 * @param in_nIndex the number of the element
	 * @return reference to the element, can be set and read
	 */
	DataType& operator[](vuint in_nIndex)
	{
		return m_pBuffer[in_nIndex];
	}

	/** @see VBufferBase::GetDataAddress */
	virtual DataType* GetDataAddress()
	{
		return m_pBuffer;
	}

	template<typename DestType>
	VBuffer<DestType>* Convert(CopyMode in_CopyMode)
	{
		VBuffer<DestType>* pNewBuffer = 0;
		
		const vuint nSizeInBytes = m_nSize * sizeof(DataType);
		const vuint nDestSize = nSizeInBytes / sizeof(DestType);

		// only allow conversion if the size ..[aufgehen]
		if( nDestSize * sizeof(DestType) != nSizeInBytes )
		{
			V3D_THROW(VException, "type size mismatch");
		}
		
		if( in_CopyMode == DropData )
		{
			pNewBuffer = new VBuffer<DestType>(
				reinterpret_cast<DestType*>(m_pBuffer), 
				nDestSize
				);

			m_pBuffer = 0;
			m_nSize = 0;
		}
		else if( in_CopyMode == CopyData )
		{
			vbyte* pNewData = new vbyte[nSizeInBytes];
			memcpy(pNewData, m_pBuffer, nSizeInBytes);
            
			pNewBuffer = new VBuffer<DestType>(
				reinterpret_cast<DestType*>(pNewData), 
				nDestSize
				);
		}
		else
		{
			V3D_THROW(VException, "invalid copy mode");
		}
		
		return pNewBuffer;
	}
};

/** a buffer of floats */
typedef VBuffer<vfloat32> VFloatBuffer;
/** a buffer of ints */
typedef VBuffer<vuint32> VIntBuffer;
/** a buffer of bytes */
typedef VBuffer<vbyte> VByteBuffer;

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBUFFER_H

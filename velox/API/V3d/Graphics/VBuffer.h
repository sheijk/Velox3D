#ifndef V3D_VBUFFER_H
#define V3D_VBUFFER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/** needed for VMeshDescription in some cases */
class VBufferBase {};

template<typename T>
struct IVBuffer : public VBufferBase
{
	virtual T* GetDataAddress() = 0;
};

/**
 * A buffer for ints/floats/..
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
	VBuffer(DataType* in_pBuffer, vuint in_nSize)
	{
		m_pBuffer = in_pBuffer;
		m_nSize = in_nSize;
	}

	~VBuffer()
	{
		delete m_pBuffer;
		m_pBuffer = 0;
		m_nSize = 0;
	}

	enum CopyMode
	{
		CopyData,
		DropData
	};

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

	vuint GetSize() const
	{
		return m_nSize;
	}

	DataType& operator[](vuint in_nIndex)
	{
		return m_pBuffer[in_nIndex];
	}

	virtual DataType* GetDataAddress()
	{
		return m_pBuffer;
	}
};

typedef VBuffer<vfloat32> VFloatBuffer;
typedef VBuffer<vint32> VIntBuffer;
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBUFFER_H

#include <V3d/Graphics/VVertexBuffer.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

//VVertexBuffer::VVertexBuffer(vuint m_nSizeInBytes, VVertexFormat in_Format)
//	:
//	m_VertexData(new vbyte[m_nSizeInBytes], m_nSizeInBytes),
//	m_Format(in_Format)
//{
//}

VVertexBuffer::VVertexBuffer(const VByteBuffer& in_Data, VVertexFormat in_Format)
	:
	// we can safely cast to non const because the VByteBuffer c'tor will not
	// change it's source buffer if called with CopyData
	m_VertexData(const_cast<VByteBuffer*>(&in_Data), VByteBuffer::CopyData),
	m_Format(in_Format)
{
}

namespace 
{
	vfloat32* CreateCopy(const vfloat32* in_pSource, vuint in_nSize)
	{
		vfloat32* pNew = new vfloat32[in_nSize];
		memcpy(pNew, in_pSource, in_nSize * sizeof(vfloat32));

		return pNew;
	}
}

VVertexBuffer::VVertexBuffer(const vfloat32* in_pData, vuint in_nFloatCount, VVertexFormat in_Format)
	: 
	m_VertexData(reinterpret_cast<vbyte*>(CreateCopy(in_pData, in_nFloatCount)), in_nFloatCount * sizeof(vfloat32)),
	m_Format(in_Format)
{
}

VVertexBuffer::~VVertexBuffer()
{
}

const VVertexFormat& VVertexBuffer::GetFormat() const
{
	return m_Format;
}

const vbyte* VVertexBuffer::GetBufferAddress() const
{
	return m_VertexData.GetDataAddress();
}

vuint VVertexBuffer::GetBufferSize() const
{
	return m_VertexData.GetSize();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Graphics/VVertexBuffer.h>
//-----------------------------------------------------------------------------
#include <V3d/Graphics/Geometry/VVertex3f.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
#include <V3d/Graphics/Geometry/VNormal3f.h>
#include <V3d/Graphics/Geometry/VTexCoord2f.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace math;

namespace 
{
	vfloat32* CreateCopy(const vfloat32* in_pSource, vuint in_nSize)
	{
		vfloat32* pNew = new vfloat32[in_nSize];
		memcpy(pNew, in_pSource, in_nSize * sizeof(vfloat32));

		return pNew;
	}

	vuint* CreateCopy(const vuint* in_pSource, vuint in_nSize)
	{
		vuint* pNew = new vuint[in_nSize];
		memcpy(pNew, in_pSource, in_nSize * sizeof(vfloat32));

		return pNew;
	}

	vuint GetIndexOfEnd(const VDataFormat& in_Format)
	{
		vuint length = in_Format.GetCount() * in_Format.GetStride();
		return (in_Format.GetFirstIndex() + length) * 4;
	}

	vuint GetRequiredSize(const VVertexFormat& in_Format)
	{
		using std::max;

		vuint size = 0;

		size = max(size, GetIndexOfEnd(in_Format.GetCoordinateFormat()));
		size = max(size, GetIndexOfEnd(in_Format.GetColorFormat()));
		size = max(size, GetIndexOfEnd(in_Format.GetNormalFormat()));
		size = max(size, GetIndexOfEnd(in_Format.GetIndexFormat()));

		for(vuint texCoordNum = 0; 
			texCoordNum < in_Format.GetTexCoordCount();
			++texCoordNum)
		{
			size = max(size, GetIndexOfEnd(in_Format.GetTexCoordFormat(texCoordNum)));
		}

		return size;
	}

}

//-----------------------------------------------------------------------------

VVertexBuffer::VVertexBuffer(const VByteBuffer& in_Data, VVertexFormat in_Format)
	:
	// we can safely cast to non const because the VByteBuffer c'tor will not
	// change it's source buffer if called with CopyData
	m_VertexData(const_cast<VByteBuffer*>(&in_Data), VByteBuffer::CopyData),
	m_Format(in_Format),
	m_nVertexCount(GetVertexCount(in_Format))
{
	V3D_ASSERT(GetRequiredSize(in_Format) <= m_VertexData.GetSize());
}

VVertexBuffer::VVertexBuffer(const vfloat32* in_pData, vuint in_nFloatCount, VVertexFormat in_Format)
	: 
	m_VertexData(reinterpret_cast<vbyte*>(CreateCopy(in_pData, in_nFloatCount)), in_nFloatCount * sizeof(vfloat32)),
	m_Format(in_Format),
	m_nVertexCount(GetVertexCount(in_Format))
{
	V3D_ASSERT(GetRequiredSize(in_Format) <= m_VertexData.GetSize());
}

VVertexBuffer::VVertexBuffer(const vuint* in_pData, vuint in_nIntCount, VVertexFormat in_Format)
	:
	m_VertexData(reinterpret_cast<vbyte*>(CreateCopy(in_pData, in_nIntCount)), in_nIntCount * sizeof(vuint)),
	m_Format(in_Format),
	m_nVertexCount(GetVertexCount(in_Format))
{
	V3D_ASSERT(GetRequiredSize(in_Format) <= m_VertexData.GetSize());
}

VVertexBuffer::VVertexBuffer(const VVertexFormat& in_Format)
	:
	m_Format(in_Format),
	m_VertexData(new vbyte[GetRequiredSize(in_Format)], GetRequiredSize(in_Format)),
	m_nVertexCount(GetVertexCount(in_Format))
{
	V3D_ASSERT(GetRequiredSize(in_Format) <= m_VertexData.GetSize());
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
template<typename T>
void SetElement(
	VByteBuffer& in_Buffer, 
	const VDataFormat& in_Format, 
	vuint in_nPos,
	const T& in_Value)
{
	vuint offset = in_Format.GetOffset(in_nPos) * sizeof(vfloat32);
	
	V3D_ASSERT(offset >= 0);
	V3D_ASSERT(offset + sizeof(T) <= in_Buffer.GetSize());

	T* pValue = reinterpret_cast<T*>(in_Buffer.GetDataAddress()+offset);
	*pValue = in_Value;
}

template<typename T>
const T* GetElementAddress(
	const VByteBuffer& in_Buffer, 
	const VDataFormat& in_Format, 
	vuint in_nPos)
{
	vuint offset = in_Format.GetOffset(in_nPos) * sizeof(vfloat32);

	V3D_ASSERT(offset + sizeof(T) <= in_Buffer.GetSize());

	return reinterpret_cast<const T*>(in_Buffer.GetDataAddress() + offset);
}

const VVertex3f& VVertexBuffer::GetCoordinate(vuint in_nVertexNum) const
{
	return *GetElementAddress<VVertex3f>(
		m_VertexData, m_Format.GetCoordinateFormat(), in_nVertexNum);
}

void VVertexBuffer::SetCoordinate(const VVertex3f& in_Coord, vuint in_nVertexNum)
{
	SetElement(m_VertexData, m_Format.GetCoordinateFormat(), in_nVertexNum, in_Coord);
}

void VVertexBuffer::SetCoordinate(const VVector3f& in_Coord, vuint in_nVertexNum)
{
	VVertex3f vec(in_Coord.GetX(), in_Coord.GetY(), in_Coord.GetZ());
	SetCoordinate(vec, in_nVertexNum);
}

const VColor4f& VVertexBuffer::GetColor(vuint in_nVertexNum) const
{
	return *GetElementAddress<VColor4f>(
		m_VertexData, m_Format.GetColorFormat(), in_nVertexNum);
}

void VVertexBuffer::SetColor(const VColor4f& in_Color, vuint in_nVertexNum)
{
	SetElement(m_VertexData, m_Format.GetColorFormat(), in_nVertexNum, in_Color);
}

const VNormal3f& VVertexBuffer::GetNormal(vuint in_nVertexNum) const
{
	return *GetElementAddress<VNormal3f>(
		m_VertexData, m_Format.GetNormalFormat(), in_nVertexNum);
}

void VVertexBuffer::SetNormal(const VNormal3f& in_Normal, vuint in_nVertexNum)
{
	SetElement(m_VertexData, m_Format.GetNormalFormat(), in_nVertexNum, in_Normal);
}

const VTexCoord2f& VVertexBuffer::GetTexCoord(vuint in_nTexCoordNum, vuint in_nVertexNum) const
{
	V3D_ASSERT(in_nTexCoordNum < m_Format.GetTexCoordCount());

	return *GetElementAddress<VTexCoord2f>(
		m_VertexData, m_Format.GetTexCoordFormat(in_nTexCoordNum), in_nVertexNum);
}

void VVertexBuffer::SetTexCoord(vuint in_nTexCoordNum, vuint in_nVertexNum, 
								const VTexCoord2f& in_TexCoord)
{
	V3D_ASSERT(in_nTexCoordNum < m_Format.GetTexCoordCount());

	SetElement(m_VertexData, m_Format.GetTexCoordFormat(in_nTexCoordNum),
		in_nVertexNum, in_TexCoord);
}

vuint VVertexBuffer::GetIndex(vuint in_nIndexNum) const
{
	return *GetElementAddress<vuint>(
		m_VertexData, m_Format.GetIndexFormat(), in_nIndexNum);
}

void VVertexBuffer::SetIndex(vuint in_nIndex, vuint in_nIndexNum)
{
	//V3D_ASSERT(in_nIndex < m_nVertexCount);
	SetElement(m_VertexData, m_Format.GetIndexFormat(), in_nIndexNum, in_nIndex);
}

vuint VVertexBuffer::GetVertexCount(const VVertexFormat& in_Format)
{
	vuint size = in_Format.GetCoordinateFormat().GetCount();
	size = std::max(size, in_Format.GetColorFormat().GetCount());
	size = std::max(size, in_Format.GetNormalFormat().GetCount());

	for(vuint texCoordNum = 0; texCoordNum < in_Format.GetTexCoordCount(); ++texCoordNum)
	{
		size = std::max(size, in_Format.GetTexCoordFormat(texCoordNum).GetCount());
	}

	return size;
}

vuint VVertexBuffer::GetIndexCount() const
{
	return GetFormat().GetIndexFormat().GetCount();
}

vuint VVertexBuffer::GetCoordinateCount() const
{
	return GetFormat().GetCoordinateFormat().GetCount();
}

vuint VVertexBuffer::GetColorCount() const
{
	return GetFormat().GetColorFormat().GetCount();
}

vuint VVertexBuffer::GetNormalCount() const
{
	return GetFormat().GetNormalFormat().GetCount();
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------


#ifndef V3D_VVERTEXBUFFER_2005_02_02_H
#define V3D_VVERTEXBUFFER_2005_02_02_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>

#include <V3d/Math/VVector.h>
#include <V3d/Graphics/VVertexFormat.h>
#include <V3d/Graphics/VBuffer.h>
#include <V3d/Graphics/VVertexFormat.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

struct VVertex3f;
struct VColor4f;
struct VTexCoord2f;
struct VNormal3f;

/**
 * @author sheijk
 */
class VVertexBuffer
{
public:
//	VVertexBuffer(vuint m_nSizeInBytes, VVertexFormat in_Format);
	VVertexBuffer(const VByteBuffer& in_Data, VVertexFormat in_Format);
	VVertexBuffer(const vfloat32* in_pData, vuint in_nFloatCount, VVertexFormat in_Format);
	VVertexBuffer(const vuint* in_pData, vuint in_nIntCount, VVertexFormat in_Format);
	explicit VVertexBuffer(const VVertexFormat& in_Format);

	template<typename DataType>
	VVertexBuffer(const VBuffer<DataType>& in_Data, VVertexFormat in_Format);

	virtual ~VVertexBuffer();

	const VVertexFormat& GetFormat() const;
	const vbyte* GetBufferAddress() const;
	vuint GetBufferSize() const;

	// accessor functions for vertex data
	const VVertex3f& GetCoordinate(vuint in_nVertexNum) const;
	void SetCoordinate(const VVertex3f& in_Coord, vuint in_nVertexNum);
	void SetCoordinate(const VVector3f& in_Coord, vuint in_nVertexNum);

	const VColor4f& GetColor(vuint in_nVertexNum) const;
	void SetColor(const VColor4f& in_Color, vuint in_nVertexNum);

	const VNormal3f& GetNormal(vuint in_nVertexNum) const;
	void SetNormal(const VNormal3f& in_Normal, vuint in_nVertexNum);

	const VTexCoord2f& GetTexCoord(
		vuint in_nTexCoordNum, vuint in_nVertexNum) const;
	void SetTexCoord(vuint in_nTexCoordNum, vuint in_nVertexNum, 
		const VTexCoord2f& in_TexCoord);

	vuint GetIndex(vuint in_nIndexNum) const;
	void SetIndex(vuint in_nVertexIndex, vuint in_nIndexNum);

private:
	vuint GetVertexCount(const VVertexFormat& in_Format);

	const vuint m_nVertexCount;
	VVertexFormat m_Format;
	VByteBuffer m_VertexData;
};

//-----------------------------------------------------------------------------

template<typename DataType>
VVertexBuffer::VVertexBuffer(
	const VBuffer<DataType>& in_Data, 
	VVertexFormat in_Format)
	:
	m_Format(in_Format),
	m_VertexData(in_Data),
	m_nVertexCount(GetVertexCount(in_Format))
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics

V3D_TYPEINFO(v3d::graphics::VVertexBuffer);

//-----------------------------------------------------------------------------
#endif // V3D_VVERTEXBUFFER_2005_02_02_H

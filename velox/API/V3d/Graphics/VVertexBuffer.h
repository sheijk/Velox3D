#ifndef V3D_VVERTEXBUFFER_2005_02_02_H
#define V3D_VVERTEXBUFFER_2005_02_02_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Graphics/VVertexFormat.h>
#include <V3d/Graphics/VBuffer.h>
#include <V3d/Graphics/VVertexFormat.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VVertexBuffer
{
public:
//	VVertexBuffer(vuint m_nSizeInBytes, VVertexFormat in_Format);
	VVertexBuffer(const VByteBuffer& in_Data, VVertexFormat in_Format);
	VVertexBuffer(const vfloat32* in_pData, vuint in_nFloatCount, VVertexFormat in_Format);

	virtual ~VVertexBuffer();

	const VVertexFormat& GetFormat() const;
	const vbyte* GetBufferAddress() const;
	vuint GetBufferSize() const;

private:
	VVertexFormat m_Format;
	VByteBuffer m_VertexData;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VVERTEXBUFFER_2005_02_02_H

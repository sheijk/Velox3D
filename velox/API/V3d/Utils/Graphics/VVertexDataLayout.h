#ifndef V3D_VVERTEXDATALAYOUT_H
#define V3D_VVERTEXDATALAYOUT_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Describes the layout of a VertexData structure in memory.
 * VertexData structures must follow the following rules:
 * - public static member VVertexDataLayout layout.
 * - reserved members: VVertex3f vertex, VColor4f color, VTexCoord2f texCoord
 */
struct VVertexDataLayout
{
	typedef vint Offset;

	Offset vertexOffset;
	Offset colorOffset;

	VVertexDataLayout()
	{
		vertexOffset = -1;
		colorOffset = -1;
	}

	static vbool IsValidOffset(Offset offs);

	template<typename VertexData>
	static void SetVertexOffset();

	template<typename VertexData>
	static void SetColorOffset();
};

vbool VVertexDataLayout::IsValidOffset(Offset offs)
{
	return offs >= 0;
}

template<typename VertexData>
void VVertexDataLayout::SetVertexOffset()
{
	VertexData* zero = 0;

	typedef VVertexDataLayout::Offset Offset;

	VertexData::layout.vertexOffset = 
		reinterpret_cast<Offset>(&(zero->vertex)) / sizeof(float);
}

template<typename VertexData>
void VVertexDataLayout::SetColorOffset()
{
	VertexData* zero = 0;

	typedef VVertexDataLayout::Offset Offset;

	VertexData::layout.colorOffset = 
		reinterpret_cast<Offset>(&(zero->color)) / sizeof(float);
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VVERTEXDATALAYOUT_H

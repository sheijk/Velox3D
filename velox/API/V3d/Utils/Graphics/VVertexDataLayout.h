#ifndef V3D_VVERTEXDATALAYOUT_H
#define V3D_VVERTEXDATALAYOUT_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Describes the layout of a VertexData structure in memory.
 * VertexData structures must follow the following rules:
 * - public static member VVertexDataLayout layout.
 * - reserved members: VVertex3f position, VColor4f color, VTexCoord2f texCoords
 */
struct VVertexDataLayout
{
	typedef vint Offset;

	Offset positionOffset;
	Offset colorOffset;
	Offset texCoordOffset;

	VVertexDataLayout()
	{
		positionOffset = -1;
		colorOffset = -1;
		texCoordOffset = -1;
	}

	static vbool IsValidOffset(Offset offs);

	template<typename VertexData>
	static void SetPositionOffset();

	template<typename VertexData>
	static void SetColorOffset();

	template<typename VertexData>
	static void SetTexCoordOffset();
};

template<typename VertexData>
void VVertexDataLayout::SetPositionOffset()
{
	VertexData* zero = 0;

	typedef VVertexDataLayout::Offset Offset;

	VertexData::layout.positionOffset = 
		reinterpret_cast<Offset>(&(zero->position)) / sizeof(vfloat32);
}

template<typename VertexData>
void VVertexDataLayout::SetColorOffset()
{
	VertexData* zero = 0;

	typedef VVertexDataLayout::Offset Offset;

	VertexData::layout.colorOffset = 
		reinterpret_cast<Offset>(&(zero->color)) / sizeof(vfloat32);
}

template<typename VertexData>
void VVertexDataLayout::SetTexCoordOffset()
{
	VertexData* zero = 0;

	VertexData::layout.texCoordOffset =
		reinterpret_cast<Offset>(&(zero->texCoords)) / sizeof(vfloat32);
}


//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VVERTEXDATALAYOUT_H

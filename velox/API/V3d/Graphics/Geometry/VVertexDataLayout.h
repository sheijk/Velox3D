/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VVERTEXDATALAYOUT_H
#define V3D_VVERTEXDATALAYOUT_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Describes the layout of a VertexData structure in memory.
 *
 * Interpretation of offset values: An offset gives the number of floats to be
 * added to convert the address of the vertex structure to it's 
 * position/color/.. member.
 *
 * struct ExampleVertex
 * {
 *    ExampleVertex();
 *
 *    VVector3f position;
 *    VColor4f color;
 *    static VVertexDataLayout layout;
 * }
 *
 * ExampleVertex::ExampleVertex()
 * {
 *    VVertexDataLayout<ExampleVertex>::SetPositionOffset();
 *    VVertexDataLayout<ExampleVertex>::SetColorOffset();
 * }
 *
 * Would result in layout.positionOffset = 0 and layout.colorOffset = 3
 * 
 * VertexData structures must follow the following rules:
 * - public static member VVertexDataLayout layout.
 * - reserved members: VVertex3f position, VColor4f color, VTexCoord2f texCoords
 *
 * @author sheijk
 */
struct VVertexDataLayout
{
	typedef vint64 Offset;

	Offset positionOffset;
	Offset colorOffset;
	Offset texCoordOffset;
	Offset vertexSize;

	VVertexDataLayout()
	{
		positionOffset = -1;
		colorOffset = -1;
		texCoordOffset = -1;
	}

	/** 
	 * Returns true if the given value is a possible offset. Does not hint
	 * whether the offset is correct
	 */
	inline static vbool IsValidOffset(Offset offs);

	/**
	 * Sets VertexData::layout.vertexSize to sizeof(VertexData)
	 */
	template<typename VertexData>
	static void SetVertexSize();

	/**
	 * Sets VertexData::layout.positionOffset to the correct value
	 */
	template<typename VertexData>
	static void SetPositionOffset();

	/**
	* Sets VertexData::layout.colorOffset to the correct value
	*/
	template<typename VertexData>
	static void SetColorOffset();

	/**
	* Sets VertexData::layout.texCoordOffset to the correct value
	*/
	template<typename VertexData>
	static void SetTexCoordOffset();
};

vbool VVertexDataLayout::IsValidOffset(Offset offs)
{
	return offs >= 0;
}

template<typename VertexData>
void VVertexDataLayout::SetVertexSize()
{
	VertexData::layout.vertexSize = sizeof(VertexData);
}

template<typename VertexData>
void VVertexDataLayout::SetPositionOffset()
{
	VertexData* zero = 0;

	typedef VVertexDataLayout::Offset Offset;

	VertexData::layout.positionOffset = 
		reinterpret_cast<Offset>(&(zero->position)) / sizeof(vfloat32);

	SetVertexSize<VertexData>();
}

template<typename VertexData>
void VVertexDataLayout::SetColorOffset()
{
	VertexData* zero = 0;

	typedef VVertexDataLayout::Offset Offset;

	VertexData::layout.colorOffset = 
		reinterpret_cast<Offset>(&(zero->color)) / sizeof(vfloat32);

	SetVertexSize<VertexData>();
}

template<typename VertexData>
void VVertexDataLayout::SetTexCoordOffset()
{
	VertexData* zero = 0;

	VertexData::layout.texCoordOffset =
		reinterpret_cast<Offset>(&(zero->texCoords)) / sizeof(vfloat32);

	SetVertexSize<VertexData>();
}


//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VVERTEXDATALAYOUT_H


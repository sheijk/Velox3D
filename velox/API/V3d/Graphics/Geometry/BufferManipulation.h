/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_BUFFERMANIPULATION_H
#define V3D_BUFFERMANIPULATION_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics.h>
#include <V3d/Math/Numerics.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // and again..

/**
 * @author sheijk
 */
template<typename VertexStructure, typename Operation>
void ForEachVertex(VBuffer<VertexStructure>& buffer, Operation& op);

//-----------------------------------------------------------------------------

/**
 * @author sheijk
 */
template<typename VertexStructure>
class SetVertexColor //clash with SetColor in VModelLoader.cpp
{
	VColor4f color;
public:
	SetVertexColor(const VColor4f col) : color(col) {}
	SetVertexColor(vfloat32 red, vfloat32 green, vfloat32 blue, vfloat32 alpha = 1.0f)
		: color(VColor4f(red, green, blue, alpha))
	{}

    void operator()(VertexStructure& vertex)
	{
		vertex.color = color;
	}    
};
 /**
  * @author: ins
  */

template<typename VertexStructure>
class SetTexCoords
{
	VTexCoord2f tex;
public:
	SetTexCoords(vfloat32 u, vfloat32 v = 1.0f)
		: tex(VTexCoord2f(u, v)) {}

	SetTexCoords(const VTexCoord2f t) : tex(t) {}

	void operator()(VertexStructure& vertex)
	{
		vertex.texCoords = tex;
	}
};

template<typename VertexStructure>
class ScaleRandom
{
	vfloat32 m_fMin;
	vfloat32 m_fMax;

public:
	ScaleRandom(vfloat32 min, vfloat32 max) : m_fMin(min), m_fMax(max) {}

	void operator()(VertexStructure& vertex)
	{
		static int lastid = 0;

		vertex.position.x *= math::PseudoRandom(++lastid, m_fMin, m_fMax);
		vertex.position.y *= math::PseudoRandom(++lastid, m_fMin, m_fMax);
		vertex.position.z *= math::PseudoRandom(++lastid, m_fMin, m_fMax);
	}
};

/**
 * @author sheijk
 */
#define V3D_DECLARE_BUFFER_OP(opName, opLine) \
	template<typename VertexStructure>\
	class opName\
	{\
		float mx, my, mz;\
	public:\
		opName(float x, float y, float z) : mx(x), my(y), mz(z) {}\
        \
		void operator()(VertexStructure& vertex)\
		{\
			opLine;\
		}\
	};

V3D_DECLARE_BUFFER_OP(AddVertex, 
	vertex.position.x += mx;
	vertex.position.y += my;
	vertex.position.z += mz;
	);

V3D_DECLARE_BUFFER_OP(SubVertex,
	vertex.position.x -= mx;
	vertex.position.y -= my;
	vertex.position.z -= mz;
	);

V3D_DECLARE_BUFFER_OP(ScaleVertex,
	vertex.position.x *= mx;
	vertex.position.y *= my;
	vertex.position.z *= mz;
	);

V3D_DECLARE_BUFFER_OP(SetVertex,
	vertex.position.x = mx;
	vertex.position.y = my;
	vertex.position.z = mz;
	);

#undef V3D_DECLARE_BUFFER_OP

/**
 * @author sheijk
 */
template<typename VertexStructure>
void InverseX(VertexStructure& vertex);

/**
 * @author sheijk
 */
template<typename VertexStructure>
void InverseY(VertexStructure& vertex);

/**
 * @author sheijk
 */
template<typename VertexStructure>
void InverseZ(VertexStructure& vertex);

/**
 * @author sheijk
 */
template<typename VertexStructure>
void SwitchYZ(VertexStructure& vertex);

template<typename VertexStructure>
void MirrorTexCoordU(VertexStructure& vertex);

template<typename VertexStructure>
void MirrorTexCoordV(VertexStructure& vertex);

template<typename VertexStructure>
void SwitchTextCoordUV(VertexStructure& vertex);

//-----------------------------------------------------------------------------
#include "BufferManipulation.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_BUFFERMANIPULATION_H


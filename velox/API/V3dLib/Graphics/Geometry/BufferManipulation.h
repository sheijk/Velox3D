#ifndef V3D_BUFFERMANIPULATION_H
#define V3D_BUFFERMANIPULATION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics.h>

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
class SetColor
{
	VColor4f color;
public:
	SetColor(const VColor4f col) : color(col) {}
	SetColor(vfloat32 red, vfloat32 green, vfloat32 blue, vfloat32 alpha = 1.0f)
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

//-----------------------------------------------------------------------------
#include "BufferManipulation.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_BUFFERMANIPULATION_H

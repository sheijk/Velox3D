#ifndef V3D_VBOX_H
#define V3D_VBOX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Utils/Graphics/VVertex3f.h>
#include <v3d/Utils/Graphics/VTexCoord2f.h>
#include <v3d/Graphics/VBuffer.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
namespace graphics {

typedef v3d::graphics::VVertex3f VVector3f;

template<typename VertexStructure>
class VBox
{
	vfloat32	m_fHeight;
	vfloat32	m_fWidth;
	vfloat32	m_fDepth;

public:
	v3d::graphics::VBuffer<VertexStructure>	buffer;

	VBox( vfloat32 in_fHeight, vfloat32 in_fWidth, vfloat32 in_fDepth )
		: m_fHeight(in_fHeight), m_fWidth(in_fWidth), m_fDepth(in_fDepth), buffer(new VertexStructure[36], 36)
	{
	}

	~VBox() {};

	void	CreateCoordinates();
	void	CreateTextureCoordinates();
};

#include "VBox.inl"

}
}
}
//-----------------------------------------------------------------------------
#endif
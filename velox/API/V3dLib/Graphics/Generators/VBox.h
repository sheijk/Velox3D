#ifndef V3D_VBOX_H
#define V3D_VBOX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3dLib/Graphics/Geometry/VVector3f.h>
#include <V3dLib/Graphics/Geometry/VTexCoord2f.h>
#include <v3d/Graphics/VBuffer.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * @author AcrylSword
 */
template<typename VertexStructure>
class VBox
{
	vfloat32	m_fHeight;
	vfloat32	m_fWidth;
	vfloat32	m_fDepth;


public:
	VBuffer<VertexStructure>	buffer;

	VBuffer<VertexStructure>* GetVertexBuffer();
	

	VBox(vfloat32 in_fSize)
		: m_fHeight(in_fSize), m_fWidth(in_fSize), m_fDepth(in_fSize),
		buffer(new VertexStructure[36], 36)
	{
	}

	VBox( vfloat32 in_fHeight, vfloat32 in_fWidth, vfloat32 in_fDepth )
		: m_fHeight(in_fHeight), m_fWidth(in_fWidth), m_fDepth(in_fDepth), 
		buffer(new VertexStructure[36], 36)
	{
	}

	~VBox() {};

	void	CreateCoordinates();
	void	CreateTextureCoordinates();
};

#include "VBox.inl"

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif
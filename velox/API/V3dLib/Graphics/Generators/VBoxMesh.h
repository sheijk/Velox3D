#ifndef V3D_VBOXMESH_2004_05_04_H
#define V3D_VBOXMESH_2004_05_04_H
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
class VBoxMesh
{
	vfloat32	m_fHeight;
	vfloat32	m_fWidth;
	vfloat32	m_fDepth;


public:
	VBuffer<VertexStructure>	buffer;

	VBuffer<VertexStructure>* GetVertexBuffer();
	

	VBoxMesh(vfloat32 in_fSize)
		: m_fHeight(in_fSize), m_fWidth(in_fSize), m_fDepth(in_fSize),
		buffer(new VertexStructure[36], 36)
	{
	}

	VBoxMesh( vfloat32 in_fHeight, vfloat32 in_fWidth, vfloat32 in_fDepth )
		: m_fHeight(in_fHeight), m_fWidth(in_fWidth), m_fDepth(in_fDepth), 
		buffer(new VertexStructure[36], 36)
	{
	}

	~VBoxMesh() {};

	void	CreateCoordinates();
	void	CreateTextureCoordinates();
};

#include "VBoxMesh.inl"

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VBOXMESH_2004_05_04_H
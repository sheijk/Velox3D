#ifndef V3D_VHEIGHTMAP_H
#define V3D_VHEIGHTMAP_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Utils/Graphics/VVector3f.h>
#include <v3d/Utils/Graphics/VTexCoord2f.h>
#include <v3d/Utils/Graphics/VColor4f.h>
#include <v3d/Graphics/VBuffer.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
namespace graphics{
//-----------------------------------------------------------------------------

/**
 * Heightmap template creation class
 * Size is hardcoded because non 1024x1024 images would be hard to traversal
 * @author: ins
 */

template <typename VertexStructure>
class VHeightmap
{
public:

	VHeightmap(vbyte* in_pBuffer, vuint in_iWidth, vuint in_iHeight)
		: m_pBuffer(in_pBuffer), m_iWidth(in_iWidth), m_iHeight(in_iHeight),
		buffer(new VertexStructure[GetNumElements()], GetNumElements())
	{};
		  

	
	void CreateCoordinates();
	void CreateTextureCoordinates();
	
	
	v3d::graphics::VBuffer<VertexStructure>	buffer;

private:

	static vint GetNumElements();
	vint GetHeight(vint in_iX, vint in_iY);

	struct Triangle
	{
		VVector3f tri[3];

		Triangle()
		{
			tri[0] = VVector3f(0.0f, 0.0f, 0.0f);
			tri[1] = VVector3f(0.0f, 0.0f, 0.0f);
			tri[2] = VVector3f(0.0f, 0.0f, 0.0f);
		}

		Triangle( VVector3f a, VVector3f b, VVector3f c)
		{
			tri[0]=a;
			tri[1]=b;
			tri[2]=c;
		}
	};

	enum Heightmap
	{
		Size = 1024, // Size of our heightmap
		Stepsize = 16, // This is width and height of each QUAD
	};

	vbyte* m_pBuffer;
	vuint m_iWidth;
	vuint m_iHeight;

};

#include "VHeightmap.inl"
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VHEIGHTMAP_H

#ifndef V3D_VSKYDOMEBODY_2004_04_26_H
#define V3D_VSKYDOMEBODY_2004_04_26_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVDevice.h>
#include <v3d/Graphics/VBuffer.h>
#include <v3d/Image/IVImageFactory.h>
#include <V3dLib/Graphics/Geometry.h>
#include <V3dLib/Graphics/Generators.h>
#include "IVSkyBody.h"
/*
#include <V3dLib/Utils/Graphics/VTexCoord2f.h>
#include <V3dLib/Utils/Graphics/VVertexDataLayout.h>
#include <V3dLib/Utils/Graphics/VGeometryData.h>
*/
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
namespace sky {
	
using namespace v3d;
using namespace v3d::graphics;
using namespace v3d::graphics::sky;
using namespace v3d::image;
	
//-----------------------------------------------------------------------------
class VSkyDomeBody : public IVSkyBody
{
	struct SkyVertex
	{
		VVector3f position;
		VTexCoord2f texCoords;

		SkyVertex()
		{
			VVertexDataLayout::SetPositionOffset<SkyVertex>();
			VVertexDataLayout::SetTexCoordOffset<SkyVertex>();
		};

		static VVertexDataLayout layout;
	};

	vfloat32 m_fRadius;
	vfloat32 m_fScale;

	NodePointer				m_pNode;
	VMeshNode*				m_pMeshNode;

	VPolarSphere<SkyVertex> m_HalfSphere;
	
	IVDevice::MeshHandle	m_pMesh;
	VMaterialDescription	m_MaterialDescription;
	
	VStringParam			m_strImage;

	void					InverseIndexBuffer();
	void					CreateMesh(IVDevice& in_Device);
	void					CreateNode();

public:

	VSkyDomeBody(IVDevice& in_Device,
		 vfloat32 in_fRadius,
		 vfloat32 in_fScale,
		 vuint in_nDetail,
		 VStringParam in_strImage);

	~VSkyDomeBody();

	virtual IVNode* GetNode();
};


//-----------------------------------------------------------------------------
} // namespace sky
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSKYDOMEBODY_2004_04_26

#ifndef V3D_VSKYDOMEBODY_2004_04_26_H
#define V3D_VSKYDOMEBODY_2004_04_26_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVDevice.h>
#include <v3d/Graphics/VBuffer.h>
#include <V3dLib/Graphics/Geometry.h>
#include <V3dLib/Graphics/Generators.h>
#include <v3dLib/Graphics/Renderers/Sky/VDaylightSkyColorizer.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {

//-----------------------------------------------------------------------------
class VSkyDome
{
	struct SkyVertex
	{
		VVertex3f position;
		VColor4f color;
		VTexCoord2f texCoords;

		SkyVertex()
		{
			VVertexDataLayout::SetPositionOffset<SkyVertex>();
			VVertexDataLayout::SetColorOffset<SkyVertex>();
			VVertexDataLayout::SetTexCoordOffset<SkyVertex>();
		};

		static VVertexDataLayout layout;
	};

	vfloat32 m_fRadius;
	vfloat32 m_fScale;
    vuint	m_nDetail;

	VPolarSphereMesh<SkyVertex> m_HalfSphere;

	VDaylightSkyColorizer m_Colorizer;

	//VGeometryData<SkyVertex> m_Geometry;

	vfloat32 m_fZenith;
	
	IVDevice::MeshHandle	m_pMesh;
	VMaterialDescription	m_MaterialDescription;
	VMaterialDescription::TextureRef* m_pTexRef;
	
	VStringParam			m_strImage;

	void					InverseIndexBuffer();
	vuint					GetVertexNum(vuint sector, vuint ring);
	void 					CreateTextureRef(IVDevice& in_Device);
	void					CreateMesh(IVDevice& in_Device);
	void		Colorize();
	void		Texturize();

public:

	VSkyDome(IVDevice& in_Device,
		 vfloat32 in_fRadius,
		 vfloat32 in_fScale,
		 vuint in_nDetail,
		 VStringParam in_strImage);

	~VSkyDome();

	virtual IVDevice::MeshHandle GetMesh();
};


//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSKYDOMEBODY_2004_04_26

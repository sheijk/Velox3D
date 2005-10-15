#ifndef V3D_VPOLARSPHEREGENERATOR_2005_09_07_H
#define V3D_VPOLARSPHEREGENERATOR_2005_09_07_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/VVertexBuffer.h>
#include <V3dLib/Graphics/Generators/IVMeshGenerator.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VPolarSphereGenerator : public IVMeshGenerator
{
public:
	VPolarSphereGenerator(
		VVertexFormat::DataTypes in_DataTypes,
		vuint in_nRings, vuint in_nSectors,
		vfloat32 in_fSize = 1.0f);

	VPolarSphereGenerator(
		VVertexFormat::DataTypes in_DataTypes,
		vuint in_nRings, vuint in_nSectors, 
		vfloat32 in_fBottom, vfloat32 in_fTop,
		vfloat32 in_fSize = 1.0f);

	virtual ~VPolarSphereGenerator();

	virtual VVertexBuffer* CreateVertexBuffer() const;
	virtual VVertexBuffer* CreateIndexBuffer() const;
	virtual VMeshDescription::GeometryType GetGeometryType() const;

private:
	vuint GetVertexNum(vuint sector, vuint ring) const;

	vuint CalculateVertexCount() const;
	vuint CalculateIndexCount() const;

    void GenerateIndices(VVertexBuffer* io_pVB) const;
	void GenerateCoordinates(VVertexBuffer* io_pVB) const;
	void GenerateTexCoords(VVertexBuffer* io_pVB) const;
	
	VVertexFormat m_Format;
	vfloat32 m_fTop;
	vfloat32 m_fBottom;
	vuint m_nRings;
	vuint m_nSectors;
	vfloat32 m_fSize;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics

V3D_TYPEINFO_WITHPARENT(
	v3d::graphics::VPolarSphereGenerator,
	v3d::graphics::IVMeshGenerator);

//-----------------------------------------------------------------------------
#endif // V3D_VPOLARSPHEREGENERATOR_2005_09_07_H

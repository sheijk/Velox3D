#ifndef V3D_VTERRAINPART_2005_12_07_H
#define V3D_VTERRAINPART_2005_12_07_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Resource.h>
#include <V3d/Graphics.h>
#include <V3d/Scene/VMeshPartBase.h>
#include <V3dLib/Containers/VArray2d.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VTerrainPart : public VMeshPartBase
{
public:
	VTerrainPart();
	virtual ~VTerrainPart();

	virtual void SendGeometry(graphics::IVDevice& in_Device) const;

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	vuint GetVertexCount() const;
	vuint GetIndexCount() const;
	vuint GetVertexNum(vuint x, vuint y) const;

	void SetVertexCount(vuint in_nWidth, vuint in_nHeigth);

	void ApplyHeightValues(const VArray2d<vfloat32>& in_Array);

	void GenerateIndices();
	void GenerateVertices();
	void GenerateNormals();

	VVector3f GetVertexAt(vuint x, vuint y);

	resource::VResourceDataPtr<graphics::VVertexBuffer> m_hVertexBuffer;
	resource::VResourceDataPtr<graphics::VVertexBuffer> m_hIndexBuffer;	
	resource::VResourceDataPtr<const graphics::IVMesh> m_hMesh;

	vuint m_nVertexCountHor;
	vuint m_nVertexCountVert;
	VVector2f m_XZMin;
	VVector2f m_XZMax;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VTerrainPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VTERRAINPART_2005_12_07_H
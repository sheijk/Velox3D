/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VTERRAINPART_2005_12_07_H
#define V3D_VTERRAINPART_2005_12_07_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Resource.h>
#include <V3d/Graphics.h>
#include <V3d/Scene/VMeshPartBase.h>
#include <V3d/Core/Container/VArray2d.h>
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

	//changed here from private to public for racer demo --ins
	resource::VResourceDataPtr<graphics::VVertexBuffer> GetVertexBuffer();
	vuint GetVertexCount() const;
	resource::VResourceDataPtr<graphics::VVertexBuffer> GetIndexBuffer();
	vuint GetIndexCount() const;

protected:
	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);

private:
	vuint GetVertexNum(vuint x, vuint y) const;

	void SetVertexCount(vuint in_nWidth, vuint in_nHeigth);

	void ApplyHeightValues(const VArray2d<vfloat32>& in_Array);

	void GenerateIndices();
	void GenerateVertices();
	void GenerateNormals();

	math::VVector3f GetVertexAt(vuint x, vuint y);

	vuint GetResolution() const;
	void SetResolution(const vuint& in_nNewCount);

	void SetHeightScale(const vfloat32& in_NewHeightScale);
	vfloat32 GetHeightScale() const;

	resource::VResourceDataPtr<graphics::VVertexBuffer> m_hVertexBuffer;
	resource::VResourceDataPtr<graphics::VVertexBuffer> m_hIndexBuffer;	
	resource::VResourceDataPtr<const graphics::IVMesh> m_hMesh;

	vuint m_nVertexCountHor;
	vuint m_nVertexCountVert;

	math::VVector2f GetExtent() const;
	void SetExtent(const math::VVector2f& in_Extent);

	math::VVector2f m_XZMin;
	math::VVector2f m_XZMax;

	vfloat32 m_fHeightScale;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VTerrainPart, v3d::entity::IVPart);
//-----------------------------------------------------------------------------
#endif // V3D_VTERRAINPART_2005_12_07_H


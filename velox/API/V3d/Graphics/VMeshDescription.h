/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMESHDESCRIPTION_H
#define V3D_VMESHDESCRIPTION_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>

#include <V3d/Graphics/VBuffer.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Graphics/VVertexFormat.h>

#include <V3d/Resource/VResourceId.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // kill auto indent

/**
 * Describes which data to use for a mesh and how to interprete it
 * Requires that all used data is already loaded into the mesh
 *
 * @author sheijk
 */
class VMeshDescription : public VVertexFormat
{
public:
	//typedef IVDevice::BufferHandle BufferHandle;

	enum GeometryType
	{
		Triangles,
		TriangleStrip,
		TriangleFan,
		Quads,
		QuadStrip,
		Lines,
		LineStrip,
		Points
	};

	VMeshDescription();
	virtual ~VMeshDescription();

	VMeshDescription(const VVertexFormat& in_Format);
	VMeshDescription(const VMeshDescription& in_Source);

	GeometryType GetGeometryType() const;
	void SetGeometryType(GeometryType in_GeometryType);

	std::string GetCoordinateResource() const;
	void SetCoordinateResource(const std::string& in_Id);

	void SetColorResource(const std::string& in_Id);
	std::string GetColorResource() const;

	void SetNormalResource(const std::string& in_Id);
	std::string GetNormalResource() const;

	void SetIndexResource(const std::string& in_Id);
	std::string GetIndexResource() const;

	void SetTexCoordResource(vuint in_nIndex, const std::string& in_Id);
	std::string GetTexCoordResource(vuint in_nCoord) const;

protected:
	virtual void SetTexCoordCount(vuint in_nNewCount);

private:
	struct DataRef
	{
		std::string resource;
	};

	void SetMinTexCoords(vuint in_nCoordCount);
	//static void Replace(
	//	DataRef& io_Ref, 
	//	BufferHandle in_hOldBuffer, 
	//	BufferHandle in_hNewBuffer);

	/** The type of primitives to be used for rendering */
	GeometryType m_GeometryType;

	DataRef m_Vertices;
	DataRef m_Colors;
	DataRef m_Normals;
	DataRef m_Indices;
	std::vector<DataRef> m_TexCoords;

	//TODO: normals, custom data(?)
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d

V3D_TYPEINFO(v3d::graphics::VMeshDescription);
//-----------------------------------------------------------------------------
#endif // V3D_VMESHDESCRIPTION_H


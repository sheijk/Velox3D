#ifndef V3D_VMESHDESCRIPTION_H
#define V3D_VMESHDESCRIPTION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VBuffer.h>
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
	typedef IVDevice::BufferHandle BufferHandle;

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

	VMeshDescription() : m_GeometryType(Triangles) 
	{
		SetTexCoordCount(1);
	}

	GeometryType GetGeometryType() const;
	void SetGeometryType(GeometryType in_GeometryType);

	std::string GetCoordinateResource() const;
	void SetCoordinateResource(const std::string& in_Id);

	void SetColorResource(const std::string& in_Id);
	std::string GetColorResource() const;

	void SetIndexResource(const std::string& in_Id);
	std::string GetIndexResource() const;

	void SetTexCoordResource(vuint in_nIndex, const std::string& in_Id);
	std::string GetTexCoordResource(vuint in_nCoord) const;

	// old, to be thrown out
	void SetCoordinateData(BufferHandle in_hBuffer, VDataFormat in_Format);
	BufferHandle GetCoordinateBuffer() const;

	void SetColorData(BufferHandle in_hBuffer, VDataFormat in_Format);
	BufferHandle GetColorBuffer() const;
	
	void SetIndexData(BufferHandle in_hBuffer, VDataFormat in_Format);
	BufferHandle GetIndexBuffer() const;

	void SetTexCoordData(vuint in_nCoord, BufferHandle in_hBuffer, VDataFormat in_Format);
	BufferHandle GetTexCoordBuffer(vuint in_nCoord) const;

	// some util functions

	/** replace each buffer equal to old buffer by new buffer */
	void ReplaceBuffer(BufferHandle in_hOldBuffer, BufferHandle in_hNewBuffer);

	/** get all buffers (for operations on all buffers) */
	std::vector<BufferHandle> GetAllBuffers() const;

protected:
	virtual void SetTexCoordCount(vuint in_nNewCount);

private:
	struct DataRef
	{
		BufferHandle hBuffer;
		std::string resource;

		DataRef();
	};

	void SetMinTexCoords(vuint in_nCoordCount);
	static void Replace(
		DataRef& io_Ref, 
		BufferHandle in_hOldBuffer, 
		BufferHandle in_hNewBuffer);

	/** The type of primitives to be used for rendering */
	GeometryType m_GeometryType;

	DataRef m_Vertices;
	DataRef m_Colors;
	DataRef m_Indices;
	std::vector<DataRef> m_TexCoords;

	//TODO: normals, custom data(?)
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMESHDESCRIPTION_H

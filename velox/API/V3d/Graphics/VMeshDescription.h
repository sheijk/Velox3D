#ifndef V3D_VMESHDESCRIPTION_H
#define V3D_VMESHDESCRIPTION_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VBuffer.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Resource/VResourceId.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // kill auto indent

/**
 * Specifies the data format of some data within an interleaved buffer
 * At FirstIndex-th byte come Count element every Stride bytes
 * 
 * @author sheijk
 */
class VDataFormat
{
	vuint m_nFirstIndex;
	vuint m_nCount;
	vuint m_nStride;

public:
	VDataFormat() : m_nStride(0), m_nFirstIndex(0), m_nCount(0) {}

	VDataFormat(vuint first, vuint count, vuint stride) :
		m_nFirstIndex(first), m_nCount(count), m_nStride(stride) {}

	vuint GetFirstIndex()	{ return m_nFirstIndex; }
	vuint GetCount()		{ return m_nCount; }
	vuint GetStride()		{ return m_nStride; }

	void SetFirstIndex(vuint f)	{ m_nFirstIndex = f; }
	void SetCount(vuint c)		{ m_nCount = c; }
	void SetStride(vuint s)		{ m_nStride = s; }
};

/**
 * Describes which data to use for a mesh and how to interprete it
 * Requires that all used data is already loaded into the mesh
 *
 * @author sheijk
 */
class VMeshDescription
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
		m_TexCoords.resize(1);
	}

	GeometryType GetGeometryType() const;
	void SetGeometryType(GeometryType in_GeometryType);

	// new
	VDataFormat GetCoordinateFormat() const;
	void SetCoordinateFormat(VDataFormat in_Format);
	std::string GetCoordinateResource() const;
	void SetCoordinateResource(const std::string& in_Id);

	VDataFormat GetColorFormat() const;
	void SetColorFormat(VDataFormat in_Format);
	void SetColorResource(const std::string& in_Id);
	std::string GetColorResource() const;

	VDataFormat GetIndexFormat() const;
	void SetIndexFormat(VDataFormat in_Format);
	void SetIndexResource(const std::string& in_Id);
	std::string GetIndexResource() const;

	vuint GetTexCoordCount() const;
	VDataFormat GetTexCoordFormat(vuint in_nCoord) const;
	void SetTexCoordFormat(vuint in_nCoord, VDataFormat in_Format);
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

private:
	struct DataRef
	{
		BufferHandle hBuffer;
		VDataFormat format;
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

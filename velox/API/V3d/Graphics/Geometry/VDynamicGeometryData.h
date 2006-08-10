#ifndef V3D_VDYNAMICGEOMETRYDATA_2004_04_09_H
#define V3D_VDYNAMICGEOMETRYDATA_2004_04_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/VMeshDescription.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Contains geometry data, like VGeometryData, but vertex and index buffers
 * may be resized by derived classes
 *
 * @author sheijk
 */
template<typename VertexStructure>
class VDynamicGeometryData
{
public:
	typedef VBuffer<VertexStructure> VertexBuffer;
	typedef VBuffer<vuint> IndexBuffer;

	VDynamicGeometryData()
	{
		m_GeometryType = VMeshDescription::Triangles;
		ResizeVertexBuffer(0);
		ResizeIndexBuffer(0);
	}

	VMeshDescription::GeometryType GetGeometryType() const
	{
		return m_GeometryType;
	}

	VertexBuffer& GetVertexBuffer()
	{
		return *m_pVertexBuffer;
	}

	IndexBuffer& GetIndexBuffer()
	{
		return *m_pIndexBuffer;
	}

	const VertexBuffer& GetVertexBuffer() const
	{
		return *m_pVertexBuffer;
	}

	const IndexBuffer& GetIndexBuffer() const
	{
		return *m_pIndexBuffer;
	}

	void SetGeometryType(VMeshDescription::GeometryType in_Type)
	{
		m_GeometryType = in_Type;
	}


protected:
	void ResizeVertexBuffer(vuint in_nSize)
	{
		m_pVertexBuffer.Assign(new VertexBuffer(
			new VertexStructure[in_nSize], in_nSize));
	}

	void ResizeIndexBuffer(vuint in_nSize)
	{
		m_pIndexBuffer.Assign(new IndexBuffer(new vuint[in_nSize], in_nSize));

	}

	
private:
	VMeshDescription::GeometryType m_GeometryType;

	typename VPointer<VertexBuffer>::SharedPtr m_pVertexBuffer;
	typename VPointer<IndexBuffer>::SharedPtr m_pIndexBuffer;
};


//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDYNAMICGEOMETRYDATA_2004_04_09_H

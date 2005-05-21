#ifndef V3D_VSTREAMMESH_2005_02_03_H
#define V3D_VSTREAMMESH_2005_02_03_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Resource.h>

#include <V3d/OpenGL.h>

#include <V3d/Graphics/VVertexBuffer.h>
#include "IVVertexStream.h"
#include "../DeviceBase/VMeshBase.h"
#include <v3d/Graphics/VMeshDescription.h>

#include <memory>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Renders a mesh using open gl vertex streams
 *
 * @author sheijk
 */
class VStreamMesh : public VMeshBase
{
public:
	VStreamMesh(
		//std::vector<IVMaterial*> in_Materials,
		const VMeshDescription& in_MeshDescription
		);

	virtual ~VStreamMesh();

	virtual void Render() const;

private:
	typedef resource::VResourceDataPtr<const IVVertexStream> StreamRes;

	struct BufferInfo
	{
		StreamRes pStream;
		VVertexFormat::DataTypes dataTypeFlag;
	};

	void AddVertexBuffer(
		std::string in_strResourceName, 
		VVertexFormat::DataTypes in_Types);

	std::vector<BufferInfo> m_Streams;
	std::auto_ptr<StreamRes> m_pIndexStream;
	vuint m_nPrimitiveCount;
	const GLint m_PrimitiveType;

	//TODO: hacked in indexoffset --ins

	vuint m_nIndexOffset;

	vbool m_bShowNormal;
	resource::VResourceDataPtr<const VVertexBuffer> m_CoordBuffer;
	resource::VResourceDataPtr<const VVertexBuffer> m_NormalBuffer;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VSTREAMMESH_2005_02_03_H

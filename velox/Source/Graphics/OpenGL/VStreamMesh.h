#ifndef V3D_VSTREAMMESH_2005_02_03_H
#define V3D_VSTREAMMESH_2005_02_03_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Resource.h>

#include <V3d/OpenGL.h>

#include "IVVertexStream.h"
#include "VImmediateVertexStream.h"
#include "../DeviceBase/VMeshBase.h"

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
		std::vector<IVMaterial*> in_Materials,
		const VMeshDescription& in_MeshDescription
		);

	virtual ~VStreamMesh();

	virtual void Render();

private:
	typedef resource::VResourceDataPtr<const VImmediateVertexStream> StreamRes;

	struct BufferInfo
	{
		StreamRes pStream;
		IVVertexStream::DataTypes dataTypeFlag;
	};

	void AddVertexBuffer(
		std::string in_strResourceName, 
		IVVertexStream::DataTypes in_Types);

	std::vector<BufferInfo> m_Streams;
	const vuint m_nPrimitiveCount;
	const GLint m_PrimitiveType;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VSTREAMMESH_2005_02_03_H

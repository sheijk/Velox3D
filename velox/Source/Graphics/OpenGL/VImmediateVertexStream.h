#ifndef V3D_VIMMEDIATEVERTEXSTREAM_2005_02_03_H
#define V3D_VIMMEDIATEVERTEXSTREAM_2005_02_03_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Resource.h>
#include <V3d/Graphics/VVertexBuffer.h>

#include "IVVertexStream.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VImmediateVertexStream : public IVVertexStream
{
public:
	typedef resource::VResourceDataPtr<const VVertexBuffer> VertexDataPtr;

	VImmediateVertexStream(VertexDataPtr in_pVertexData);
	virtual ~VImmediateVertexStream();

	virtual vbool Bind(DataTypes in_StreamTypes) const;
	virtual void UnbindAll() const;

	virtual const void* GetIndexAddress() const;
private:
	/** 
	 * Returns true iff the associated vertex buffer contains
	 * all data specified in in_DataTypes and the size of
	 * the required data is big enough
	 */
	vbool CanProvideStream(DataTypes in_DataTypes) const;

	VertexDataPtr m_pVertexData;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VIMMEDIATEVERTEXSTREAM_2005_02_03_H

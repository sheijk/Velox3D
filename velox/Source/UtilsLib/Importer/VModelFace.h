//-----------------------------------------------------------------------------
#ifndef V3D_VMODELFACE_H
#define V3D_VMODELFACE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace util{
namespace importer{
//-----------------------------------------------------------------------------
class VModelFace
{

public:
	VModelFace();
    ~VModelFace();

	vint32 m_iTextureUVIndex[3];
	vint32 m_iVertexIndex[3];

};
//-----------------------------------------------------------------------------
} // namespace importer
} // namespace util
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMODELFACE_H
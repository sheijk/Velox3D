#ifndef V3D_VMODELOBJECT3D_H
#define V3D_VMODELOBJECT3D_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
#include "VModelFace.h"
//-----------------------------------------------------------------------------
namespace v3d{
namespace utils{
namespace importer{
//-----------------------------------------------------------------------------
class VModelObject3D
{
public:
	VModelObject3D();
	~VModelObject3D();
	
	vuint32 m_iNumVertices;
	vuint32 m_iNumFaces;
	vuint32 m_iNumTexCoords2f;
	VModelFace* m_ModelFaces;
	vfloat32* m_VerticesList;
	vfloat32* m_TextureCoordsList;
	vuint32* m_pVertexIndex;

};
//-----------------------------------------------------------------------------
} // namespace importer
} // namespace util
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMODELOBJECT3D_H
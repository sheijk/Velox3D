//-----------------------------------------------------------------------------
#ifndef V3D_VOPENGLVBOMESH_H
#define V3D_VOPENGLVBOMESH_H
//-------------------------------------------------------------------------
#include "../DeviceBase/VBaseMesh.h"
#include "../DeviceBase/VRenderMethodRegistry.h"
//-------------------------------------------------------------------------
#include <extgl/extgl.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------


/**
 * @author ins
 * @version 1.0
 * @created 23-Dez-2003 18:14:53
 */


class VOpenGLVBOMesh : public VBaseMesh 
{
	VMeshDescription::FloatDataRef m_TriangleData;
	VMeshDescription::FloatDataRef m_ColorData;

public:
	VOpenGLVBOMesh(VMeshDescription& in_MeshDescr);
	virtual ~VOpenGLVBOMesh();
	virtual void Render();

private:

	vuint m_iNumElements;

	/* array id for the vertex buffer object */
	GLuint m_ArrayID;
	GLuint m_ColorArrayID;

};

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#endif // V3D_VOPENGLVBOMESH_H
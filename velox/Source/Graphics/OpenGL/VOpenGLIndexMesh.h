//-----------------------------------------------------------------------------
#ifndef V3D_VOPENGLINDEXMESH_H
#define V3D_VOPENGLINDEXMESH_H
//-----------------------------------------------------------------------------
#include <v3d/Math/VVector.h>
#include <v3d/Graphics/VMeshDescription.h>

#include "../DeviceBase/VRenderMethodRegistry.h"

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Simplest rendering method. Renders using glBegin, glVertex.. etc
 *
 * @author ins 
 */
class VOpenGLIndexMesh : public VBaseMesh
{
	typedef VVector<vfloat32, 3> Vertex;

	VMeshDescription::FloatDataRef m_TriangleData;
	VMeshDescription::FloatDataRef m_ColorData;
	VMeshDescription::IntDataRef m_IndexData;

public:
	VOpenGLIndexMesh(const VMeshDescription& in_Descr);
	virtual ~VOpenGLIndexMesh();

	virtual void Render();	
};


//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------


#endif // V3D_VOPENGLINDEXMESH_H
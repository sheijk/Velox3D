//-------------------------------------------------------------------------
#ifndef V3D_VOPENGLVBORENDERINGMETHOD_H
#define V3D_VOPENGLVBORENDERINGMETHOD_H
//-------------------------------------------------------------------------
#include <v3d/Graphics/VMeshDescription.h>
#include "../DeviceBase/VRenderMethodRegistry.h"
#include "VOpenGLVBOMesh.h"
//-------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------


/**
 * @author ins
 * @version 1.0
 * @created 23-Dez-2003 18:03:00
 */

class VOpenGLVBOMesh;

class VOpenGLVBORenderMethod : public IVRenderMethod 
{
public:
	
	/**
	 * @param creates VBOMesh out of a Mesh description
	 */
	virtual VOpenGLVBOMesh* CreateMesh(VMeshDescription& desc);

};

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------------
#endif // V3D_VOGLVBORENDERINGMETHOD_H
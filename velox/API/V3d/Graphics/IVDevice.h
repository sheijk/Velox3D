#ifndef V3D_IVDEVICE_H
#define V3D_IVDEVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVMesh.h>
#include <v3d/Graphics/IVMaterial.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

class IVDevice
{
public:
	
	virtual ~IVDevice() {};

	virtual IVMesh* CreateMesh() = 0;
	virtual IVMaterial* CreateMaterial() = 0;
	virtual void ApplyMaterial(IVMaterial* in_pMatrial) = 0;
	virtual void RenderMesh(IVMesh* in_pMesh) = 0;
	
	/**
	* This is only implemented to show anything by now
	* TODO: build the damn renderer ;)
	*/

	virtual void BeginScene() = 0;
	virtual void EndScene() = 0;
	
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDEVICE_H

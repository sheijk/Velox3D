#ifndef V3D_VMeshBase_H
#define V3D_VMeshBase_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/IVMesh.h>
#include <v3d/Graphics/IVMaterial.h>

//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

class VMeshBase : public IVMesh
{
	IVMaterial* const m_pMaterial;

public:
	VMeshBase(IVMaterial* in_pMaterial);

	virtual IVMaterial& GetMaterial();
	virtual void Render() = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMeshBase_H

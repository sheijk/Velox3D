#ifndef V3D_VMeshBase_H
#define V3D_VMeshBase_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/IVMesh.h>
#include <v3d/Graphics/IVMaterial.h>
#include <v3d/Graphics/VMeshDescription.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

class VMeshBase : public IVMesh
{
	std::vector<VMeshDescription::BufferHandle> m_Buffers;

	const std::vector<IVMaterial*> m_Materials;
	//IVMaterial* const m_pMaterial;

public:
	VMeshBase(std::vector<IVMaterial*> in_Materials);

	virtual vuint GetMaterialCount() const;
	virtual IVMaterial& GetMaterial(vuint in_nMaterialId);

	virtual void Render() = 0;

	void SetBuffers(std::vector<VMeshDescription::BufferHandle> in_Buffers);
	std::vector<VMeshDescription::BufferHandle> GetBuffers() const;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMeshBase_H

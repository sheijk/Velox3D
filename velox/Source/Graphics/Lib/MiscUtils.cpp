//TODO: insert header file name
#include <V3dLib/Graphics/Misc/MiscUtils.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/MemManager.h>
#include <V3dLib/Graphics/Misc/IVDrawList.h>
#include <V3dLib/Math.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

void ApplyMaterial(IVDevice& in_Device, const IVPass* in_pMaterial)
{
	for(vuint prio = 0; prio < in_pMaterial->StateCount(); ++prio)
	{
		in_Device.ApplyState(in_pMaterial->GetState(prio));
	}
}

void RenderMesh(
	IVDevice& in_Device, 
	IVDevice::MeshHandle in_hMesh,
	IVMaterial* in_hMaterial
	)
{
	for(vuint matid = 0; matid < in_hMaterial->PassCount(); ++matid)
	{
		const IVPass* pPass = & in_hMaterial->GetPass(matid);

		ApplyMaterial(in_Device, pPass);
		in_Device.RenderMesh(in_hMesh);
	}

	//for(vuint matid = 0; matid < in_hMesh->GetMaterialCount(); ++matid)
	//{
	//	IVMaterial* pMaterial = & in_hMesh->GetMaterial(matid);

	//	ApplyMaterial(in_Device, pMaterial);
	//	in_Device.RenderMesh(in_hMesh);
	//}
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
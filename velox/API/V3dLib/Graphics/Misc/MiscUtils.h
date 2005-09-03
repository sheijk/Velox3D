#ifndef V3D_SHEIJKUTILS20040407_H
#define V3D_SHEIJKUTILS20040407_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
#include <v3d/Image.h>
#include <v3d/Graphics.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * @author: ins
 */
void ApplyMaterial(IVDevice& in_Device, const IVPass* in_pMaterial);

/**
 * Renders the given mesh to the device. All materials will be rendered
 * using as many passes as materials
 *
 * @author sheijk
 */
void RenderMesh(
	IVDevice& in_Device, 
	IVDevice::MeshHandle in_hMesh,
	IVDevice::MaterialHandle in_hMaterial);

/**
 * Renders the given mesh to the device
 *
 * @author sheijk
 */
void RenderMesh(graphics::IVDevice& in_Device, const graphics::VModelMesh& in_Mesh);

/**
 * Renders all meshes of the given model
 *
 * @author sheijk
 */
void RenderModel(graphics::IVDevice& in_Device, const graphics::VModel& in_Model);

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_SHEIJKUTILS20040407_H

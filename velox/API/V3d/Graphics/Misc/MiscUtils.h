/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_SHEIJKUTILS20040407_H
#define V3D_SHEIJKUTILS20040407_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
#include <V3d/Image.h>
#include <V3d/Graphics.h>
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


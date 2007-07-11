/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVMESH_H
#define V3D_IVMESH_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
class IVMaterial;

/**
 * A handle for a mesh loaded in the device
 *
 * @author sheijk
 */
class IVMesh
{
public:
	virtual ~IVMesh() {};

	//virtual vuint GetMaterialCount() const = 0;
	//virtual IVMaterial& GetMaterial(vuint in_nMaterialId) = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
V3D_TYPEINFO(v3d::graphics::IVMesh);
//-----------------------------------------------------------------------------
#endif // V3D_IVMESH_H


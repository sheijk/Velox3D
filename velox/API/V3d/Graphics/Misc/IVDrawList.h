/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVDRAWLIST_H
#define V3D_IVDRAWLIST_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Math/VMatrix.h>
#include <V3d/Graphics/IVDevice.h>
#include <V3d/Graphics/VModel.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Holds a list of meshes and renders them. Should sort meshes by their
 * render states to gain speed
 *
 * @author sheijk
 */
struct IVDrawList
{
	typedef vuint ModelMeshId;
	static ModelMeshId GetInvalidId() { return 0; }

	virtual ~IVDrawList() {}

	virtual ModelMeshId Add(VModelMesh in_Model) = 0;
	virtual void Remove(ModelMeshId in_Model) = 0;

	virtual void Render() = 0;

	virtual IVDevice& GetDevice() = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDRAWLIST_H


/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMeshBase_H
#define V3D_VMeshBase_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVMesh.h>
//#include <V3d/Graphics/IVMaterial.h>
//#include <V3d/Graphics/VMeshDescription.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

class VMeshBase : public IVMesh
{
	//std::vector<VMeshDescription::BufferHandle> m_Buffers;

	//const std::vector<IVMaterial*> m_Materials;
	//IVMaterial* const m_pMaterial?;

public:
	//VMeshBase(std::vector<IVMaterial*> in_Materials);

	//virtual vuint GetMaterialCount() const;
	//virtual IVMaterial& GetMaterial(vuint in_nMaterialId);

	virtual void Render() const = 0;

	//void SetBuffers(std::vector<VMeshDescription::BufferHandle> in_Buffers);
	//std::vector<VMeshDescription::BufferHandle> GetBuffers() const;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMeshBase_H


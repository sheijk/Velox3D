/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSIMPLEDRAWLIST_H
#define V3D_VSIMPLEDRAWLIST_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/Misc/IVDrawList.h>
#include <list>
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
class VSimpleDrawList : public IVDrawList
{
public:
	VSimpleDrawList(v3d::graphics::IVDevice& in_Device);
	~VSimpleDrawList();
		
	virtual ModelMeshId Add(VModelMesh in_Model);
	virtual void Remove(ModelMeshId in_Model);

	virtual void Render();
	virtual IVDevice& GetDevice();

private:
	void ApplyMaterial(const IVPass* in_pRenderStates);

	typedef std::pair<ModelMeshId, VModelMesh> ModelMeshAndId;
	typedef std::list<ModelMeshAndId> ModelList;

	ModelMeshId m_nNextFreeId;
	
	ModelList m_Models;
	IVDevice& m_Device;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSIMPLEDRAWLIST_H


#ifndef V3D_VSIMPLEDRAWLIST_H
#define V3D_VSIMPLEDRAWLIST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3dLib/Graphics/Misc/IVDrawList.h>
#include <list>
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
class VSimpleDrawList : public IVDrawList
{
public:
	//typedef v3d::graphics::IVDevice::BufferHandle BufferHandle;
	//typedef v3d::graphics::IVDevice::MeshHandle MeshHandle;
	//typedef v3d::graphics::IVDevice::MaterialHandle MaterialHandle;

	VSimpleDrawList(v3d::graphics::IVDevice& in_Device);
	~VSimpleDrawList();
		
	virtual void Add(VModelMesh in_Model);
	//virtual void Remove(VModelMesh in_Model);

	virtual void Render();
	virtual IVDevice& GetDevice();

private:
	void ApplyMaterial(const IVPass* in_pRenderStates);

	typedef std::list<VModelMesh> ModelList;
	
	ModelList m_Models;
	IVDevice& m_Device;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSIMPLEDRAWLIST_H

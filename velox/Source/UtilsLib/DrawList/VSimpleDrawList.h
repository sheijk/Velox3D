#ifndef V3D_VSIMPLEDRAWLIST_H
#define V3D_VSIMPLEDRAWLIST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/DrawList/IVDrawList.h>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
namespace drawlist {
//-----------------------------------------------------------------------------
class VSimpleDrawList : public IVDrawList
{
public:

	typedef IVDevice::BufferHandle BufferHandle;
	typedef IVDevice::MeshHandle MeshHandle;
	typedef IVDevice::MaterialHandle MaterialHandle;

	VSimpleDrawList(IVDevice& in_Device);
	~VSimpleDrawList();
		
	virtual void Add(VModel* in_pModel);
	virtual void Remove(VModel* in_pModel);

	virtual void Render();

	void ApplyMaterial(IVMaterial* in_pRenderStates);
	

private:
	typedef std::list<VModel*> ModelList;

	ModelList m_Models;
	IVDevice& m_Device;
};

//-----------------------------------------------------------------------------
} // namespace drawlist
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSIMPLEDRAWLIST_H

#ifndef V3D_VSIMPLEDRAWLIST_H
#define V3D_VSIMPLEDRAWLIST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3dLib/Graphics/Misc/IVDrawList.h>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
class VSimpleDrawList : public IVDrawList
{
public:
	typedef v3d::graphics::IVDevice::BufferHandle BufferHandle;
	typedef v3d::graphics::IVDevice::MeshHandle MeshHandle;
	typedef v3d::graphics::IVDevice::MaterialHandle MaterialHandle;

	VSimpleDrawList(v3d::graphics::IVDevice& in_Device);
	~VSimpleDrawList();
		
	virtual void Add(VModel in_Model);
	virtual void Remove(VModel in_Model);

	virtual void Render();
	virtual IVDevice& GetDevice();

private:
	void ApplyMaterial(IVMaterial* in_pRenderStates);

	typedef VModel::TransformMatrixPtr TransformMatrixPtr;
	typedef std::list<VModel> ModelList;
	
	ModelList m_Models;
	IVDevice& m_Device;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSIMPLEDRAWLIST_H

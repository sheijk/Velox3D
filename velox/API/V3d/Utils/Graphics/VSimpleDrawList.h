#ifndef V3D_VSIMPLEDRAWLIST_H
#define V3D_VSIMPLEDRAWLIST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/DrawList/IVDrawList.h>
#include <list>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
namespace graphics {
namespace drawlist {
//-----------------------------------------------------------------------------
class VSimpleDrawList : public v3d::graphics::drawlist::IVDrawList
{
public:

	typedef v3d::graphics::IVDevice::BufferHandle BufferHandle;
	typedef v3d::graphics::IVDevice::MeshHandle MeshHandle;
	typedef v3d::graphics::IVDevice::MaterialHandle MaterialHandle;

	VSimpleDrawList(v3d::graphics::IVDevice& in_Device);
	~VSimpleDrawList();
		
	virtual void Add(v3d::graphics::drawlist::VModel in_Model);
	virtual void Remove(v3d::graphics::drawlist::VModel in_Model);

	virtual void Render();

	void ApplyMaterial(v3d::graphics::IVMaterial* in_pRenderStates);
	

private:
	typedef std::list<v3d::graphics::drawlist::VModel> ModelList;
	
	ModelList m_Models;
	v3d::graphics::IVDevice& m_Device;
};

//-----------------------------------------------------------------------------
} // namespace drawlist
} // namespace utils
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSIMPLEDRAWLIST_H

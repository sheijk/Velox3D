#ifndef V3D_VSIMPLESCENEGRAPH_H
#define V3D_VSIMPLESCENEGRAPH_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Graphics/SimpleSG/IVNode.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
namespace simplesg {
//-----------------------------------------------------------------------------

class IVSceneManager
{
	virtual IVNode* GetRootNode() = 0;
};

// frage: sollte hier eine drawlist fester bestandteil sein?
// pro: man muss sich nicht extra um die drawlist kuemmern und es beugt
// bugs durch unbemerktes vertauschen von drawlists vor
class VSimpleSceneGraph : public IVSceneManager
{
public:
	//void SetCamera(VCamera* in_pCamera);

	virtual IVNode* GetRootNode();

	//-
//	VSimpleSceneGraph(IVDevice* in_pDevice);
	//void Update();
	//void Render();
//	void SetParentNode(IVNode* in_pNode);

private:
	IVNode* m_pRootNode;

	//-
	//VCamera* m_pCamera;
	//IVDevice* m_pDevice;
	//drawlist::VSimpleDrawList* m_pDrawlist;
	//VVisibilityChecker* m_pVisChecker;
};

//-----------------------------------------------------------------------------
} // namespace simplesg
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSIMPLESCENEGRAPH_H

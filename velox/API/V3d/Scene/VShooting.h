#ifndef V3D_VSHOOTING_2005_05_22_H
#define V3D_VSHOOTING_2005_05_22_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Scene/IVShooting.h>
#include <V3d/Scene/IVRenderAlgorithm.h>
#include <V3d/Scene/IVScene.h>
#include <V3d/Scene/IVRenderList.h>

#include <V3d/Graphics/IVDevice.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VShooting : public IVShooting
{
public:
	VShooting(graphics::IVDevice* in_pDevice, IVRenderAlgorithm* in_pAlgorithm);

	virtual void Activate();
	virtual void Deactivate();
	virtual void Connect(
		Location in_Location, const std::string& in_Id, IVPart& in_Part);
	virtual void Disconnect(
		Location in_Location, const std::string& in_Id, IVPart& in_Part);
	virtual vbool IsReady() const;
	virtual vuint DependencyCount() const;
	virtual Dependency GetDependencyInfo(vuint in_nIndex) const;

	void Cull();
	void Render();

private:
	/** The associated scene */
	IVScene* m_pScene;

	/** The rendering algorithm */
	VSharedPtr<IVRenderAlgorithm> m_pRenderAlgorithm;

	/** The camera */

	/** The render target */
	graphics::IVDevice* m_pRenderTarget;

	/** The list of currently visible objects */
	IVRenderList* m_pRenderList;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VSHOOTING_2005_05_22_H

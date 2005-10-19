#ifndef V3D_VSIMPLESHOOTING_2005_09_24_H
#define V3D_VSIMPLESHOOTING_2005_09_24_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVShooting.h>
#include <V3d/Scene/IVGraphicsPart.h>
#include <V3d/Entity/VPartBase.h>
#include <V3d/Graphics/IVDevice.h>

#include <V3d/Scene/IVRenderStepPart.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVRenderStepPart;

/**
 * Simply renders the whole scene "as it is". For every visible shape it's
 * material and transform are applied and it's geometry is rendered
 *
 * Also serves as a base class for special shootings like shadow mapping etc
 *
 * @author sheijk
 */
class VSimpleShooting : public entity::VPartBaseAdapter<IVShooting>
{
public:
	VSimpleShooting();

	virtual void UpdateAndCull();
	virtual void Render();

	void SetRenderTarget(graphics::IVDevice* in_pDevice);
	graphics::IVDevice* GetRenderTarget() const;
	
	void SetCamera(graphics::IVCamera* in_pCamera);
	graphics::IVCamera* GetCamera() const;

	void Add(IVRenderStepPart* in_pRenderStep);
	void Remove(IVRenderStepPart* in_pRenderStep);

	virtual void Activate();
	virtual void Deactivate();

	virtual vbool IsActive() const;

protected:
	VSimpleShooting(entity::VPartDependency::Location in_SceneLocation,
		const std::string& in_SceneId,
		entity::VPartDependency::Condition in_SceneCondition);
	
	void SetupRenderSteps();

	typedef std::vector<IVRenderStepPart*> RenderStepArray;
	RenderStepArray m_RenderSteps;

	entity::VPartConnection<IVGraphicsPart> m_pScene;
	graphics::IVDevice* m_pDevice;
	graphics::IVCamera* m_pCamera;

private:
	vbool m_bActive;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VSIMPLESHOOTING_2005_09_24_H

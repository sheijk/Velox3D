#ifndef V3D_VNAIVELIGHTMANAGER_2006_01_21_H
#define V3D_VNAIVELIGHTMANAGER_2006_01_21_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Scene/IVLightManager.h>
#include <V3d/Entity/VUnconnectedPart.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
class VLightPart;
class IVShapePart;

/**
 * A simple light manager. Will always try to activate all registered lights
 *
 * @author sheijk
 */
class VNaiveLightManager : public entity::VUnconnectedPartAdapter<IVLightManager>
{
public:
	virtual void Add(VLightPart* in_pLight);
	virtual void Remove(VLightPart* in_pLight);

	void ApplyLights(graphics::IVDevice* in_pDevice, IVShapePart* in_pShape);

	void Activate();
	void Deactivate();
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

private:
	typedef std::set<VLightPart*> LightSet;
	LightSet m_Lights;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
V3D_TYPEINFO_WITHPARENT(v3d::scene::VNaiveLightManager, v3d::scene::IVLightManager);
//-----------------------------------------------------------------------------
#endif // V3D_VNAIVELIGHTMANAGER_2006_01_21_H

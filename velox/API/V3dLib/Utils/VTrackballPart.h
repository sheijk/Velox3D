#ifndef V3D_VTRACKBALLPART_2005_12_09_H
#define V3D_VTRACKBALLPART_2005_12_09_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3dLib/Utils/VMouseTrackball.h>

#include <V3d/Entity/VPartBase.h>
#include <V3dLib/EntityParts/VUpdateablePart.h>
#include <V3dLib/EntityParts/VRigidBodyPart.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VTrackballPart : public entity::VPartBaseAdapter<entity::IVUpdateablePart>
{
public:
	VTrackballPart();
	virtual ~VTrackballPart();

	virtual void Update(vfloat32 in_fSeconds);

	virtual void Activate();
	virtual void Deactivate();
	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

	void SetTrackball(const VSharedPtr<VMouseTrackball>& in_Trackball);
private:
	VSharedPtr<VMouseTrackball> m_pTrackball;

	entity::VPartConnection<entity::VRigidBodyPart> m_pRigidBodyPart;
	entity::VPartConnection<entity::VUpdateManagerPart> m_pUpdateManager;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils

V3D_TYPEINFO_WITHPARENT(v3d::utils::VTrackballPart, v3d::entity::IVUpdateablePart);
//-----------------------------------------------------------------------------
#endif // V3D_VTRACKBALLPART_2005_12_09_H

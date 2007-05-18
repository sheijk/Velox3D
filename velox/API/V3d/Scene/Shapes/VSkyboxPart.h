/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSKYBOXPART_2005_12_01_H
#define V3D_VSKYBOXPART_2005_12_01_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Entity/VPartBase.h>
#include <V3d/Scene/IVShapePart.h>
#include <V3d/Entity/VRigidBodyPart.h>
#include <V3d/Resource.h>
#include <V3d/Graphics/IVMaterial.h>
#include <V3d/Scene/IVSceneManagerPart.h>
#include <V3d/Graphics/Geometry/VColor4f.h>

#include <vector>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
	class IVDevice;
	class IVMaterial;
}}

namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VSkyboxPart : public entity::VPartBaseAdapter<IVGraphicsPart>
{
public:
	VSkyboxPart();
	virtual ~VSkyboxPart();

	/** 
	 * Use in_strDirectory/*.extension as textures
	 * * = left/right/front/back/top/bottom
	 */
	void SetTextureDir(
		const std::string& in_strDirectory, 
		const std::string& in_strExtension);

	/** The sky box will be blended with the given color via vertex color */
	void SetBaseColor(const graphics::VColor4f& in_Color);

	// inherited
	virtual void UpdateAndCull(const graphics::IVCamera& in_Camera);
	virtual VRangeIterator<const IVShapePart> GetVisibleMeshes() const;

	virtual void Activate();
	virtual void Deactivate();

	virtual const VTypeInfo& GetTypeInfo() const { return GetCompileTimeTypeInfo(this); }

protected:
	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();
	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);

private:
	std::string GetTextureDir() const;
	void SetTextureDir(const std::string& dirname);
	std::string m_strTextureDir;

	class VSide;

	const math::VRBTransform& GetModelTransform() const;

	std::vector<VSharedPtr<VSide> > m_Sides;
	entity::VPartConnection<entity::VRigidBodyPart> m_pRigidBodyPart;
	entity::VPartConnection<scene::IVSceneManagerPart> m_pSceneManager;

	graphics::VColor4f m_BaseColor;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene

V3D_TYPEINFO_WITHPARENT(v3d::scene::VSkyboxPart, v3d::scene::IVGraphicsPart);
//-----------------------------------------------------------------------------
#endif // V3D_VSKYBOXPART_2005_12_01_H


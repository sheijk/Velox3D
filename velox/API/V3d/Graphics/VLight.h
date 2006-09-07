/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VLIGHT_2005_12_26_H
#define V3D_VLIGHT_2005_12_26_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Graphics/IVParameter.h>
#include <V3d/Graphics/Parameters/IVParameterValue.h>
#include <V3d/Core/RangeIter.h>
#include <V3d/Graphics/Geometry/VColor4f.h>
#include <V3d/Math/VRBTransform.h>

#include <string>
#include <map>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
	class VLightPart;
}}

namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VLight
{
public:
	VLight();
	virtual ~VLight();

	VRangeIterator<IVParameterValue> Parameters();
	VSharedPtr<IVParameterValue> GetParameter(const std::string& in_strName);

	void AddParameter(const std::string& in_strName, VSharedPtr<IVParameterValue> in_pParameter);

	void ApplyTo(VRangeIterator<IVParameter> in_Parameters);

	//VRangeIterator<IVParameter> Parameters();
	///** Returns Null if no param with the given name exists */
	//VSharedPtr<IVParameter> GetParameter(const std::string& in_strName);

	//VSharedPtr<IVParameter> AddParameter(const std::string& in_strName);

	// some default values used for fixed function pipeline rendering
	// (and probably supported in many shaders)
	math::VVector3f GetPosition() const;
	void SetPosition(const math::VVector3f& in_Position);

	const math::VRBTransform& GetTransform() const;
	void SetTransform(const math::VRBTransform& in_Transform);

	vfloat32 GetW() const { return m_fW; }
	void SetW(const vfloat32& in_Value) { m_fW = in_Value; }

	VColor4f GetAmbientColor() const;
	void SetAmbientColor(const VColor4f& in_AmbientColor);

	VColor4f GetDiffuseColor() const;
	void SetDiffuseColor(const VColor4f& in_DiffuseColor);

	VColor4f GetSpecularColor() const;
	void SetSpecularColor(const VColor4f& in_SpecularColor);

private:
	// temp. workaround for VMessageInterpreter's lack of support for getters
	// and setters (->VLightPart.OnMessage)
	friend class ::v3d::scene::VLightPart;

	math::VVector3f m_Position;
	math::VRBTransform m_Transform;
	vfloat32 m_fW;
	VColor4f ambientColor;
	VColor4f diffuseColor;
	VColor4f specularColor;

	typedef std::map<std::string, VSharedPtr<IVParameterValue> > ParameterMap;
	ParameterMap m_Parameters;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VLIGHT_2005_12_26_H


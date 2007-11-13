/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVPARAMETER_2005_11_26_H
#define V3D_IVPARAMETER_2005_11_26_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Math/VVector.h>
#include <V3d/Math/VMatrix.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVDevice;

/**
 * Base class for parameters which belong to a material/shader/.. <br />
 * Values can only be applied and queried while the associated material/shader/..
 * is active. Values are not guaranteed to keep the same after the material/..
 * is unapplied and need to be set after each time the material is applied.
 *
 * @author sheijk
 */
class IVParameter
{
public:
	enum Type
	{
		Float, Float2, Float4, Float44,
		Int,
		Boolean,
		Texture,
		Unknown
	};
	
	virtual ~IVParameter(){};

	virtual std::string GetName() const = 0;
	virtual Type GetType() const = 0;

	virtual void Apply(vfloat32 in_fNewValue) const = 0;
	virtual vfloat32 AsFloat() const = 0;
	virtual void Apply(const math::VVector2f& in_NewValue) const = 0;
	virtual math::VVector2f AsFloat2() const = 0;
	virtual void Apply(const math::VVector4f& in_NewValue) const = 0;
	virtual math::VVector4f AsFloat4() const = 0;

	virtual math::VMatrix44f AsFloat44() const = 0;
	virtual void Apply(const math::VMatrix44f& in_NewValue) const = 0;

	virtual void Apply(vint in_nNewValue) const = 0;
	virtual vint AsInt() const = 0;

	virtual void Apply(vbool in_bNewValue) const = 0;
	virtual vbool AsBool() const = 0;

	virtual void ApplyTexture(VStringParam in_strResourceName) const = 0;
	virtual std::string TextureResource() const = 0;

	// -> VMaterialSetup.cpp, TODO: correct this!
	/** Will convert the string to a value dependent on this parameter's type */
	void Apply(const std::string& in_strValue);
	/** Return's the parameters value to a string (depending on it's type */
	std::string AsString() const;

	/** applies values to special parameters (v3d_MaxLight etc.) */
	void ApplyAutoValue(IVDevice& in_Device);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_IVPARAMETER_2005_11_26_H


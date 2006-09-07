/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VTEXTUREVALUE_2005_12_27_H
#define V3D_VTEXTUREVALUE_2005_12_27_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Graphics/Parameters/IVParameterValue.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Parameter value to set a texture parameter
 *
 * @author sheijk
 */
class VTextureValue : public IVParameterValue
{
public:
	VTextureValue();
	VTextureValue(const std::string& in_strTextureResource);

	virtual void Apply(const IVParameter& in_Param) const;

	std::string GetTextureResource() const;
	void SetTextureResource(const std::string& in_Value);

	virtual void Set(const std::string& in_NewValue);
	virtual std::string Get() const;
private:
	std::string m_strTextureResource;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTUREVALUE_2005_12_27_H


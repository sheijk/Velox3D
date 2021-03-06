/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVPARAMETERVALUE_2005_11_29_H
#define V3D_IVPARAMETERVALUE_2005_11_29_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/SmartPtr/VSharedPtr.h>
#include <V3d/Graphics/IVParameter.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class IVParameterValue
{
public:
	virtual ~IVParameterValue() {}

	virtual void Apply(const IVParameter& in_Param) const = 0;
	virtual void Set(const std::string& in_NewValue) = 0;
	virtual std::string Get() const = 0;
};

// implemented in VMaterialSetup.cpp, sorry *hide* ;)
VSharedPtr<IVParameterValue> CreateParamValue(IVParameter::Type in_ParamType);

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_IVPARAMETERVALUE_2005_11_29_H


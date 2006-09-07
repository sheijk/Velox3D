/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMATERIALSETUP_2005_11_29_H
#define V3D_VMATERIALSETUP_2005_11_29_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/SmartPtr/VSharedPtr.h>
#include <V3d/Graphics/IVParameter.h>

#include <map>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVMaterial;
class IVParameterValue;

/**
 */
class VMaterialSetup
{
public:
	VMaterialSetup();
	virtual ~VMaterialSetup();

	void Apply(IVMaterial& io_Material) const;

	void Add(VStringParam in_strParamName, VSharedPtr<IVParameterValue> in_Value);

private:
	typedef std::map<std::string, VSharedPtr<IVParameterValue> > NameValueMap;

	NameValueMap m_Values;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VMATERIALSETUP_2005_11_29_H


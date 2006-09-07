/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVMATERIAL_H
#define V3D_IVMATERIAL_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>

#include <V3d/Graphics/IVParameter.h>
#include <V3d/Graphics/IVPass.h>
#include <V3d/Math/VVector.h>
//----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Client visible material controlling
 *
 * @author sheijk
 */
class IVMaterial
{
public:	
	typedef std::string ParamHandle;

	virtual ~IVMaterial() {};

	virtual vuint PassCount() const = 0;
	virtual const IVPass& GetPass(vuint in_nNum) const = 0;

	//virtual void SetParameter(ParamHandle in_Param, vfloat32 in_Value) const = 0;
	//virtual void SetParameter(ParamHandle in_Param, VVector4f in_Value) const = 0;

	virtual VRangeIterator<IVParameter> Parameters() = 0;
	virtual IVParameter* GetParameterByName(const std::string& in_strName) = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d

V3D_TYPEINFO(v3d::graphics::IVMaterial);
//-----------------------------------------------------------------------------
#endif // V3D_IVMATERIAL_H


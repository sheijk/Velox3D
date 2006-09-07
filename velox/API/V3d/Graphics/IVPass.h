/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVPASS_2005_08_18_H
#define V3D_IVPASS_2005_08_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/RangeIter/VRangeIterator.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class IVRenderState;

class IVPass
{
public:
	virtual ~IVPass() {};
	virtual vuint StateCount() const = 0;
	virtual const IVRenderState& GetState(vuint in_nPriority) const = 0;

	virtual VRangeIterator<IVParameter> Parameters() = 0;
	virtual IVParameter* GetParameterByName(const std::string& in_strName) = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_IVPASS_2005_08_18_H


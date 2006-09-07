/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVRANGEITERATORPOLICY_H_2005_01_20_H
#define V3D_IVRANGEITERATORPOLICY_H_2005_01_20_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting
	
template<typename T>
	class IVRangeIteratorPolicy
{
public:
	virtual void Proceed() = 0;
	virtual T* Get() const = 0;
	virtual vbool HasNext() const = 0;
	virtual IVRangeIteratorPolicy<T>* Clone() const = 0;
	virtual vbool IsEqual(const IVRangeIteratorPolicy<T>&) const = 0;
};
	
//-----------------------------------------------------------------------------
} // namespace v3d
  //-----------------------------------------------------------------------------
#endif // V3D_IVRANGEITERATORPOLICY_H_2005_01_20_H


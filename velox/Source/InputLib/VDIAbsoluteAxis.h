/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDIABSOLUTEAXIS_09_02_H
#define V3D_VDIABSOLUTEAXIS_09_02_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/Wrappers/VString.h>
#include <V3d/Input/IVAbsoluteAxis.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/**
 * DirectInput implementation of IVRelativeAxis
 * @author AcrylSword
 * @version 1.2
 */
class VDIAbsoluteAxis : public IVAbsoluteAxis
{
    VDIAbsoluteAxis();

    VString	  m_strName;		
    vfloat32  m_fPos;

public:
	VDIAbsoluteAxis( VStringParam in_strName );
	virtual	~VDIAbsoluteAxis();
    virtual VStringRetVal GetName();
    virtual vfloat32 GetPosition();
    void Set( vfloat32 in_fPos );
};
//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDIABSOLUTEAXIS_09_02_H

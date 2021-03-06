/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDIRELATIVEAXIS_09_02_2004_H
#define V3D_VDIRELATIVEAXIS_09_02_2004_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/Wrappers/VString.h>
#include <V3d/Input/IVRelativeAxis.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace input {
//-----------------------------------------------------------------------------
/**
 * DirectInput implementation of IVRelativeAxis
 * @author AcrylSword
 * @version 1.2
 */
class VDIRelativeAxis : public IVRelativeAxis
{
	VString		m_strName;
	vfloat32	m_fMovement;
public:
        					VDIRelativeAxis();
							VDIRelativeAxis( VStringParam in_strName );

	virtual					~VDIRelativeAxis();

    virtual VStringRetVal	GetName();
	virtual vfloat32		GetLastMovement();

			void			Set( vfloat32 in_fMovement );
};
//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDIRELATIVEAXIS_09_02_2004_H

#ifndef V3D_VDIRELATIVEAXIS_09_02_2004_H
#define V3D_VDIRELATIVEAXIS_09_02_2004_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Input/IVRelativeAxis.h>
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
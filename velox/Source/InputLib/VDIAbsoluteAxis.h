#ifndef V3D_VDIABSOLUTEAXIS_H
#define V3D_VDIABSOLUTEAXIS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Input/IVAbsoluteAxis.h>

#include <dinput.h>
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

    VString					m_strName;		
    vfloat32				m_fPos;

    public:
								VDIAbsoluteAxis( VStringParam in_strName );
		virtual					~VDIAbsoluteAxis();
        
        virtual VStringRetVal	GetName();
        virtual vfloat32		GetPosition();
        void					Set( vfloat32 in_fPos );
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDIABSOLUTEAXIS_H

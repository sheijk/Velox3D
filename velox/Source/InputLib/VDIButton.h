#ifndef V3D_VDIBUTTON_H
#define V3D_VDIBUTTON_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Input/IVButton.h>

//-----------------------------------------------------------------------------
namespace v3d {
	namespace input {
	
//-----------------------------------------------------------------------------

/**
 * DirectInput implementation of a button
 * @author AcrylSword
 * @version 1.2
 */

class VDIButton : public IVButton
{
	//VDIButton();
    VString					m_strName;
	vbool					m_bState;


    public:

								VDIButton(VStringParam in_strName);
		virtual					~VDIButton();

        virtual VStringRetVal	GetName();
        virtual vbool			IsDown();

        void					Set( vbool in_bState );
};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDIBUTTON_H

#ifndef V3D_VDIMOUSEAXIS_H
#define V3D_VDIMOUSEAXIS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Input/IVRelativeAxis.h>

#include <dinput.h>

//-----------------------------------------------------------------------------
namespace v3d {
	namespace input {

		//-----------------------------------------------------------------------------
		/**
		* DirectInput implementation of IVRelativeAxis
		* @author AcrylSword
		* @version 1.1
		*/

		class VDIMouseAxis : public IVRelativeAxis
		{
			VString		m_strName;
			vlong*		m_pPointer;
			
		public:
			VDIMouseAxis() {;};
			VDIMouseAxis( VStringParam in_strName, vlong* in_pPointer );
			virtual			~VDIMouseAxis();

			virtual VStringRetVal	GetName();
			virtual vfloat32		GetLastMovement();
		};

		//-----------------------------------------------------------------------------
	} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDIMOUSEAXIS_H
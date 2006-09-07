/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDIMOUSEBUTTON_H
#define V3D_VDIMOUSEBUTTON_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/Input/IVButton.h>
//-----------------------------------------------------------------------------
namespace v3d {
	namespace input {
	
//-----------------------------------------------------------------------------

/**
 * DirectInput implementation of a mouse button
 * @author AcrylSword
 * @version 1.0
 */
		class VDIMouseButton : public IVButton
		{
						
		public:
						VDIMouseButton() {;};
            			VDIMouseButton( VStringParam in_strName, vbyte* in_pPointer);
			virtual		~VDIMouseButton();

			virtual VStringRetVal	GetName();
			virtual vbool			IsDown();

		protected:
			VString		m_strName;
			vbyte*		m_pPointer;
		};

//-----------------------------------------------------------------------------
} // namespace input
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDIMOUSEBUTTON_H


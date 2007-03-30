/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VXMLEXCEPTIONS_H
#define V3D_VXMLEXCEPTIONS_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VException.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace xml {
//-----------------------------------------------------------------------------

V3D_DECLARE_EXCEPTION(VXMLException, VException);
V3D_DECLARE_EXCEPTION(VXMLTranslationException, VXMLException);
V3D_DECLARE_EXCEPTION(VXMLAttributeException, VXMLException);
V3D_DECLARE_EXCEPTION(VXMLVistorException, VXMLException);
V3D_DECLARE_EXCEPTION(VXMLTinyXMLException, VXMLException);


//-----------------------------------------------------------------------------
} // namespace xml
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VXMLEXCEPTIONS_H


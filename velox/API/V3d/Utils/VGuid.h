/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VGUID_H
#define V3D_VGUID_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
* Generate ID for Objects
*
* @author lars
*/
class VGuid
{
public:

	VGuid();
	virtual ~VGuid();

	vbool operator==(const VGuid& in_other) const;
	vbool operator!=(const VGuid& in_other) const;
	
	/** Generate a ID */
	VGuid Generate();

private:

	vint m_iID;
};

//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VGUID_H

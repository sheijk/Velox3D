/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VALLFILTER_H
#define V3D_VALLFILTER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Error/IVErrorFilter.h> //TODO: namspace inkonsistent mit dir name
#include <v3d/Error/VMessageTypeEnum.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
//-----------------------------------------------------------------------------

/**
 * Filter for error logging
 */
class VAllFilter : public error::IVErrorFilter
{
public:
	vbool AcceptMessage(VStringParam in_strName,
		error::VMessageType in_MessageTyoe)	{ return true; };
	vbool AcceptState( VStringParam in_strName ) {return false;};
	vbool AcceptProgressbar( VStringParam in_strName ) {return false;};
};

//-----------------------------------------------------------------------------
} // namespace v3d
} // namespace utils
//-----------------------------------------------------------------------------
#endif // V3D_VALLFILTER_H



#ifndef V3D_VALLFILTER_H
#define V3D_VALLFILTER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Error/IVErrorFilter.h> //TODO: namspace inkonsistent mit dir name
#include <v3d/Error/VMessageTypeEnum.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace util {
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
} // namespace util
//-----------------------------------------------------------------------------
#endif // V3D_VALLFILTER_H


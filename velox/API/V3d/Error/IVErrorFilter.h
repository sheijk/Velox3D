#ifndef V3D_IVERRORFILTER_H
#define V3D_IVERRORFILTER_H

//TODO: //---- Zeilen wie in den Templates, damit der Source einheitlich ist (sheijk)

#include <v3d/Core/VCoreLib.h>
#include <v3d/Error/VMessageTypeEnum.h>

namespace v3d {
namespace error {

//TODO: Doku
class IVErrorFilter
{
public:
	virtual ~IVErrorFilter() {};
	virtual vbool AcceptMessage( VStringParam in_strName, VMessageType in_MessageType ) = 0;
	virtual vbool AcceptProgressbar( VStringParam in_strName ) = 0;
	virtual vbool AcceptState( VStringParam in_strName ) = 0;
};

} // error
} // v3d
#endif // V3D_IVERRORFILTER_H
#ifndef V3D_IVCONSOLESERVICE_H
#define V3D_IVCONSOLESERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VNamedObject.h>
#include <V3d/Utils/IVStringStream.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------

/**
 * An simple console service using wxWindows
 */
class IVConsoleSerivce : public VNamedObject, public utils::IVStringStream
{
public:

	virtual ~IVConsoleSerivce() {} ;
	

protected:
	/**
	* a protected constructor is needed to pass the parameters to the 
	* VNamedObject constructor
	*/
	IVConsoleSerivce(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent)
	{
	}
};

//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVCONSOLESERVICE_H

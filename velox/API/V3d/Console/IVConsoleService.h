#ifndef V3D_IVCONSOLESERVICE_H
#define V3D_IVCONSOLESERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VNamedObject.h>
#include <V3d/Utils/IVStringStream.h>

#include <V3dLib/BoostSignals.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace console {
//-----------------------------------------------------------------------------

/**
 * A simple console service using wxWindows
 *
 * @author ins, sheijk
 */
class IVConsoleService : public VNamedObject, public utils::IVStringStream
{
public:
	typedef boost::signal<void (VStringParam)> CommandSignal;
	typedef CommandSignal::slot_type CommandSlot;
	typedef boost::signals::connection CommandConnection;

	virtual ~IVConsoleService() {} ;

	/** register a callback for invoked commands */
	virtual CommandConnection RegisterCommandListener(
		const CommandSlot& slot) = 0;

protected:
	/**
	* a protected constructor is needed to pass the parameters to the 
	* VNamedObject constructor
	*/
	IVConsoleService(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent)
	{
	}
};

//-----------------------------------------------------------------------------
} // namespace console
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVCONSOLESERVICE_H

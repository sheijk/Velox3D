#ifndef V3D_VCOMMANDLISTENER_H
#define V3D_VCOMMANDLISTENER_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/SmartPtr/VGuards.h>
#include <V3d/BoostSignals.h>
#include <V3d/Core/VException.h>
#include <string>

//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;

V3D_DECLARE_EXCEPTION(VCommandManagerException, VException);

/**
 * A class for managing connections between commands and handler functions.
 * A command is any string which may not contain any whitespace. The
 * associated handler will be called every time it's command is entered in the
 * velox console. Any string following the command will be supplied as 
 * arguments. Argument string and command have to be seperated by whitespace
 * A handler must have the following signature: 
 * void f(VStringParam, VStringParam);
 *
 * Example:
 *
 * void OnSay(VStringParam, VStringParam arg)
 * {
 *    vout << "saying: " << arg << vendl;
 * }
 *
 * //...
 * VCommandManager commandManager;
 * commandManager.RegisterCommand("say", &OnSay);
 *
 * @author sheijk
 */
class VCommandManager
{
public:
	typedef boost::signal<void (VStringParam, VStringParam)> Signal;
	typedef Signal::slot_type Slot;
	typedef boost::signals::connection Connection;

	VCommandManager();

	/** Registers a handler for a command */
	void RegisterCommand(VStringParam in_strCommand, const Slot& in_Slot);

	/** Unregisters a command */
	void UnregisterCommand(VStringParam in_strCommand);

	/** returns whether the given command is registered for some handler */
	vbool IsCommandRegistered(std::string in_strCommand);

private:
	/**
	 * A registered listener. Maintains the connection to the listener
	 * and delivers calls to it. Connection will be closed on destruction
	 */
	class Listener
	{
		boost::signals::scoped_connection m_Connection;
        Signal m_Signal;
	
	public:
		Listener(const Slot& in_Slot);

		void Call(VStringParam in_strCommand, VStringParam in_strArgs);
	};

	/** Used to create a slot for handling console commands */
	class Caller
	{
		VCommandManager& m_CommandManager;
	
	public:
		Caller(VCommandManager& mngr);

		void operator()(VStringParam in_strCommandLine);
	};

	typedef std::map<std::string, VPointer<Listener>::SharedPtr> 
		CommandHandlers;

	void OnCommand(VStringParam in_strCommand);

	CommandHandlers m_CommandHandlers;
	Caller m_Caller;
	boost::signals::scoped_connection m_Connection;
};

//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VCOMMANDLISTENER_H

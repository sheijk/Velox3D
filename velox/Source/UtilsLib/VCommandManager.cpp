#include <V3dLib/Utils/VCommandManager.h>
//-----------------------------------------------------------------------------
#include <string>

#include <v3d/Console.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;

VCommandManager::VCommandManager() : m_Caller(*this)
{
	// register at console service
	VServicePtr<v3d::console::IVConsoleService> pConsole;
	m_Connection = pConsole->RegisterCommandListener(m_Caller);
}

void VCommandManager::RegisterCommand(
	VStringParam in_strCommand, 
	const Slot& in_Slot)
{
	std::string strCommand(in_strCommand);

	if( IsCommandRegistered(strCommand) )
	{
		V3D_THROW(VCommandManagerException,
			VString("command \n") + in_strCommand + "\"registered twice");
	}
	else
	{
		VPointer<Listener>::SharedPtr pListener(new Listener(in_Slot));
		m_CommandHandlers[strCommand] = pListener;
	}
}

void VCommandManager::UnregisterCommand(VStringParam in_strCommand)
{
	CommandHandlers::iterator listener = m_CommandHandlers.find(
		std::string(in_strCommand));

	m_CommandHandlers.erase(listener);
}

vbool VCommandManager::IsCommandRegistered(std::string in_strCommand)
{
	return (m_CommandHandlers.find(in_strCommand) 
		!= m_CommandHandlers.end());
}

VCommandManager::Listener::Listener(const Slot& in_Slot)
{
	m_Connection = m_Signal.connect(in_Slot);
}

void VCommandManager::Listener::Call(
	VStringParam in_strCommand, 
	VStringParam in_strArgs)
{
	m_Signal(in_strCommand, in_strArgs);
}

VCommandManager::Caller::Caller(VCommandManager& mngr)
 : m_CommandManager(mngr) 
{
}

void VCommandManager::Caller::operator()(VStringParam in_strCommandLine)
{
	m_CommandManager.OnCommand(in_strCommandLine);
}

void VCommandManager::OnCommand(VStringParam in_strCommand)
{
	using std::string;
	//TODO: use a lexxer to allow any whitespace

	string commandLine(in_strCommand);

	// get command and arguments
	string::iterator iWS = 
		std::find(commandLine.begin(), commandLine.end(), ' ');
	string command(commandLine.begin(), iWS);
	if( iWS != commandLine.end() )
		++iWS;
	string args(iWS, commandLine.end());

	// if command is registered
	CommandHandlers::iterator handler = m_CommandHandlers.find(command);

	if(handler != m_CommandHandlers.end())
	{
		// notify handler
		handler->second->Call(command.c_str(), args.c_str());
	}
}

//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------

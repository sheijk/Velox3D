#ifndef V3D_VCOMMANDLINEPARSER_H
#define V3D_VCOMMANDLINEPARSER_H


//
// *** VCommandLineParser ***
//
// Synopsis:
//    - parses the command line
//
// Description:
//    - Command Line Parser, parses lines like:
//      "demo.exe -fullscreen -x:320 -y:240 -time:50.00 -bpp:32"
//
// History:
//    - based upon Outbreak code posed on flipcode cofd
//

#include <windows.h>
#include <Core/VTypes.h>
#include <string>
#include <vector>


class VCommandLineParser
{
private:

	// Entity data
	struct EntityData {
		std::string sName;
		std::string sValue;
	};

	// Entity list.
	std::vector<EntityData> m_EntityList;

	char m_cSeperator;

	// Trim and sets entity.
	bool AddEntity(const std::string& sEntityName);

	// Trimmer
	std::string Trim(const std::string& sInput);

public:

	// Creates the register of strings
	VCommandLineParser();

	// Call this to parse the line
	void AnalyseCommandLine();

	// default '-', for other register before AnalyseComamndLine();
	void SetSeperator(char Seperator);

	// Check if command is entered, good for detecting "demo.exe /fullscreen"
	const vbool IsEntity(const std::string& sName);

	// Get entity with entered name, for instance, "demo.exe /x:320 /y:240 /bpp:32"
	const std::string GetEntity(const std::string& sName);
};

#endif

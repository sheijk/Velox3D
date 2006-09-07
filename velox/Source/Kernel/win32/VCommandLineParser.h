/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VCOMMANDLINEPARSER_H
#define V3D_VCOMMANDLINEPARSER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
//-----------------------------------------------------------------------------
#include <windows.h>
#include <vector>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
namespace win32 {
//-----------------------------------------------------------------------------

/**
 * Synopsis: parses the command line
 *
 * Description: Command Line Parser, parses lines like:
 *              "demo.exe -fullscreen -x:320 -y:240 -time:50.00 -bpp:32"
 *
 * History:	based upon Outbreak code posted on flipcode cofd
 *
 */

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
	const vchar* GetEntity(const std::string& sName);
};

//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------

#endif //V3D_VCOMMANDLINEPARSER_H

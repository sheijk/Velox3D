#include "VCommandLineParser.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace win32 {
//-----------------------------------------------------------------------------

VCommandLineParser::VCommandLineParser()
{
	m_cSeperator = '-';

}
//-----------------------------------------------------------------------------

const vbool VCommandLineParser::IsEntity(const std::string& sName)
{

	// Loop through entities
	vuint i;
	for (i=0; i< m_EntityList.size(); i++)
	{

		// If match, return true
		if (m_EntityList[i].sName == sName)
			return true;
	}

	return false;
}
//-----------------------------------------------------------------------------

const char* VCommandLineParser::GetEntity(const std::string& sName)
{

	// Loop through entities
	vuint i;
	for (i=0; i<m_EntityList.size(); i++)
		if (m_EntityList[i].sName == sName)
			return m_EntityList[i].sValue.c_str();
	
	return NULL;
}
//-----------------------------------------------------------------------------

std::string VCommandLineParser::Trim(const std::string& sInput)
{

	// If string is empty, there is nothing to look for.
	if (sInput.length() == 0)
		return "";

	// Set up temporary
	std::string final=sInput;

	// Remove spaces at beginning
	vuint i=0;
	while ((i<sInput.length()) && (sInput[i]==' ')) {
		i++;
	}

	// String full of spaces, return nothing.
	if (i >= sInput.length()) return "";

	if (i>0) {
		final = sInput.substr(i, sInput.length()-i);
	}

	// Remove spaces at end
	i= (vuint) final.length()-1;
	while ((i>=0) && (final[i]==' ')) {
		i--;
	}

	final = final.substr(0, i+1);

	// Return the new string
	return final;
}
//-----------------------------------------------------------------------------

bool VCommandLineParser::AddEntity(const std::string& sEntityName)
{

	// Set defaults
	std::string name=sEntityName;
	std::string value="";

	// Loop through and look for ":" to make a value.
	vuint i;
	for (i=1; i<sEntityName.length(); i++) {

		// Found seperator
		if ((sEntityName[i] == ':') || (sEntityName[i] == '=')) {

			// Set name
			name  = sEntityName.substr(0,i);

			// Set value, if any
			if (i+1 < sEntityName.length()) {
				value = sEntityName.substr(i+1, sEntityName.length()-i-1);
			}

			break;
		}
	}

	// Trim values
	name = Trim(name);
	value = Trim(value);

	// Only add if name is valid!
	if (name.length() != 0)
	{

		// Set up entity structure
		EntityData ed;
		ed.sName  = name;
		ed.sValue = value;

		// Add entity
		m_EntityList.push_back(ed);
		return true;
	}

	else
		return false;
}
//-----------------------------------------------------------------------------

void VCommandLineParser::AnalyseCommandLine()
{

	// Get command line arguments
	std::string args = GetCommandLine();

	vint start=-1;

	// Loop through argument line and search for entities.
	vint i;
	for (i=0; i  < (vint)args.length(); i++)
	{

		// Found new entity.
		if (args[i] == m_cSeperator)
		{

			// Only if not first time.
			if ((start != -1) && (start != (i-1))) {

				// Adds entity to the list and trims the value.
				AddEntity(args.substr(start+1, i-start-1));
			}		

			// Store position for next '/'
			start = i;
		}
	}

	// Add remaining string
	if ((start!=-1) && (start < i-1))
		AddEntity(args.substr(start+1, i-start-1));
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
} //namsepace win32
} //namespace v3d
//-----------------------------------------------------------------------------


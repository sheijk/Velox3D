// VStringList.cpp: Implementierung der Klasse VStringList.
//
//////////////////////////////////////////////////////////////////////

//#pragma warning(disable: 4786)
#include "VStringList.h"

using namespace std;
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

VStringList::VStringList()
{

}

VStringList::~VStringList()
{

}

VStringList::iterator VStringList::begin()
{
	return m_Strings.begin();
}

VStringList::iterator VStringList::end()
{
	return m_Strings.end();
}

void VStringList::insert(string str)
{
	m_Strings.insert(str);
}

void VStringList::erase(string str)
{
	m_Strings.erase(str);
}

void VStringList::erase(iterator itString)
{
	m_Strings.erase(itString);
}

VStringList::iterator VStringList::find(string str)
{
	return m_Strings.find(str);
}

VStringList::size_type VStringList::size()
{
	return m_Strings.size();
}

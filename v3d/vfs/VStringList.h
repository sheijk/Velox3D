#ifndef VSTRINGLIST_H
#define VSTRINGLIST_H

#pragma warning(disable: 4786)

#include <Core/vtypes.h>
#include <string>
#include <set>

class VStringList
{
private:
	typedef std::set< std::string > StringGroup;

	StringGroup m_Strings;
public:
	typedef StringGroup::iterator iterator;
	typedef StringGroup::size_type size_type;

	VStringList();
	virtual ~VStringList();

	size_type size();

	iterator end();
	iterator begin();

	void erase( iterator itString );
	void erase( std::string str );
	void insert( std::string str );

	iterator find( std::string str );
};

#endif 

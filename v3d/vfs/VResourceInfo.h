#ifndef VRESOURCE_H
#define VRESOURCE_H

#include <Core/vtypes.h>
#include <string>

enum ELocationType
{
	ltNone,
	ltFile,
	ltArchive,
	ltFtp,
	ltBacksideOfTheMoon
};

struct VResourceInfo
{
	inline VResourceInfo();

	std::string m_strPathAndName;
	ELocationType m_Location;
	vbool m_bReadOnly;
};

VResourceInfo::VResourceInfo() :
	m_strPathAndName(""),
	m_Location(ltNone),
	m_bReadOnly(false)
{
}

#endif
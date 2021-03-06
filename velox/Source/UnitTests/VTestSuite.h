/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VTESTSUITE_H
#define V3D_VTESTSUITE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/IVApplication.h>
#include <v3d/Core/VNamedObject.h>

#include <set>
#include <string>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

class IVUnitTest;

struct VUnitTestInfo
{
	VUnitTestInfo()
	{
		Reset();
	}

	void Reset()
	{
		strName = "no name";
		strSubject = "no subject specified";
		pUnitTest = 0;
	}

	bool operator<(const VUnitTestInfo& other) const
	{
		return (strName < other.strName);
	}

	VString strSubject;
	VString strName;
	IVUnitTest* pUnitTest;
};

class VTestSuite
{
public:
	VTestSuite();
	virtual ~VTestSuite();

	int Main();

private:
	void ExecuteTests();
	void PrintList() const;
	void GenerateTestList();

	typedef std::set<VUnitTestInfo> UnitTestInfoList;

	UnitTestInfoList m_UnitTests;	
};

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTESTSUITE_H


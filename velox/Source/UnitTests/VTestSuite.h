#ifndef V3D_VTESTSUITE_H
#define V3D_VTESTSUITE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

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

	std::string strSubject;
	std::string strName;
	IVUnitTest* pUnitTest;
};

class VTestSuite  
{
public:
	void ExecuteTests();
	void PrintList() const;
	void GenerateTestList();
	VTestSuite();
	virtual ~VTestSuite();

private:
	typedef std::set<VUnitTestInfo> UnitTestInfoList;

	UnitTestInfoList m_UnitTests;	
};

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTESTSUITE_H

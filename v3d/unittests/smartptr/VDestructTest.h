#ifndef V3D_VDESTRUCT_TEST_H
#define V3D_VDESTRUCT_TEST_H

#include <Core/VCoreLib.h>

// constructor sets flag to true, destructor to false
class VDestructTest 
{
private:
	vbool& m_bFlag;

public:
	VDestructTest(bool& io_bDestFlag) : m_bFlag(io_bDestFlag) 
	{
		m_bFlag = true;
	}
	
	~VDestructTest()
	{
		m_bFlag = false;
	}

	void Reset(vbool& nval)
	{
		m_bFlag = nval;
	}
};

#endif
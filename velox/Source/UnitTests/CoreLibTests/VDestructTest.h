#ifndef V3D_VDESTRUCT_TEST_H
#define V3D_VDESTRUCT_TEST_H

// constructor sets flag to true, destructor to false
class VDestructTest 
{
private:
	bool& m_bFlag;

public:
	VDestructTest(bool& io_bDestFlag) : m_bFlag(io_bDestFlag) 
	{
		m_bFlag = true;
	}
	
	~VDestructTest()
	{
		m_bFlag = false;
	}

	void Reset(bool& nval)
	{
		m_bFlag = nval;
	}
};

#endif
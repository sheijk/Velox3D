/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDESTRUCT_TEST_H
#define V3D_VDESTRUCT_TEST_H

//TODO: in namespace tun

// constructor sets flag to true, destructor to false
class VDestructTest 
{
private:
	static bool m_bDummy;
	bool& m_bFlag;

public:
	VDestructTest() : m_bFlag(m_bDummy)
	{
	}

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

bool VDestructTest::m_bDummy = false;

#endif

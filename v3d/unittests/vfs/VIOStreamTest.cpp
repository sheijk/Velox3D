// VIOStreamTest.cpp: Implementierung der Klasse VIOStreamTest.
//
//////////////////////////////////////////////////////////////////////

#include "VIOStreamTest.h"
#include <Vfs/IVStream.h>
#include <Vfs/VMemoryStream.h>

#include <memory.h>

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

//! one instance of IOStreamTest
VREGISTER_UNIT_TEST(VIOStreamTest);


template<class t_type>
class array_ptr
{
private:
	t_type* m_pSubject;

public:
	array_ptr() 
	{
		m_pSubject = 0;
	}

	~array_ptr()
	{
		delete[] m_pSubject;
	}

	void operator=(t_type* in_pNewSubject)
	{
		delete[] m_pSubject;
		m_pSubject = in_pNewSubject;
	}

	t_type* operator->()
	{
		return m_pSubject;
	}

	t_type& operator*()
	{
		return *m_pSubject;
	}

	t_type* addr()
	{
		return m_pSubject;
	}
};

VIOStreamTest::VIOStreamTest()
{

}

VIOStreamTest::~VIOStreamTest()
{

}

/*!
	does a simple read/write test of the stream
*/
IVUnitTest::VTestResult TestIOStreamRW(IVStream* in_Stream)
{
	char* pcTestData = "this is a little test string for IVStream";
	char* pcCheckData = 0;

	// write data to stream
	in_Stream->Write(pcTestData, strlen(pcTestData));

	// reset position pointer
	in_Stream->SetPos(IVStream::begin, 0);

	// read data
	pcCheckData = new char[strlen(pcTestData)];
	in_Stream->Read(pcCheckData, strlen(pcTestData));

	if( memcmp(pcTestData, pcCheckData, strlen(pcTestData)) != 0 )
	{
		delete[] pcCheckData;
		return IVUnitTest::VError;
	}
	else
	{
		delete[] pcCheckData;
		return IVUnitTest::VOk;
	}
}

IVUnitTest::VTestResult TestIOStreamSetpos(IVStream* in_pStream)
{
	array_ptr<char> pcTestData;
	pcTestData = new char[10];
	array_ptr<char> pcCheckData;
	pcCheckData = new char[strlen(pcTestData.addr())];
	
	// write some data
	in_pStream->Write(pcTestData.addr(), strlen(pcTestData.addr()));

	// reset write pos
	in_pStream->SetPos(IVStream::current, -3);

	// write again
	in_pStream->Write("789", 3);

	// back to start
	in_pStream->SetPos(IVStream::begin, 0);

	// read data
	in_pStream->Read(pcCheckData.addr(), strlen(pcTestData.addr()));

	// check data
	if( memcmp(pcTestData.addr(), pcCheckData.addr(), strlen(pcTestData.addr())) != 0 )
	{
		// error
		return IVUnitTest::VError;
	}
	else 
	{
		return IVUnitTest::VOk;
	}
}

/*!
	applies all stream tests to stream
*/
IVUnitTest::VTestResult TestStreamIO(IVStream* in_Stream)
{
	// test simple read write
	return TestIOStreamRW(in_Stream);
}

void VIOStreamTest::GetTestInfo(std::string& out_TestName, std::string& out_SubjectName)
{
	out_TestName = "VIOStreamTest";
	out_SubjectName = "IVStream";
}

IVUnitTest::VTestResult VIOStreamTest::ExecuteTest()
{
	VMemoryStream theMemStream;

	return TestStreamIO(&theMemStream);
}

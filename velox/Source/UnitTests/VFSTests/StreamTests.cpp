#include "StreamTests.h"
//-----------------------------------------------------------------------------
#include <v3d/VFS/IVStream.h>
#include <v3d/UnitTests/VUnitTestException.h>

#include <cstring>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------
using v3d::vfs::IVStream;

//TODO: v3d smart pointer fuer arrays benutzen
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

	array_ptr(t_type* in_pVal)
	{
		m_pSubject = in_pVal;
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

//-----------------------------------------------------------------------------

//TODO: tests fuer IVOfflineStreams: schreiben/lesen, pos., zugriffsrechte

void TestStreamRW(IVUnitTest* in_pTest, vfs::IVStream* in_pStream)
{
	vchar* pTestData = "Dies sind einige dusselig Testdaten";
	const vuint nTestDataLen = strlen(pTestData);
	array_ptr<vchar> pTestRes = new vchar[nTestDataLen];

	// save stream pos
	IVStream::StreamPos nOriginalStreamPos = in_pStream->GetPos();

	// write some data to stream
	in_pStream->Write(pTestData, nTestDataLen);

	// reset to previous pos
	in_pStream->SetPos(IVStream::Begin, nOriginalStreamPos);

	// read it out
	in_pStream->Read(pTestRes.addr(), nTestDataLen);

	// compare data
	if( memcmp(pTestData, pTestRes.addr(), nTestDataLen) != 0 )
	{
		V3D_UNITTEST_FAILURE_STATIC("IVStream read/write test failed", 
			VUnitTestException::CriticalError);
	}
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------

#include "StreamTests.h"
//-----------------------------------------------------------------------------
#include <v3d/VFS/IVStream.h>
#include <v3d/VFS/VStreamOps.h>
#include <v3d/UnitTests/VUnitTestException.h>

#include <cstring>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------
using v3d::vfs::IVStream;
using namespace v3d::vfs;

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

void TestStreamOps(IVStream& stream)
{
	vint v = 5, v2 = 3;
	IVStream::ByteCount pos = stream.GetPos();

	stream << v;
	stream.SetPos(IVStream::Begin, pos);
	stream >> v2;

	if( v != v2 )
	{
        V3D_UNITTEST_ERROR_STATIC("op<</>>(IVStream&, vint) failed");
	}

	stream.SetPos(IVStream::Begin, pos);

	vint8 i8 = 8;
	vint16 i16 = 16;
	vint32 i32 = 32;
	vint64 i64 = 64;

	vint8 i8_2 = 0;
	vint16 i16_2 = 0;
	vint32 i32_2 = 0;
	vint64 i64_2 = 0;

	stream << i8 << i16 << i32 << i64;
	stream.SetPos(IVStream::Begin, pos);
	stream >> i8_2 >> i16_2 >> i32_2 >> i64_2;

	if( i8 != i8_2 || i16 != i16_2 || i32 != i32_2 || i64 != i64_2 )
	{
		V3D_UNITTEST_ERROR_STATIC("op<</>>(IVStream,int*) failed");
	}

	vfloat32 f32 = 32.32, f32_2 = 0;
	vfloat64 f64 = 64.64, f64_2 = 0;
	
	stream.SetPos(IVStream::Begin, pos);
	stream << f32 << f64;
	stream.SetPos(IVStream::Begin, pos);
	stream >> f32_2 >> f64_2;

	if( f64 != f64_2 || f32 != f32_2 )
	{
		V3D_UNITTEST_ERROR_STATIC("op<</>>(IVStream&,vfloat*) failed");
	}

	vbool b = true, b_2 = false;

	stream.SetPos(IVStream::Begin, pos);
	stream << b;
	stream.SetPos(IVStream::Begin, pos);
	stream >> b_2;

	if( b != b_2 )
	{
		V3D_UNITTEST_ERROR_STATIC("op<</>>(IVStream&,vbool) failed");
	}
}

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

	TestStreamOps(*in_pStream);
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------

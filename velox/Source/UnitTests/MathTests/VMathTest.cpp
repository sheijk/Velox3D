#include "VMathTest.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/VException.h>
#include <v3d/UnitTests/IVTestManager.h>
#include <v3d/UnitTests/VUnitTestException.h>

#include <v3d/Math/VMatrix.h>
#include <v3d/Math/VVector.h>
#include <v3d/Math/VMatrixOps.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

VMathTest::VMathTest()
{
	IVTestManager* pTestManager = 0;

	// register unit test
	pTestManager = QueryObject<IVTestManager>("testmngr");

	if( ! pTestManager ) 
	{
		V3D_THROW(VException, "test manager could not be found");
	}

	pTestManager->AddCommonTest(this);
}

VMathTest::~VMathTest()
{
}

//TODO: add info
void VMathTest::GetTestInfo(
	VString& out_TestName, 
	VString& out_SubjectName)
{
	// set the name
	out_TestName = "MathTests";

	// specifiy the subject of the whole thing
	out_SubjectName = "VMatrix";
}


//TODO: implement test
void VMathTest::ExecuteTest()
{
	{
		typedef VMatrix<float, 4, 3> Matrix43f;
		typedef VMatrix<float, 3, 5> Matrix35f;
		typedef VMatrix<float, 4, 5> Matrix45f;

		Matrix43f mat1;
		Matrix35f mat2;
		Matrix45f res;

		Mult(res, mat1, mat2);
	}

	{
		typedef VMatrix<float, 4, 4> Matrix44f;

		Matrix44f r, a, b;
		
		// compile tests
		Identity(r);
		Add(r, a, b);
		Sub(r, a, b);
		Mult(r, a, b);

		r = a + b - a * b;
		r += a;
		r -= b;
		r *= a;

		MakeInverse(r);
		MakeTranspose(r);
	}

	{
		typedef VVector<float, 3> Vector3f;

		Vector3f r, a, b;
		float f;

		Add(r, a, b);
		Sub(r, a, b);

		r = a + b - a;
		r += a;
		r -= b;

		ApplyCross(r, a, b);
		r = Cross(a, b);

		f = Dot(a, b);

		Mult(r, .2);
		r *= .2f;
		r = r * .2;
		r = 2 * r;

		Normalize(r);
		f = Length(r);
		f = LengthSquared(r);
	}

	{
		typedef VVector<float, 4> Vector4f;
		typedef VMatrix<float, 3, 4> Matrix34f;

		Vector4f v4f, v4f2;
		Matrix34f m34f;
		
		Mult(v4f2, m34f, v4f);
	}
}

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------

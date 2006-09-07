/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSmartPointerTest_H
#define V3D_VSmartPointerTest_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/UnitTests/IVUnitTest.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------

/**
//TODO: insert documentation here
*/
class VSmartPointerTest : public IVUnitTest
{
public:
	VSmartPointerTest();
	virtual ~VSmartPointerTest();

	/*! @see IVUnitTest#GetTestInfo(VStringParam, VStringParam) */
	virtual void GetTestInfo(
		VString& out_TestName, 
		VString& out_SubjectName);

	/*! @see IVUnitTest#Execute() */
	virtual void ExecuteTest();

private:
	void TestAutoPtr();
	void TestRefCountPtr();
	void TestAutoArray();
	void TestIteratorPtr();
	void TestIterator();
};

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSmartPointerTest_H


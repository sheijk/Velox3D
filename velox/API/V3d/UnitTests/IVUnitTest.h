/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVUNITTEST_H
#define V3D_IVUNITTEST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace unittests {
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

/**
 *	abstract interface for all unit tests
 */
class IVUnitTest
{
public:
	/*!
		returns the name of the test and the name of the subject to 
		be tested
	*/
	virtual void GetTestInfo(
		VString& out_TestName, 
		VString& out_SubjectName) = 0;

	/*!
		executes the test. must catch all exceptions
	*/
	virtual void ExecuteTest() = 0;

	virtual ~IVUnitTest() {};
};

//-----------------------------------------------------------------------------
} // namespace unittests
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVUNITTEST_H


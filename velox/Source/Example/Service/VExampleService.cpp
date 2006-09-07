/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VExampleService.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace example {
//-----------------------------------------------------------------------------

VExampleService::VExampleService(VStringParam in_strName) :
	IVExampleService(in_strName, 0)
{

}

VExampleService::~VExampleService()
{

}

vint VExampleService::GiveMeFive()
{
	return 5;
}

//-----------------------------------------------------------------------------
} // example
} // v3d
//-----------------------------------------------------------------------------



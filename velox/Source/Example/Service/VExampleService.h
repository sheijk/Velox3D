/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VEXAMPLESERVICE_H
#define V3D_VEXAMPLESERVICE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VNamedObject.h>
#include <v3d/ExampleService/IVExampleService.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace example {
//-----------------------------------------------------------------------------

/**
 * A service which implements the example interface
 */
class VExampleService : public IVExampleService
{
public:
	VExampleService(VStringParam in_strName);
	virtual ~VExampleService();
public:
	virtual vint GiveMeFive();
	
};

//-----------------------------------------------------------------------------
} // example 
} // v3d
//-----------------------------------------------------------------------------
#endif // V3D_VEXAMPLESERVICE_H


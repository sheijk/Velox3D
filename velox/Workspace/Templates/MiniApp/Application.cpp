/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Core.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d;

class %%name%%App : public VVeloxApp
{
public:
	virtual vint Main(std::vector<std::string> args);
};

vint %%name%%App::Main(std::vector<std::string> args)
{
	vout << "Hello velox" << vendl;
	
	return 0;
}

//-----------------------------------------------------------------------------
namespace {
	%%name%%App g_theApp;
}


#include <V3d/Core.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
using namespace v3d;

class MinimalApp : public VVeloxApp
{
public:
	virtual vint Main(std::vector<std::string> args);
};

vint MinimalApp::Main(std::vector<std::string> args)
{
	vout << "Hello velox" << vendl;
	
	return 0;
}

//-----------------------------------------------------------------------------
namespace {
	MinimalApp g_theApp;
}

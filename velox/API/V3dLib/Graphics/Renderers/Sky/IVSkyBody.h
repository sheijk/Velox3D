#ifndef V3D_IVSKYBODY_2004_04_26_H
#define V3D_IVSKYBODY_2004_04_26_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3dLib/Graphics/SimpleSG.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
namespace sky {

using namespace v3d;
using namespace v3d::graphics;
	
//-----------------------------------------------------------------------------
class IVSkyBody
{
	public:
		//typedef VPointer<IVNode>::AutoPtr NodePointer; 
		typedef IVNode* NodePointer;

		virtual ~IVSkyBody() {;};
		virtual IVNode* GetNode() = 0;
};
//-----------------------------------------------------------------------------
}// namespace sky
}// namespace graphics
}// namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVSKYBODY_2004_04_26_H

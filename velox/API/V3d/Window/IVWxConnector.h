#ifndef V3D_IVWXCONNECTOR_H
#define V3D_IVWXCONNECTOR_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Core/Wrappers/VIterator.h>
//-----------------------------------------------------------------------------
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------
class IVWindowFrame;

/**
 *	Manages all IVConnectable classes
 */

class IVWxConnector
{
public:

	typedef std::vector<IVWindowFrame*> VFrameList;

	virtual void Register(IVWindowFrame* in_pFrame) = 0;
	virtual void Unregister(IVWindowFrame* in_pFrame) = 0;

	//Test
	virtual IVWindowFrame* GetCurrentFrame() = 0;
	virtual vuint GetNumElements() = 0;

			
	virtual ~IVWxConnector(){};
};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVWXCONNECTOR_H

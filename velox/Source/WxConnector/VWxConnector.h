#ifndef V3D_VWXCONNECTOR_H
#define V3D_VWXCONNECTOR_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VNamedObject.h>
#include <v3d/Window/IVWxConnector.h>
//-----------------------------------------------------------------------------
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------


class VWxConnector : public IVWxConnector, public VNamedObject
{
public:

	VWxConnector();
	virtual ~VWxConnector();

	void Register(IVWindowFrame* in_pFrame);
	void Unregister(IVWindowFrame* in_pFrame);
	
	//Test
	
	virtual IVWindowFrame* GetCurrentFrame();
	virtual vuint GetNumElements();
	
private:
	
	vuint m_iNumElements;
	std::vector<IVWindowFrame*> m_FrameList;
};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VWXCONNECTOR_H

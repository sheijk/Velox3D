#ifndef V3D_VMESHHANDLE_2004_11_07_H
#define V3D_VMESHHANDLE_2004_11_07_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Graphics/IVDevice.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VMeshBase;

/**
 */
class VMeshHandle
{
public:
	VMeshHandle(VMeshBase* in_hBuffer);
	virtual ~VMeshHandle();

	VMeshBase* GetGLMesh() const;

private:
	VMeshBase* m_pMesh;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VMESHHANDLE_2004_11_07_H

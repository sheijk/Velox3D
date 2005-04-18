#ifndef V3D_IVMATERIAL_H
#define V3D_IVMATERIAL_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
//----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
class IVRenderState;

class IVPass
{
public:
	virtual ~IVPass() {};
	virtual vuint StateCount() const = 0;
	virtual const IVRenderState& GetState(vuint in_nPriority) const = 0;
};

/**
 * Client visible material controlling
 *
 * @author sheijk
 */
class IVMaterial
{
public:	
	virtual ~IVMaterial() {};

	virtual vuint PassCount() const = 0;
	virtual const IVPass& GetPass(vuint in_nNum) const = 0;
//	virtual vuint StateCount() const = 0;  // number of states
//	virtual const IVRenderState& GetState(vuint in_nPriority) const = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVMATERIAL_H

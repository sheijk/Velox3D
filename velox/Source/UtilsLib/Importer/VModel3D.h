//-----------------------------------------------------------------------------
#ifndef V3D_VMODEL3D_H
#define V3D_VMODEL3D_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
#include <vector>
#include "VModelObject3D.h"
//-----------------------------------------------------------------------------
namespace v3d{
namespace util{
namespace importer{
//-----------------------------------------------------------------------------
/**
 * @version 1.0
 * @created 13-Jan-2004 23:26:51
 * @author ins
 */
class VModel3D
{

public:
	VModel3D();
	~VModel3D();
	std::vector<VModelObject3D*> m_Objects;

};
//-----------------------------------------------------------------------------
} // namespace util
} // namespace v3d
} // namespace importer
//-----------------------------------------------------------------------------
#endif // V3D_VMODEL3D_H
//-----------------------------------------------------------------------------
#ifndef V3D_IVMODELIMPORTER_H
#define V3D_IVMODELIMPORTER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
#include "VModel3D.h"
//-----------------------------------------------------------------------------
namespace v3d{
namespace utils{
namespace importer{
//-----------------------------------------------------------------------------
/**
 * @version 1.0
 * @created 13-Jan-2004 23:51:43
 * @author ins
 */
class IVModelImporter
{
public:
	/* Loads a model out of the file and save to Model param */
	virtual void Create(VStringParam sFilename, VModel3D* Model) = 0;
};
//-----------------------------------------------------------------------------
} // namespace importer
} // namespace util
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVMODELIMPORTER_H
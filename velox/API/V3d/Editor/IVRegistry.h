#ifndef V3D_IVREGISTRY_2004_05_05_H
#define V3D_IVREGISTRY_2004_05_05_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Editor/IVPlugin.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * A registry for editor plugins
 *
 * @author sheijk
 */
class IVRegistry
{
public:
	virtual void RegisterPlugin(IVPlugin& in_Plugin) = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_IVREGISTRY_2004_05_05_H

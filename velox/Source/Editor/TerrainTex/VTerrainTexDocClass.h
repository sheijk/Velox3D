#ifndef V3D_VTEXTURETEXDOCCLASS_2004_06_18_H
#define V3D_VTEXTURETEXDOCCLASS_2004_06_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Editor/IVDocumentClass.h>

//#include "VTextureStageSetupFrame.h"

#include <wx/wx.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VTerrainTexDocClass : public IVDocumentClass
{
public:
	virtual DocumentPtr Create(wxWindow* in_pParent);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_VTEXTURETEXDOCCLASS_2004_06_18_H

#include "VTerrainTexDocClass.h"
//-----------------------------------------------------------------------------
#include <v3d/Core/VIOStream.h>
#include "VTerrainTexDocument.h"
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

IVDocumentClass::DocumentPtr VTerrainTexDocClass::Create(wxWindow* in_pParent)
{
	// show options dialog
	wxArrayString choiceMessages;
	choiceMessages.Add("256x256");
	choiceMessages.Add("512x512");
	choiceMessages.Add("1024x1024");
	choiceMessages.Add("2048x2048");
	choiceMessages.Add("4096x4096");

	vint choice = wxGetSingleChoiceIndex(
		"Please select a texture size",
		"New Terrain Texture",
		choiceMessages,
		in_pParent
		);

	// extract options
	vuint size = 0;

	switch(choice)
	{
	case 0: size = 256; break;
	case 1: size = 512; break;
	case 2: size = 1024; break;
	case 3: size = 2048; break;
	case 4: size = 4096; break;
	default: return DocumentPtr(0);
	}

	DocumentPtr pDoc(new VTerrainTexDocument(in_pParent, size, size));

	vout << "created terrain texture of size " 
		<< size << "x" << size << vendl;

	return pDoc;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------

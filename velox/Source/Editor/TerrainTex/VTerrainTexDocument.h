#ifndef V3D_VTERRAINTEXDOCUMENT_2004_06_18_H
#define V3D_VTERRAINTEXDOCUMENT_2004_06_18_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Editor/IVDocument.h>
#include <v3d/Editor/IVMessage.h>

#include <V3dLib/Graphics/Misc/VSimpleDrawList.h>

#include "VTerrainTexGenPreviewFrame.h"
#include "VTextureStage.h"
#include "VTextureStageSetupFrame.h"

#include <vector>
#include <wx/wx.h>
#include <wx/tbarsmpl.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

class VRenderPanel : public wxPanel
{
public:
	VRenderPanel(wxWindow* in_pParent, wxPoint in_Pos, wxSize in_Size);
	v3d::graphics::IVDevice& GetDevice();
	const v3d::graphics::IVDevice& GetDevice() const;

private:
	v3d::window::IVWindowManager::GraphicsDevicePtr m_pDevice;
};

class VTerrainTexDocument : public wxMiniFrame, public IVDocument
{
public:
	VTerrainTexDocument(
		wxWindow* in_pParent, 
		vuint in_nWidth, 
		vuint in_nHeight);

	virtual Connection RegisterFocusListener(const FocusSlot& in_Slot);
	virtual void SetWindowMode(WindowMode in_Mode);
	virtual VMessageTreatment DeliverMessage(IVMessage& in_Message);

private:
	// document
	typedef std::vector<VTextureStage> TextureStageList;

	void UpdateTexStageListBox();
	void Render();

	VPointer<v3d::graphics::VSimpleDrawList>::SharedPtr m_pDrawList;

	TextureStageList m_TextureStages;

	// user interface
	enum Ids
	{
		TimerId = 1
	};

	void OnRegularUpdate(wxTimerEvent& in_Event);

    wxPanel* m_pTexStagePanel;
	wxListBox* m_pTexStageListBox;
	VRenderPanel* m_pRenderPanel;
	wxToolBarSimple* m_pToolbar;

	wxTimer* m_pTimer;

	DECLARE_EVENT_TABLE();
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_VTERRAINTEXDOCUMENT_2004_06_18_H

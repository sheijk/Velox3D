/*


class VTextureStageSetupFrame : public wxMiniFrame
{
public:
	VTextureStageSetupFrame(wxWindow* in_pParent) :
		wxMiniFrame(
			in_pParent,
			-1,
			"Texture Stages",
			wxPoint(0, 0),
			wxSize(150, 300),
			wxTINY_CAPTION_HORIZ | wxFRAME_FLOAT_ON_PARENT | wxFRAME_NO_TASKBAR
			),
		m_pListBox(0)
	{
		wxPoint parentPos = in_pParent->ClientToScreen(wxPoint(0,15));
		wxSize parentSize = in_pParent->GetSize();

		SetSize(
			parentPos.x + parentSize.GetWidth() - GetSize().GetWidth(), 
			parentPos.y + 5, 
			-1, -1);

		m_pListBox = new wxListBox(
			this,
			-1,
			wxPoint(0, 0),
			GetClientSize(),
			0,
			NULL
			);		
	}

private:
	wxListBox* m_pListBox;
};

class VTerrainTexGenEditor : public VEditorBase
{
public:
	VTerrainTexGenEditor() 
		: 
		VEditorBase("TerrTex"),
		m_pWindow(0),
		m_pTexWindow(0)
	{
		AddAction(ActionPtr(new VPrintAction("Show Heightmap")));
		AddAction(ActionPtr(new VPrintAction("Show Texture")));
	}

	virtual void Enable(wxWindow* in_pParent)
	{
		if(! m_pWindow)
		{
			m_pTexWindow = new VTextureStageSetupFrame(in_pParent);
			m_pTexWindow->Show(true);

			m_pWindow = new VTerrainTexGenPreviewFrame(in_pParent);
			m_pWindow->Show(true);
		}
	}

	virtual VMessageTreatment DeliverMessage(IVMessage& in_Message)
	{
		vout << "terr tex received a message" << vendl;

		return MessageIgnored;
	}

	graphics::IVDevice& GetDevice()
	{
		V3D_ASSERT(m_pWindow != 0);
		return m_pWindow->QueryDevice();
	}

private:
	VTerrainTexGenPreviewFrame* m_pWindow;
	VTextureStageSetupFrame* m_pTexWindow;
};
*/


//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------





















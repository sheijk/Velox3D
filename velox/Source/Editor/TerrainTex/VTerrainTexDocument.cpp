#include "VTerrainTexDocument.h"
//-----------------------------------------------------------------------------
#include <V3dLib/Graphics.h>
#include <V3dLib/Math.h>

#include "Messages.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

VRenderPanel::VRenderPanel(
	wxWindow* in_pParent, 
	wxPoint in_Pos, 
	wxSize in_Size
	) :
	wxPanel(
		in_pParent,
		-1,
		in_Pos,
		in_Size
		)
{
	VServicePtr<window::IVWindowManager> pWinManager;

	graphics::VDisplaySettings settings;
	settings.m_bFullscreen = false;
	settings.m_sAPIType = "OpenGL";
	settings.m_iWinCoordX = in_Pos.x;
	settings.m_iWinCoordY = in_Pos.y;
	settings.m_iWidth = GetSize().GetWidth();
	settings.m_iHeight = GetSize().GetHeight();

	m_pDevice = pWinManager->CreateGraphicsDevice(settings, (void*)GetHandle());
}

v3d::graphics::IVDevice& VRenderPanel::GetDevice()
{
	return *m_pDevice;
}

const v3d::graphics::IVDevice& VRenderPanel::GetDevice() const
{
	return *m_pDevice;
}

//-----------------------------------------------------------------------------

VTerrainTexDocument::VTerrainTexDocument(
	wxWindow* in_pParent, 
	vuint in_nWidth, 
	vuint in_nHeight)
	:
	wxMiniFrame(
		in_pParent,
		-1, 
		"Terrain Texture",
        wxPoint(0, 0),
		wxSize(640, 480),
		wxTINY_CAPTION_HORIZ | wxFRAME_FLOAT_ON_PARENT | wxFRAME_NO_TASKBAR
		)
{
	using namespace v3d::graphics;

	CenterOnParent();
	this->wxMiniFrame::Show(true);

	//m_pToolbar = new wxToolBarSimple(this);
	CreateToolBar();
	wxToolBar* pToolbar = GetToolBar();

	wxBitmap plus("icons/plus.bmp", wxBITMAP_TYPE_BMP);
	plus.SetMask(new wxMask(plus, wxColour(255, 255, 255)));
	pToolbar->AddTool(AddTexStageId, plus, wxNullBitmap, false, 5, 0, NULL, "Add texture stage");

	wxBitmap redx("icons/redx.bmp", wxBITMAP_TYPE_BMP);
	redx.SetMask(new wxMask(redx, wxColour(255, 255, 255)));
	pToolbar->AddTool(RemoveTexStageId, redx, wxNullBitmap, false, 5, 0, NULL, "Delete texture stage");

	pToolbar->Realize();
	pToolbar->SetRows(1);

	// create texture stage panel
    m_pTexStagePanel = new wxPanel(
		this,
		-1,
		wxPoint(GetClientRect().GetX(), GetClientRect().GetY()),
		wxSize(100, GetClientSize().GetHeight())
		);

	m_pTexStageListBox = new wxListBox(
		m_pTexStagePanel,
		-1,
		wxPoint(0, 0),
		m_pTexStagePanel->GetClientSize()
		);

	UpdateTexStageListBox();

	const vuint renderPanelRight = m_pTexStagePanel->GetRect().GetRight();

	m_pRenderPanel = new VRenderPanel(
		this,
		wxPoint(renderPanelRight, GetClientRect().GetTop()),
		wxSize(
			GetClientSize().GetWidth() - renderPanelRight,
			GetClientSize().GetHeight()
			)
		);

	m_pRenderPanel->SetBackgroundColour(wxColour(255, 0, 0));

	m_pTimer = new wxTimer(this, TimerId);
	m_pTimer->Start(100);

	m_pDrawList.Assign(new VSimpleDrawList(m_pRenderPanel->GetDevice()));

	// create preview mesh
	VMaterialDescription mat;

	VQuadMesh<VSimpleVertex> quadMesh(1.0f);

	IVDevice& device(m_pRenderPanel->GetDevice());

	IVDevice::MeshHandle hMesh = BuildMesh(device, quadMesh, mat);
	
	m_pDrawList->Add(VModel(hMesh, math::IdentityPtr()));

	// load data

	VCamera cam;
	cam.Strafe(1.0f);
	cam.MoveUp(1.0f);
	cam.MoveForward(-3);
	device.SetMatrix(IVDevice::ViewMatrix, cam.TransformMatrix());

	Render();
}

void VTerrainTexDocument::UpdateTexStageListBox()
{
	m_pTexStageListBox->Clear();

	for(vuint stageId = 0; stageId < m_TextureStages.size(); ++stageId)
	{
		m_pTexStageListBox->Append(
			m_TextureStages[stageId].GetTextureFileName().AsCString());
	}
}

VMessageTreatment VTerrainTexDocument::DeliverMessage(IVMessage& in_Message)
{
	vout << "hello message" << vendl;

	if( in_Message.IsOfType<VTextureStageUpdated>() )
	{
		Render();

		return MessageProcessed;
	}
	else
	{
		return MessageIgnored;
	}
}

void VTerrainTexDocument::Render()
{
	v3d::graphics::IVDevice& device(m_pRenderPanel->GetDevice());

	device.BeginScene();
	m_pDrawList->Render();
	device.EndScene();
}

IVDocument::Connection VTerrainTexDocument::RegisterFocusListener(
	const FocusSlot& in_Slot)
{
	//return m_pPreviewWindow->RegisterFocusListener(in_Slot);
	return IVDocument::Connection();
}

void VTerrainTexDocument::SetWindowMode(WindowMode in_Mode)
{
	switch(in_Mode)
	{
	case IVDocument::Hide:
		{
			this->wxMiniFrame::Show(true);
		} break;
	case IVDocument::Show:
		{
			this->wxMiniFrame::Show(false);
		} break;
	}
}

void VTerrainTexDocument::OnRegularUpdate(wxTimerEvent& in_Event)
{
	Render();
}

void VTerrainTexDocument::OnAddTexStage(wxCommandEvent& in_Event)
{
	wxString filename = wxGetTextFromUser("Please enter a vfs file name");

	try
	{
		if( filename != "" )
		{
			m_TextureStages.push_back(VTextureStage(filename));

			UpdateTexStageListBox();
		}
	}
	catch(VException& e)
	{
		std::string message = "Could not find file: ";
		message += e.GetErrorString().AsCString();

		wxMessageBox(message.c_str(), "Error");
	}
}

void VTerrainTexDocument::OnRemoveTexStage(wxCommandEvent& in_Event)
{
	vuint selection = m_pTexStageListBox->GetSelection();

	if( selection >= 0 && selection < m_pTexStageListBox->GetCount() )
	{
		m_TextureStages.erase(m_TextureStages.begin()+selection);

		UpdateTexStageListBox();
	}
}

BEGIN_EVENT_TABLE(VTerrainTexDocument, wxMiniFrame)
EVT_TIMER(TimerId, OnRegularUpdate)
EVT_TOOL(AddTexStageId, OnAddTexStage)
EVT_TOOL(RemoveTexStageId, OnRemoveTexStage)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------

#include "VTerrainTexDocument.h"
//-----------------------------------------------------------------------------
#include <V3dLib/Graphics.h>
#include <V3dLib/Math.h>

#include "Messages.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------

VTerrainTexDocument::VTerrainTexDocument(wxWindow* in_pParent, vuint in_nWidth, vuint in_nHeight)
{
	using namespace v3d::graphics;

	m_pPreviewWindow = new VTerrainTexGenPreviewFrame(in_pParent, *this);
	m_pPreviewWindow->Show(true);

	m_pDrawList.Assign(new VSimpleDrawList(m_pPreviewWindow->QueryDevice()));

	// create preview mesh
	VMaterialDescription mat;

	VQuadMesh<VSimpleVertex> quadMesh(1.0f);

	IVDevice::MeshHandle hMesh = 
		BuildMesh(m_pPreviewWindow->QueryDevice(), quadMesh, mat);
	
	m_pDrawList->Add(VModel(hMesh, math::IdentityPtr()));

	// load data
	IVDevice& device(m_pPreviewWindow->QueryDevice());

	VCamera cam;
	cam.Strafe(1.0f);
	cam.MoveUp(1.0f);
	cam.MoveForward(-3);
	device.SetMatrix(IVDevice::ViewMatrix, cam.TransformMatrix());

	Render();
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
	v3d::graphics::IVDevice& device(m_pPreviewWindow->QueryDevice());

	device.BeginScene();
	m_pDrawList->Render();
	device.EndScene();
}

IVDocument::Connection VTerrainTexDocument::RegisterFocusListener(
	const FocusSlot& in_Slot)
{
	return m_pPreviewWindow->RegisterFocusListener(in_Slot);
}

void VTerrainTexDocument::SetWindowMode(WindowMode in_Mode)
{
	switch(in_Mode)
	{
	case Hide:
		{
			m_pPreviewWindow->Show(true);
		} break;
	case Show:
		{
			m_pPreviewWindow->Show(false);
		} break;
	}
}


//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------

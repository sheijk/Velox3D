#include "VWxCOnnector.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------


VWxConnector::VWxConnector() : VNamedObject("wx.connector", 0)
{
	m_iNumElements = 0;
}
VWxConnector::~VWxConnector()
{
}

void VWxConnector::Register(IVWindowFrame* in_pFrame)
{
	m_FrameList.push_back(in_pFrame);
}

void VWxConnector::Unregister(IVWindowFrame* in_pFrame)
{
	//TODO
	//m_FrameList.remove(in_pFrame);
}

IVWindowFrame* VWxConnector::GetCurrentFrame()
{
	m_iNumElements++;
	if(m_iNumElements <= (m_FrameList.size()-1))
		return m_FrameList[m_iNumElements];

	else
	{
		m_iNumElements = 0;
		return m_FrameList[0];
	}
}

vuint VWxConnector::GetNumElements()
{
	return m_FrameList.size();
}

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------

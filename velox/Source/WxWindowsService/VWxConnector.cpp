#include "VWxCOnnector.h"

//-----------------------------------------------------------------------------
namespace v3d {
namespace wxwindows {
//-----------------------------------------------------------------------------

VWxConnector::VWxConnector(VStringParam in_Name) :	VNamedObject(in_Name, 0)
{
	m_iNumElements = 0;
}
//-----------------------------------------------------------------------------

VWxConnector::~VWxConnector()
{
}
//-----------------------------------------------------------------------------

void VWxConnector::Register(IVWindowFrame* in_pFrame)
{
	m_FrameList.push_back(in_pFrame);
}
//-----------------------------------------------------------------------------

void VWxConnector::Unregister(IVWindowFrame* in_pFrame)
{
	//TODO
	//m_FrameList.remove(in_pFrame);
}
//-----------------------------------------------------------------------------

IVWindowFrame* VWxConnector::GetCurrentFrame()
{
	m_iNumElements++;
	if(m_iNumElements <= m_FrameList.size())
		return m_FrameList[m_iNumElements-1];

	else
	{
		m_iNumElements = 0;
		return m_FrameList[0];
	}
}
//-----------------------------------------------------------------------------

vuint VWxConnector::GetNumElements()
{
	return m_FrameList.size();
}

//-----------------------------------------------------------------------------
} // namespace wxwindows
} // namespace v3d
//-----------------------------------------------------------------------------

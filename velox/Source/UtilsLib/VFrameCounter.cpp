/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Utils/VFrameCounter.h>
//-----------------------------------------------------------------------------
#include <cstdio>
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
//-----------------------------------------------------------------------------

VFrameCounter::VFrameCounter(vuint in_nHistoryLen)
	: m_nHistoryLen(in_nHistoryLen)
{
  if( m_nHistoryLen == 0 )
	V3D_THROW(VException, "history length must be greater > 0");
	for( ; in_nHistoryLen > 0; --in_nHistoryLen)
	{
		m_LastFrameDurations.push_front(0.0f);
	}
}

void VFrameCounter::LogFrameDuration(vfloat32 in_fDuration)
{
	m_LastFrameDurations.pop_front();
	m_LastFrameDurations.push_back(in_fDuration);
}

void VFrameCounter::LogLastFrameDuration()
{
	LogFrameDuration(vfloat32(UpdateManager().GetFrameDuration()));
}

vfloat32 VFrameCounter::GetAverageFPS() const
{
	const vfloat32 fFrameFactor = 1.0f / (vfloat32) m_nHistoryLen;
	vfloat32 fAverage = 0.0f;

	std::list<vfloat32>::const_iterator fps = m_LastFrameDurations.begin();
	for( ; fps != m_LastFrameDurations.end(); ++fps )
	{
		fAverage += fFrameFactor * (*fps);
	}

	return 1.0f / fAverage;
}

const char* VFrameCounter::GetFPSString() const
{
	std::sprintf(m_strFPSString, "fps = %d", vint(GetAverageFPS()));

	return m_strFPSString;
}

v3d::updater::IVUpdateManager& VFrameCounter::UpdateManager()
{
	return *VServicePtr<v3d::updater::IVUpdateManager>();
}

//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------


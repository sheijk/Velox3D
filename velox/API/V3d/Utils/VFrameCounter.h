/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VFRAMECOUNTER_2004_05_27_H
#define V3D_VFRAMECOUNTER_2004_05_27_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Updater.h>

#include <list>

//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Calculates the average fps of the last n frames
 *
 * @author sheijk
 */
class VFrameCounter
{
public:
	explicit VFrameCounter(vuint in_nHistoryLen);

	void LogFrameDuration(vfloat32 in_fDuration);
	void LogLastFrameDuration();

	vfloat32 GetAverageFPS() const;

	const char* GetFPSString() const;

private:
	v3d::updater::IVUpdateManager& UpdateManager();

	const vuint m_nHistoryLen;
	std::list<vfloat32> m_LastFrameDurations;
	mutable char m_strFPSString[100];
};

//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VFRAMECOUNTER_2004_05_27_H


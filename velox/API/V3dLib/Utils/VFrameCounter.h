#ifndef V3D_VFRAMECOUNTER_2004_05_27_H
#define V3D_VFRAMECOUNTER_2004_05_27_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

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

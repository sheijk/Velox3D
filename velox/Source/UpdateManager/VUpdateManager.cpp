#include "VUpdateManager.h"
//-----------------------------------------------------------------------------
#include <v3d/Updater/IVUpdateable.h>
#include <algorithm>
#include <functional>
#include <v3d/Core/MemManager.h>

using namespace std;
//-----------------------------------------------------------------------------
namespace v3d {
namespace updater {
//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VUpdateManager::VUpdateManager(VStringParam in_strId)
	: IVUpdateManager(in_strId)
{
	m_pTimer = 0;

	// instanciate VTimer here
	m_pTimer = new VPerformanceCounter();


}

/**
 * d'tor
 */
VUpdateManager::~VUpdateManager()
{
}

void VUpdateManager::Register(IVUpdateable* in_pObject)
{
	my_Subjects.push_back(in_pObject);
}

void VUpdateManager::Unregister(IVUpdateable* in_pObject)
{
	my_Subjects.remove(in_pObject);
}

void VUpdateManager::StartNextFrame()
{
	for_each(
		my_Subjects.begin(), 
		my_Subjects.end(), 
		bind2nd(mem_fun(&IVUpdateable::Update), 1.0f)
		);
}

void VUpdateManager::Start()
{
	for_each(
		my_Subjects.begin(), 
		my_Subjects.end(), 
		mem_fun(&IVUpdateable::Activate)
		);
}

void VUpdateManager::Stop()
{
	for_each(
		my_Subjects.begin(), 
		my_Subjects.end(), 
		mem_fun(&IVUpdateable::Deactivate)
		);
}

void VUpdateManager::Mainloop()
{
	Start();

	while(true)
	{
		StartNextFrame();
	}

	Stop();
}

vfloat64 VUpdateManager::GetFrameDuration()
{
	return m_pTimer->GetFrameDuration();
}

//-----------------------------------------------------------------------------
} // namespace updater
} // namespace v3d
//-----------------------------------------------------------------------------

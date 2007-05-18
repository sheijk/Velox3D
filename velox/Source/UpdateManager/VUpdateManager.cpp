/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VUpdateManager.h"
//-----------------------------------------------------------------------------
#include <V3d/Updater/IVUpdateable.h>
#include <algorithm>
#include <functional>
#include <V3d/Core/MemManager.h>

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

	// instantiate VTimer here
	m_pTimer = new VPerformanceCounter();

	m_nMilliSecondsSinceStart = 0;
}

/**
 * d'tor
 */
VUpdateManager::~VUpdateManager()
{
	//delete m_pTimer;
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

	m_nMilliSecondsSinceStart += vuint32(m_pTimer->GetFrameDuration() * 1000.0);
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

vuint32 VUpdateManager::GetMilliSecondsSinceStart()
{
	return m_nMilliSecondsSinceStart;
}

//-----------------------------------------------------------------------------
} // namespace updater
} // namespace v3d
//-----------------------------------------------------------------------------


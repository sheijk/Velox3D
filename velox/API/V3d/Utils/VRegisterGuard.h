/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VREGISTERGUARD_2005_10_19_H
#define V3D_VREGISTERGUARD_2005_10_19_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/SmartPtr/VServicePtr.h>

#include <set>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Base class for VRegisterGuard<T, Registry> to allow all register guards of
 * arbitrary types to be stored inside a single list
 */
class VRegisterGuardBase
{
public:
	static void RegisterAll();
	static void UnregisterAll();

protected:
	static void Register(VRegisterGuardBase* in_pGuard);
	static void Unregister(VRegisterGuardBase* in_pGuard);

private:
	virtual void Register() = 0;
	virtual void Unregister() = 0;
};

/**
 * Will register the given object to the Registry service. Registering will
 * be done after the module has to be loaded
 * Note: each module has to call VRVRegisterGuardBase::RegisterAll() and
 * UnregisterAll()
 *
 * @author sheijk
 */
template<typename T, typename Registry>
class VRegisterGuard : public VRegisterGuardBase
{
	T* m_pRegisteredObject;

public:
	VRegisterGuard();
	VRegisterGuard(T* in_pToBeRegistered);
	~VRegisterGuard();

	T* operator->() const;
	T& operator*() const;

	virtual void Register();
	virtual void Unregister();
};

//-----------------------------------------------------------------------------

template<typename T, typename Registry>
VRegisterGuard<T, Registry>::VRegisterGuard()
{
	m_pRegisteredObject = new T();
	VRegisterGuardBase::Register(this);
}

template<typename T, typename Registry>
VRegisterGuard<T, Registry>::VRegisterGuard(T* in_pToBeRegistered)
{
	m_pRegisteredObject = in_pToBeRegistered;
    VRegisterGuardBase::Register(this);
}

template<typename T, typename Registry>
VRegisterGuard<T, Registry>::~VRegisterGuard()
{
	VRegisterGuardBase::Unregister(this);
	//delete m_pRegisteredObject;
	m_pRegisteredObject = 0;
}

template<typename T, typename Registry>
T* VRegisterGuard<T, Registry>::operator->() const
{
	return m_pRegisteredObject;
}

template<typename T, typename Registry>
T& VRegisterGuard<T, Registry>::operator*() const
{
	return *m_pRegisteredObject;
}

template<typename T, typename Registry>
void VRegisterGuard<T, Registry>::Register()
{
	VServicePtr<Registry>()->Register(m_pRegisteredObject);
}

template<typename T, typename Registry>
void VRegisterGuard<T, Registry>::Unregister()
{
	VServicePtr<Registry>()->Unregister(m_pRegisteredObject);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VREGISTERGUARD_2005_10_19_H


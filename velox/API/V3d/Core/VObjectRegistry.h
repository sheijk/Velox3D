/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VOBJECTREGISTRY_H
#define V3D_VOBJECTREGISTRY_H
//------------------------------------------------------------------------

#include <V3d/Core/VObjectKey.h>
#include <V3d/Core/VNamedObject.h>
#include <V3d/Core/VObjectRegistryExceptions.h>

#pragma warning(disable:4786) //TODO: restore warning --ins
#include <map>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * Manages a mapping between unique keys and registered objects.

 * Verwaltet eine Zuordnung von eindeutigen Schluesseln zu registrierten Objekten.
 * Die Schluessel/Objektpaare koennen dabei in einem Baum angeordnet sein (d.h.,
 * dass ein Objekt beim Registrieren einen Parent angeben kann). Aufloesungen sind
 * in beiden Richtungen moeglich (Schluessel -> Objekt, Objekt -> Schluessel)
 *
 * Objekte die zerstoert werden muessen sich abmelden. Es koennen Handler
 * registriert werden, welche beim Entfernen/Hinzufuegen von Objekten
 * benachrichtigt werden
 *
 * @author sheijk
 * @created 02-Apr-2003 23:49:31
 */
class VObjectRegistry
{
private:
	// singleton object may not be explicitly created
	VObjectRegistry();
	VObjectRegistry(const VObjectRegistry&);
	virtual ~VObjectRegistry();
	void operator=(const VObjectRegistry&);

	static VObjectRegistry* s_pInstance;

	typedef std::map<VObjectKey, VNamedObject*> ObjectKeyMap;

	ObjectKeyMap m_Objects;
	std::string m_strLastGeneratedName;
	vint64 m_nLastKeyNum;
public:
	//TODO: VStringRetVal
	VStringRetVal GetObjectDump() const;

	/** in case a smart pointer might be used in future */
	typedef VObjectRegistry* Pointer;

	/** set the instance. may only be called once */
	static void SetInstance(Pointer in_pInstance);

	/** creates an instance of the object registry */
	static Pointer CreateInstance();

	/** get the single instance */
	static Pointer GetInstance();

	/** Returns true iff an object of the given name exists */
	virtual vbool ContainsObject(const VObjectKey& in_Key);

	/** get a registered object by name */
	virtual VNamedObject& GetObject(const VObjectKey& Name);

	/** get the name of a registered object */
	virtual VObjectKey GetKey(const VNamedObject& obj);

	/** generate an unused object name */
	virtual VObjectKey GenerateKey();

protected:
	/** register an object to the manager */
	virtual void RegisterObject(const VObjectKey& in_Name, VNamedObject& in_Object);

	/** unregister a registered object */
	virtual void UnregisterObject(VNamedObject& in_Object);

	friend class VNamedObject;
};

/**
 * Retrieves a pointer to a named object and converts it to the right type
 * using RTTI. Returns zero if type does not match and throws the same
 * exception VObjectRegistry.GetObject throws if the object does not exist
 */
template<typename T>
T* QueryObject(const VObjectKey& in_Key)
{
	VNamedObject* pNamedObj = 0;

	pNamedObj = & VObjectRegistry::GetInstance()->GetObject(in_Key);

	return dynamic_cast<T*>(pNamedObj);
}

//-----------------------------------------------------------------------------
} // namespace v3d
//------------------------------------------------------------------------
#endif // V3D_VOBJECTREGISTRY_H



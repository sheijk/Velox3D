#ifndef V3D_VOBJECTREGISTRY_H
#define V3D_VOBJECTREGISTRY_H
//------------------------------------------------------------------------

#include "VObjectKey.h"
#include "VNamedObject.h"
#include "VObjectRegistryExceptions.h"

#pragma warning(disable:4786)
#include <map>

/**
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
 * @version 1.0
 * @generator Enterprise Architect
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

	static VObjectRegistry* m_pInstance;

	typedef std::map<VObjectKey, VNamedObject*> ObjectKeyMap;

	ObjectKeyMap m_Objects;
public:
	/** in case a smart pointer might be used in future */
	typedef VObjectRegistry* Pointer;

	/** get the single instance */
	static Pointer GetInstance();	

	/** register an object to the manager */
	void RegisterObject(const VObjectKey& in_Name, VNamedObject& in_Object);

	/** unregister a registered object */
	void UnregisterObject(VNamedObject& in_Object);

	/** get a registered object by name */
	VNamedObject& GetObject(const VObjectKey& Name);

	/** get the name of a registered object */
	VObjectKey GetKey(const VNamedObject& obj);

	/** generate an unused object name */
	VObjectKey GenerateKey();
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

//------------------------------------------------------------------------
#endif // V3D_VOBJECTREGISTRY_H


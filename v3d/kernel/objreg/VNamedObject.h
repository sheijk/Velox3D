#if !defined(VNamedObject_7B0D1B0E_58C5_4e4d_A230_851331B25E20__INCLUDED_)
#define VNamedObject_7B0D1B0E_58C5_4e4d_A230_851331B25E20__INCLUDED_
//------------------------------------------------------------------------
#include <Core/VCoreLib.h>

#include "VObjectKey.h"

/**
 * Registriert sich automatisch beim Objekt Manager
 * Unterstuetzt Persistenz (speichern/laden in Dateien) sowie Replication
 * (abgleichen von Unterschieden zu einer Instanz auf einem entfernten Rechner)
 *
 * @author sheijk
 * @version 1.0
 * @generator Enterprise Architect
 * @created 02-Apr-2003 23:49:20
 */
class VNamedObject
{
private:
	VNamedObject();

	VObjectKey m_Key;
public:
	/** create object and register it to the object registry */
	VNamedObject(const VNamedObject* in_Parent);
	virtual ~VNamedObject();

public:
	const VObjectKey& GetKey() const;

//	void create(VNamedObject& in_Parent);
//	void createNamed(std::string in_strName, VNamedObject& in_Parent);
};

#endif // !defined(VNamedObject_7B0D1B0E_58C5_4e4d_A230_851331B25E20__INCLUDED_)

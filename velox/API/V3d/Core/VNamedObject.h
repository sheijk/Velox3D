#ifndef V3D_VNAMEDOBJECT_H
#define V3D_VNAMEDOBJECT_H
//------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VObjectKey.h>


//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

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

	/** create object and register it using the given name */
	VNamedObject(VStringParam in_pcName, const VNamedObject* in_Parent);

	/** destructor */
	virtual ~VNamedObject();

	/** get the key of the object */
	const VObjectKey& GetKey() const;
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VNAMEDOBJECT_H

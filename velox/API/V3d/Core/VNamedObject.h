/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VNAMEDOBJECT_H
#define V3D_VNAMEDOBJECT_H
//------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VObjectKey.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * The base class for all objects registered at the object registry.
 * Automatically registers itself at the registry on construction and
 * unregisters itself on deletion.
 *
 * @author sheijk
 */
class VNamedObject
{
private:
	VNamedObject();

	VObjectKey m_Key;
	vbool m_bRegistered;
public:
	/** create object and register it to the object registry */
	VNamedObject(const VNamedObject* in_Parent);

	/** create object and register it using the given name */
	VNamedObject(VStringParam in_pcName, const VNamedObject* in_Parent);

	/** destructor */
	virtual ~VNamedObject();

	/** get the key of the object */
	const VObjectKey& GetKey() const;

protected:
	/**
	 * Unregisters the object from the object registry
	 */
	void UnregisterFromObjectRegistry();
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VNAMEDOBJECT_H


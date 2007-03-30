/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VOBJECTKEY_H
#define V3D_VOBJECTKEY_H
//------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/Wrappers/VString.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * Key to identify registered objects in the object registry
 *
 * @author sheijk
 */
class VObjectKey
{
private:

	// the name of it..
	VString m_strName;
public:
	VObjectKey();

	/** create with name */
	VObjectKey(VStringParam in_pcName);

	/** destructor.. */
	virtual ~VObjectKey();

	/** convert to string */
	VStringRetVal ToString() const;

	bool operator<(const VObjectKey& in_Other) const
	{
		return m_strName < in_Other.m_strName;
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d
//------------------------------------------------------------------------
#endif // V3D_VOBJECTKEY_H


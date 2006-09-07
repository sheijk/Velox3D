/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//TODO: correct file guard
#ifndef V3D_IVFileSystemObject_H
#define V3D_IVFileSystemObject_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------
class IVAccessRights;

/**
 * Basic infos for files and directories
 */
class IVFileSystemObject
{
public:
	virtual ~IVFileSystemObject() {}

	typedef const IVAccessRights* AccessRightsPtr;

	virtual VStringRetVal GetName() const = 0;
	virtual VStringRetVal GetSource() const = 0;
	virtual AccessRightsPtr GetAccessRights() const = 0;
};

inline bool operator==(const IVFileSystemObject& pA, const IVFileSystemObject& pB)
{
	return pA.GetName() == pB.GetName() && pA.GetSource() == pB.GetSource();
}
//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVFileSystemObject_H


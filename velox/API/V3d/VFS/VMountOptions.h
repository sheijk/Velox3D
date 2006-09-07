/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMountOptions_H
#define V3D_VMountOptions_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/Wrappers/VString.h>
#include <v3d/VFS/IVAccessRights.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
 * Information for mounting something (i.e. a directory) to the virtual
 * file system.
 */
struct VMountOptions
{
	typedef VPointer<IVAccessRights>::SharedPtr AccessRightsPtr;

	VString m_strName;
	VString m_strSource;
	VString m_strOptions;
	VString m_strType;
	AccessRightsPtr m_pAccessRights;

public:
	VMountOptions() {};

	VMountOptions(
		VStringParam name, VStringParam source, 
		VStringParam options, VStringParam type,
		AccessRightsPtr accRights)
		: m_strName(name), m_strSource(source), m_strOptions(options),
		m_strType(type), m_pAccessRights(accRights)
	{}

	virtual ~VMountOptions() {}

	const VString& GetName() const;
	const VString& GetType() const;
	const VString& GetOptions() const;
	const VString& GetSource() const;
	const AccessRightsPtr GetAccessRights() const;

	void SetName(VStringParam name) { m_strName = name; }
	void SetSource(VStringParam source) { m_strSource = source; }
	void SetOptions(VStringParam opt) { m_strOptions = opt; }
	void SetType(VStringParam type) { m_strType = type; }
	void SetAccessRights(AccessRightsPtr pAR) { m_pAccessRights = pAR; }
};

//-----------------------------------------------------------------------------
#include "VMountOptions.inl"
//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMountOptions_H


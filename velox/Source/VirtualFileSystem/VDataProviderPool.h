/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//TODO: correct file guard
#ifndef V3D_VDataProviderPool_H
#define V3D_VDataProviderPool_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/VFS/IVDataProviderPool.h>

#include <map>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
//TODO: insert documentation here
*/
class VDataProviderPool : public IVDataProviderPool
{
	typedef std::map<std::string, IVDataProvider*> DataProviderMap;

	DataProviderMap m_DataProviders;

public:
	VDataProviderPool(VStringParam in_strName);
	virtual ~VDataProviderPool();

	virtual vbool RegisterDataProvider(IVDataProvider* in_pDP);
	virtual void UnregisterDataProvider(IVDataProvider* in_pDP);
	virtual IVDataProvider& GetDataProvider(VStringParam in_strType) const;
};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDataProviderPool_H


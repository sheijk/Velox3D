/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VDataProviderPool.h"
//-----------------------------------------------------------------------------
#include <V3d/vfs/VIOException.h>

#include <algorithm>
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

/**
* standard c'tor
*/
VDataProviderPool::VDataProviderPool(VStringParam in_strName)
	: IVDataProviderPool(in_strName)
{
}

/**
* d'tor
*/
VDataProviderPool::~VDataProviderPool()
{
}

vbool VDataProviderPool::RegisterDataProvider(IVDataProvider* in_pDP)
{
	if( 0 != in_pDP )
	{
		std::string strId = in_pDP->GetId();

		if( m_DataProviders.find(strId) == m_DataProviders.end() )
		{
            m_DataProviders[strId] = in_pDP;
			return true;
		}
	}

	return false;
}

void VDataProviderPool::UnregisterDataProvider(IVDataProvider* in_pDP)
{
	if( in_pDP )
	{
		std::string strId = in_pDP->GetId();

		m_DataProviders.erase(strId);
	}
}

IVDataProvider& VDataProviderPool::GetDataProvider(VStringParam in_strType) const
{
	std::string strId = in_strType;

	DataProviderMap::const_iterator dpIter = m_DataProviders.find(strId);

	if( m_DataProviders.end() != dpIter )
	{
		return *(*dpIter).second;
	}
	else
	{
		V3D_THROW(VIOException, 
			VString("Data Provider for type <") + in_strType + "> not found");
	}
}

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------


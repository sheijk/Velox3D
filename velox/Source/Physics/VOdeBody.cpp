/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Physics/VOdeBody.h>
#include <V3d/Physics/VWorld.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace  physics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VOdeBody::VOdeBody()
{
	m_Body = 0;
}

VOdeBody::~VOdeBody()
{
	Destroy();	
}

void VOdeBody::Create(VWorld* in_pWorld)
{
	V3D_ASSERT(in_pWorld != 0);

  	m_Body = dBodyCreate(*in_pWorld->GetWorld());
}

void VOdeBody::Destroy()
{
	if( m_Body )
	{
//		dBodyDestroy(m_Body); //TODO #148
		m_Body = 0;
	}
}

dBodyID VOdeBody::GetBodyID()
{
	return m_Body;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::
//-----------------------------------------------------------------------------


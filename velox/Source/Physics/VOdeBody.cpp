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
	m_bIsAlive = false;
}

VOdeBody::~VOdeBody()
{
	Destroy();	
}

void VOdeBody::Create(VWorld* in_pWorld)
{
	V3D_ASSERT(in_pWorld != 0);

	if(!m_bIsAlive)
	{
		m_Body = dBodyCreate(*in_pWorld->GetWorld());
		m_bIsAlive = true;
	}
}

void VOdeBody::Destroy()
{
	if(m_Body != 0 && m_bIsAlive)
	{
		dBodyDestroy(m_Body);
		m_bIsAlive = false;
	}
}

vbool VOdeBody::IsAlive()
{
	return m_bIsAlive;
}

dBodyID* VOdeBody::GetBodyID()
{
	return &m_Body;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::
//-----------------------------------------------------------------------------

#include <Core/VObserver.h>

VSubject::VSubject(void)
{
}

VSubject::~VSubject(void)
{
}

void VSubject::Attach(VObserver* in_pObserver)
{
	m_Observers.push_back(in_pObserver);
}

void VSubject::Detach(VObserver* in_pObserver)
{
	m_Observers.remove(in_pObserver);
}

void VSubject::Notify(void)
{
	std::list<VObserver*>::iterator it = m_Observers.begin();
	for (; it != m_Observers.end(); it++)
	{
		(*it)->UpdateFromSubject(this);
	}
}

VObserver::VObserver(void)
{
}

VObserver::~VObserver(void)
{
}
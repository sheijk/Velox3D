#include "VRenderContextFactory.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

template <class T>
VRenderContextFactory<T>::VRenderContextFactory(T* in_pinstance) : m_pinstance(in_pinstance)
{
}

template <class T>
VRenderContextFactory<T>::~VRenderContextFactory()
{
	DeleteInstance();
}

template <class T>
VSharedPtr<IVRenderContext> VRenderContextFactory<T>::GetInstance()
{
	return m_pinstance;
}

template <class T>
void VRenderContextFactory<T>::DeleteInstance()
{
	if(m_pinstance)
	{
		delete m_pinstance;
		m_pinstance = 0;
	}
}
//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
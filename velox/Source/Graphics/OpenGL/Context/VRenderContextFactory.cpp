/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VRenderContextFactory.h"

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace graphics; // anti auto indent

//TODO: templates in einer cpp datei zu definieren bringt nix (bei den meisten
// compilern). sowas sollte lieber in eine .inl datei die am ende des headers
// includet wird, beispiele dafuer findets du im API/.. dir

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

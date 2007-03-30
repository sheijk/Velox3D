/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVWXCONNECTOR_H
#define V3D_IVWXCONNECTOR_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d {
namespace window {
//-----------------------------------------------------------------------------
class IVWindowFrame;


/**
 *	Manages all IVConnectable classes <- ?!?
 */
class IVWxConnector
{
public:
	virtual void Register(IVWindowFrame* in_pFrame) = 0;
	virtual void Unregister(IVWindowFrame* in_pFrame) = 0;

	//Test
	virtual IVWindowFrame* GetCurrentFrame() = 0;
	virtual vuint GetNumElements() = 0;

	virtual ~IVWxConnector(){};

	//TODO: koennte problematisch sein, wenn stl klassen im interface sind (sheijk)
	typedef std::vector<IVWindowFrame*> VFrameList;
};

//-----------------------------------------------------------------------------
} // namespace window
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVWXCONNECTOR_H


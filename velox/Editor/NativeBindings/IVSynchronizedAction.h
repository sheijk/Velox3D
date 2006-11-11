/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_IVSYNCHRONIZEDACTION_2006_11_11_H
#define V3D_IVSYNCHRONIZEDACTION_2006_11_11_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace editor {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A synchronzid action will be run once in the in the C++ render thread
 * by VView
 *
 * @see v3d::editor::VView
 * @author sheijk
 */
class IVSynchronizedAction
{
public:
	virtual ~IVSynchronizedAction() {}

	virtual void Run() = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::editor
//-----------------------------------------------------------------------------
#endif // V3D_IVSYNCHRONIZEDACTION_2006_11_11_H


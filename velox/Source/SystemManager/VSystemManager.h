/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VSYSTEMMANAGER_H
#define V3D_VSYSTEMMANAGER_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/System/IVSystemManager.h>
#include <V3d/Core/VNamedObject.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace system {
//-----------------------------------------------------------------------------

/**
 * Provides a system to close velox	
 */

class VSystemManager : public IVSystemManager, public VNamedObject
{
public:
	VSystemManager(VStringParam in_Name);
	virtual ~VSystemManager();

	/*
	 * true for running false for quit
	 */
	virtual void SetStatus(vbool in_Param);
	/*
	 * returns true for running false for quit 
	 */
	virtual vbool GetStatus(); 
	
	//virtual void GetCPU(); // vout's cpu info

private:

	vbool m_bIsRunning;
};

//-----------------------------------------------------------------------------
} // namespace system
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSYSTEMMANAGER_H


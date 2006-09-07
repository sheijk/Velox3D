/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VMODULEBASE_H
#define V3D_VMODULEBASE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

V3D_DECLARE_EXCEPTION(VModuleLoadFailure, VException);

/**
 * Abstract base class for modules. Derive a class from VModuleBase implement
 * Initialize and Shutdown and create a global instance of it inside each 
 * module (dll). 
 * 
 * Also create a function const char* v3d::GetModuleName() which returns a 
 * short unique identifier for the module
 *
 * @author sheijk
 */
class VModuleBase
{
	static VModuleBase* s_pModule;
	static const vchar* s_pcModuleName;

	VModuleBase(const VModuleBase&);
	void operator=(const VModuleBase&);
protected:
	VModuleBase(/*VStringParam in_pcModuleName*/);
	virtual ~VModuleBase();

public:
	static VModuleBase* GetInstance();
	static const vchar* GetModuleName();

	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
};

/** implement this function inside each module */
const char* GetModuleName();

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMODULEBASE_H


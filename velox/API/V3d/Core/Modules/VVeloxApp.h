/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VVELOXAPP_2004_10_09_H
#define V3D_VVELOXAPP_2004_10_09_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/Modules/VModuleBase.h>
#include <V3d/Core/IVApplication.h>
#include <V3d/Core/VNamedObject.h>

#include <vector>
#include <string>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
 * Base class for a velox application. Derive a new application class from
 * this class. Override the main method. Create a global instance of your
 * class
 *
 * @author sheijk
 */
class VVeloxApp : public VModuleBase
{
	class VVeloxMainProxy : public IVApplication, public VNamedObject
	{
		VVeloxApp* m_pApp;
	public:
		VVeloxMainProxy(VVeloxApp* pApp);
		virtual vint Main(const std::vector<std::string>& args);
	};

	std::auto_ptr<VVeloxMainProxy> m_pMainService;

protected:
	VVeloxApp();
	virtual ~VVeloxApp();

	/** Override this method in your application class */
	virtual vint Main(std::vector<std::string>) = 0;

	/** 
	 * Will be called when the kernel loaded all sevices.
	 *
	 * If you need to override this, be sure to call VVeloxApp::Initialize
	 */
	void Initialize();

	/** 
	 * Will be called when the system is going to shutdown.
	 *
	 * If you need to override this, be sure to call VVeloxApp::Shutdown
	 */
	void Shutdown();
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VVELOXAPP_2004_10_09_H


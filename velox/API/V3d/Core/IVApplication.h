/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_APPLICATION_H
#define V3D_APPLICATION_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VTypes.h>

#include <vector>
#include <string>

namespace v3d {
//-----------------------------------------------------------------------------

/**
 * Interface for a velox service that is an application. Write a class
 * inheriting from it and register it as main service in the init.xml
 * Main will be called after initialisation is done
 *
 * @author sheijk
 * @created 26-Apr-2003 19:30:59
 */
class IVApplication
{
public:
	/**
	 * The main function. Will be called by the kernel after initialisation
	 */
	virtual int Main(const std::vector<std::string>& args) = 0;

	virtual ~IVApplication() {}
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_APPLICATION_H


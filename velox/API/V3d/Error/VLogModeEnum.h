/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VLOGMODEENUM_H
#define V3D_VLOGMODEENUM_H

namespace v3d {
namespace error {

	/**
	 * Different types of message logging.
	 */
	//TODO: muesste VLogMode heissen, weil nicht in einer Klasse
	enum LogMode {

		Ok,
		Warning,
		Error
	};

} //error
} //v3d

#endif

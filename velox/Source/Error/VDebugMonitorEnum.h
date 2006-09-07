/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDEBUGMONITORENUM_H
#define V3D_VDEBUGMONITORENUM_H

enum DMSendOptions
{
	MessageOk,
	MessageWarning,
	MessageError,
	DebugLevel,
	StateCreate,
	StateUpdate,
	StateDelete,
	StateData,
	ProgressbarBegin,
	ProgressbarUpdate,
	ProgressbarEnd
};

#endif

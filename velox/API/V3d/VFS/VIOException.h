/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VIOException_H
#define V3D_VIOException_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VException.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace vfs {
//-----------------------------------------------------------------------------

	V3D_DECLARE_EXCEPTION(VIOException, VException);

	V3D_DECLARE_EXCEPTION(VIllegalOperationException, VIOException);

	V3D_DECLARE_EXCEPTION(VElementNotFoundException, VIOException);

/**
 * Base exception class for all virtual file system exceptions
 */
//class VIOException : public VException
//{
//public:
//	VIOException(
//		VStringParam errorMsg, 
//		VStringParam fileName, 
//		vuint lineNumber)
//		: VException(errorMsg, fileName, lineNumber) {};
//
//	virtual ~VIOException() {};
//};
//
//class VIllegalOperationException : public VIOException
//{
//public:
//	VIllegalOperationException(
//		VStringParam errorMsg, 
//		VStringParam fileName, 
//		vuint lineNumber)
//		: VIOException(errorMsg, fileName, lineNumber) {};
//};
//
//class VElementNotFoundException : public VIOException
//{
//public:
//	VElementNotFoundException(
//		VStringParam errorMsg,
//		VStringParam fileName,
//		vuint lineNumber)
//		: VIOException(errorMsg, fileName, lineNumber) {};
//};

//-----------------------------------------------------------------------------
} // namespace vfs
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VIOException_H


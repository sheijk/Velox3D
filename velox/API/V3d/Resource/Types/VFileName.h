/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//TODO: add file creation date to file guard
#ifndef V3D_VFILENAME_H
#define V3D_VFILENAME_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 */
class VFileName
{
public:
	VFileName(VStringParam in_strName);
	VFileName(const std::string& in_strName);
	virtual ~VFileName();

	const std::string& AsString() const;

	/** Returning a file name describing a subdir or file */
	VFileName Append(const std::string& in_strName) const;
private:
	std::string m_strName;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::resource

V3D_TYPEINFO(v3d::resource::VFileName);

//-----------------------------------------------------------------------------
#endif // V3D_VFILENAME_H


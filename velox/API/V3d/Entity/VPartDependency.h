/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VPARTDEPENDENCY_2005_10_23_H
#define V3D_VPARTDEPENDENCY_2005_10_23_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/VTypeInfo.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/** 
* Dependency to another part placed in the same entity or an (in)direct 
* parent
*/
struct VPartDependency
{
	VPartDependency() { typeInfo = 0; }

	/** The location of a dependency: where the required part is located */
	enum Location { Neighbour, Ancestor };

	enum Condition { Optional, Mandatory };

#ifndef SWIG
	Location location;
	std::string id;
	Condition condition;
	const VTypeInfo* typeInfo;
#endif

	Location GetLocation() const { return location; }
	void SetLocation(Location loc) { location = loc; }

	std::string GetId() const { return id; }
	void SetId(const std::string& in_Id) { id = in_Id; }

	Condition GetCondition() const { return condition; }
	void SetCondition(Condition cond) { condition = cond; }

	const VTypeInfo& GetTypeInfo() const { return *typeInfo; }
	void SetTypeInfo(const VTypeInfo& in_Value) { typeInfo = &in_Value; }
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VPARTDEPENDENCY_2005_10_23_H


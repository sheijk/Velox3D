/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VTAGREGISTRY_2006_05_31_H
#define V3D_VTAGREGISTRY_2006_05_31_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Tags/VTag.h>
#include <V3d/Core/VNamedObject.h>
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d { namespace tags {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Manages tags. Every tag has a name and a unique id. Thus tags can 
 * efficiently be compared by comparing their ids and human readable names
 * can be provided
 *
 * tag1.name == tag2.name <=> tag1.id == tag2.id
 * tag1.name != tag2.name <=> tag1.id != tag2.id
 *
 * @author sheijk
 */
class VTagRegistry : public VNamedObject
{
public:
	VTagRegistry();
	virtual ~VTagRegistry();

	virtual VTag& GetTagWithName(const std::string& name);
	virtual vbool ExistsTagWithName(const std::string& name);

private:
	typedef std::vector<VSharedPtr<VTag> > TagSet;
	TagSet m_Tags;
	vuint m_nLastId;
};

typedef VServicePtr<VTagRegistry> VTagRegistryPtr;
//-----------------------------------------------------------------------------
}
template<>
inline v3d::tags::VTagRegistry* QueryService<v3d::tags::VTagRegistry>()
{
	return QueryObject<v3d::tags::VTagRegistry>("tag.registry");
}
} // namespace v3d::tags

//-----------------------------------------------------------------------------
#endif // V3D_VTAGREGISTRY_2006_05_31_H


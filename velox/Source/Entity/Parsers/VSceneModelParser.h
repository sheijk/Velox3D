/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//TODO: add file creation date to file guard
#ifndef V3D_VSCENEMODELPARSER_2005_07_18_H
#define V3D_VSCENEMODELPARSER_2005_07_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVPartParser.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VSceneModelParser : public IVPartParser
{
public:
	VSceneModelParser();
	virtual ~VSceneModelParser();

	virtual std::string GetType() const;
	virtual VSharedPtr<IVPart> Create();
	//virtual VSharedPtr<IVPart> Parse(xml::IVXMLElement& in_Node);
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VSCENEMODELPARSER_2005_07_18_H


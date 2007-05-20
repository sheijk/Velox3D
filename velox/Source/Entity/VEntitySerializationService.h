/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VENTITYSERIALIZATIONSERVICE_2005_07_18_H
#define V3D_VENTITYSERIALIZATIONSERVICE_2005_07_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Entity/IVEntitySerializationService.h>

#include <map>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * @author sheijk
 */
class VEntitySerializationService : public IVEntitySerializationService
{
public:
	VEntitySerializationService();
	virtual ~VEntitySerializationService();

	virtual void Register(IVPartParser* in_pPartParser);
	virtual void Unregister(IVPartParser* in_pPartParser);

	virtual VSharedPtr<VNode> ParsePart(xml::IVXMLElement& in_Node);
	virtual VSharedPtr<VEntity> ParseScene(xml::IVXMLElement& in_Node);

	virtual VRangeIterator<IVPartParser> PartParsers();
	virtual void DumpInfo();

	virtual VSharedPtr<VNode> CreateNode(const std::string& name);
private:
	typedef std::map<std::string, IVPartParser*> ParserMap;

	VSharedPtr<VEntity> Parse(xml::IVXMLElement& in_Node);

	ParserMap m_Parsers;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
#endif // V3D_VENTITYSERIALIZATIONSERVICE_2005_07_18_H


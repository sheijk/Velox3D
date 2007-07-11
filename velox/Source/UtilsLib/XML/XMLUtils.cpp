/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/XML/XMLUtils.h>
//-----------------------------------------------------------------------------

#include <V3d/Vfs.h>
#include <V3d/Xml/IVXMLComment.h>
#include <V3d/Xml/IVXMLText.h>

#include <sstream>
#include <fstream>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace xml {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using std::string;
using namespace v3d::vfs;


IVXMLElement* ToElement(IVXMLNode* in_pNode)
{
	if( in_pNode != 0 && in_pNode->GetType() == IVXMLNode::Element )
		return reinterpret_cast<IVXMLElement*>(in_pNode);
	else
		return 0;
}

vfs::IVStream& operator<<(vfs::IVStream& stream, const std::string str)
{
	stream.Write(str.c_str(), static_cast<IVStream::ByteCount>(str.length()));
	return stream;
}

void Save(std::ostream& stream, IVXMLNode& node, const string& indent);

void Save(std::ostream& stream, IVXMLElement& element, const string& indent)
{
	using namespace std;
	
	string name = element.GetName().AsCString();

	stream << indent << "<" << element.GetName();

	// save all attributes
	VRangeIterator<IVXMLAttribute> attrib = element.AttributeBegin();
	while( attrib.HasNext() )
	{
		string attribName = attrib->GetName().AsCString();
		string attribValue = attrib->GetValue().Get<string>();

		stream << " " << attribName << "=\"" << attribValue << "\"";
			
		++attrib;
	}

	vbool hasChilds = false;

	// save all child nodes
	VRangeIterator<IVXMLNode> child = element.ChildBegin();

	// if the element has childs
	if( child.HasNext() )
	{
		stream << ">\n";

		while( child.HasNext() )
		{
			hasChilds = true;
			Save(stream, *child, indent + "\t");
			
			++child;
		}

		stream << indent << "</" << element.GetName() << ">\n";
	}
	// if the element has no childs
	else
	{
		stream << "/>\n";
	}
}

void Save(std::ostream& stream, IVXMLComment& comment, const string& indent)
{
	stream << indent << "<!== " << comment.GetComment() << " -->\n";
}

void Save(std::ostream& stream, IVXMLText& text, const string& indent)
{
	stream << indent << text.GetText() << "\n";
}

void Save(std::ostream& stream, IVXMLNode& node, const string& indent)
{
	if( node.ToElement() != 0 )
		Save(stream, *node.ToElement(), indent);
	else if( node.ToComment() != 0 )
		Save(stream, *node.ToComment(), indent);
	else if( node.ToText() != 0 )
		Save(stream, *node.ToText(), indent);
}

void SaveXMLElementToFile(IVXMLElement* in_pELement, VStringParam in_strFileName)
{
	VSharedPtr<IVStream> pFileStream = vfs::VFileSystemPtr()->OpenFile(
		in_strFileName, vfs::VWriteAccess);

	*pFileStream << "<?" << "xml version=\"1.0\"?>" <<"\n";

	std::stringstream stream;
	Save(stream, *in_pELement, "");

	*pFileStream << stream.str();
}

void SaveXMLElementToFileNoVFS(IVXMLElement* in_pElement, VStringParam in_strFileName)
{
	std::ofstream file(in_strFileName);

	file << "<?" << "xml version=\"1.0\"?>" <<"\n";
    Save(file, *in_pElement, "");
}

std::string XMLElementToString(IVXMLElement* in_pElement)
{
	if( in_pElement != NULL )
	{
		std::stringstream stream;
		Save(stream, *in_pElement, "");
		return stream.str();
	}
	else
	{
		return "";
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::xml
//-----------------------------------------------------------------------------


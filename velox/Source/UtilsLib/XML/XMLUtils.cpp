#include <V3d/XML/XMLUtils.h>
//-----------------------------------------------------------------------------

#include <V3d/Vfs.h>
#include <V3d/Xml/IVXMLComment.h>
#include <V3d/Xml/IVXMLText.h>

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
	stream.Write(str.c_str(), str.length());
	return stream;
}

void Save(vfs::IVStream& stream, IVXMLNode& node, const string& indent);

void Save(vfs::IVStream& stream, IVXMLElement& element, const string& indent)
{
	stream << indent << "<" << element.GetName();

	// save all attributes
	VRangeIterator<IVXMLAttribute> attrib = element.AttributeBegin();
	vbool first = true;
	while( attrib.HasNext() )
	{
		stream << (first ? "" : " ")
			<< attrib->GetName() << "=" << attrib->GetValue().Get<string>();
	}

	vbool hasChilds = false;

	// save all child nodes
	VRangeIterator<IVXMLNode> child = element.ChildBegin();
	while( child.HasNext() )
	{
		hasChilds = true;
		Save(stream, *child, indent + "\t");
	}

	if( hasChilds )
		stream << indent << "</" << element.GetName() << ">\n";
	else
		stream << indent << ">\n";
}

void Save(vfs::IVStream& stream, IVXMLComment& comment, const string& indent)
{
	stream << indent << "<!== " << comment.GetComment() << " -->\n";
}

void Save(vfs::IVStream& stream, IVXMLText& text, const string& indent)
{
	stream << indent << text.GetText() << "\n";
}

void Save(vfs::IVStream& stream, IVXMLNode& node, const string& indent)
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

	Save(*pFileStream, *in_pELement, "");
}

//-----------------------------------------------------------------------------
}} // namespace v3d::xml
//-----------------------------------------------------------------------------

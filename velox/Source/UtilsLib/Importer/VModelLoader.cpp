#include <V3dLib/Graphics/Importer/VModelLoader.h>
//-----------------------------------------------------------------------------
#include <V3d/XML.h>
#include <V3d/Vfs.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::xml;
using namespace v3d::resource;

/**
 * standard c'tor
 */
VModelLoader::VModelLoader()
{
	m_PrimitiveNames["triangles"] = VMeshDescription::Triangles;
	m_PrimitiveNames["triangleStrip"] = VMeshDescription::TriangleStrip;
	m_PrimitiveNames["triangleFan"] = VMeshDescription::TriangleFan;
}

/**
 * d'tor
 */
VModelLoader::~VModelLoader()
{
}

IVXMLElement* ToElement(IVXMLNode* in_pNode)
{
	if( in_pNode != 0 && in_pNode->GetType() == IVXMLNode::Element )
		return reinterpret_cast<IVXMLElement*>(in_pNode);
	else
		return 0;
}

template<typename T>
vbool HasAttributeWithValue(
	IVXMLElement* in_pElement, 
	VStringParam in_strAttribName,
	const T& in_ExpectedValue)
{
	vbool result = false;

	try
	{
		IVXMLAttribute* pAttrib = in_pElement->GetAttribute(in_strAttribName);

		if( pAttrib != 0 )
		{
			result = pAttrib->GetValue().Get<T>() == in_ExpectedValue;
		}
	}
	catch(VException&)
	{}

	return result;
}

template<typename Iterator>
vuint Count(const Iterator& in_Begin, const Iterator& in_End)
{
	vuint count = 0;

	for(Iterator it = in_Begin; it != in_End; ++it)
	{
		++count;
	}

	return count;
}

vuint CalculateOffsetInBytes(vuint in_nIndex, const VDataFormat& in_Format)
{
	return in_Format.GetFirstIndex() * sizeof(vfloat32) + 
		(in_Format.GetStride() * in_nIndex * sizeof(vfloat32));
}

void SetCoordinate(
   VByteBuffer& io_Buffer,
   vuint in_nIndex,
   const VVertexFormat& in_Format,
   const VVertex3f& in_Coordinate)
{
    // calc offset
	const vuint offset = CalculateOffsetInBytes(
		in_nIndex, in_Format.GetCoordinateFormat());

	// copy data
	V3D_ASSERT( offset >= 0 );
	V3D_ASSERT( (offset+sizeof(VVertex3f)) <= io_Buffer.GetSize() );

	memcpy(io_Buffer.GetDataAddress()+offset, &in_Coordinate, sizeof(in_Coordinate));
}

void SetColor(
	VByteBuffer& io_Buffer,
	vuint in_nIndex,
	const VVertexFormat& in_Format,
	const VColor4f& in_Color)
{
	const vuint offset = CalculateOffsetInBytes(
		in_nIndex, in_Format.GetColorFormat());

	V3D_ASSERT( offset >= 0 );
	V3D_ASSERT( (offset+sizeof(VVertex3f)) <= io_Buffer.GetSize() );

	memcpy(io_Buffer.GetDataAddress()+offset, &in_Color, sizeof(in_Color));
}

VVertex3f ReadCoordinate(IVXMLElement* in_pElement)
{
	return VVertex3f(
		in_pElement->GetAttributeValue<vfloat32>("x"),
		in_pElement->GetAttributeValue<vfloat32>("y"),
		in_pElement->GetAttributeValue<vfloat32>("z")
		);
}

VColor4f ReadColor(IVXMLElement* in_pElement)
{
	return VColor4f(
		in_pElement->GetAttributeValue<vfloat32>("r"),
		in_pElement->GetAttributeValue<vfloat32>("g"),
		in_pElement->GetAttributeValue<vfloat32>("b"),
		in_pElement->GetAttributeValue<vfloat32>("a")
		);
}

void VModelLoader::CheckRootNode(IVXMLElement* in_pRootNode)
{
	if( in_pRootNode->GetName() != VString("model") )
	{
		std::stringstream msg;
		msg << "Failed to load model from xml file '"
			<< m_strCurrentFile << "'. Root element named '"
			<< in_pRootNode->GetName() << "' instead of 'model'";

		std::string smsg = msg.str();
		const char* pmsg = smsg.c_str();

		V3D_THROW(VModelLoadingException, pmsg);
	}
}

void VModelLoader::LoadMesh(
	VStringParam in_strFileName, 
	VResourceId in_pResource)
{
	m_strCurrentFile = in_strFileName;

	// open xml file for reading
	vfs::IVFileSystem::FileStreamPtr pFile =
		vfs::VFileSystemPtr()->OpenFile(in_strFileName, vfs::VReadAccess);
	IVXMLService::IVXMLElementPtr pRootNode =
		VXMLServicePtr()->GetRootElement(&*pFile);

	// main node should be model with version 1.0
	CheckRootNode(&*pRootNode);
	
	//TODO: check version

	// for each mesh node
	for(IVXMLElement::NodeIter node = pRootNode->ChildBegin();
		node != pRootNode->ChildEnd();
		++node)
	{
		IVXMLElement* pMeshNode = ToElement(&*node);

		if( pMeshNode != 0 && pMeshNode->GetName() == VString("mesh") )
		{
			// create mesh for the node
			CreateMeshNode(pMeshNode, in_pResource);
		}
	}
}

void VModelLoader::CreateMeshNode(
	xml::IVXMLElement* in_pMeshNode, 
	resource::VResourceId in_pResource)
{
	// get format and size
	// get vertex count
	const vertexCount = 
		Count(in_pMeshNode->ChildBegin(), in_pMeshNode->ChildEnd());

	// get contained vertex elements
	const vbool bCoordinates = HasAttributeWithValue<std::string>(
		in_pMeshNode, "coords", "yes");
	const vbool bColors = HasAttributeWithValue<std::string>(
		in_pMeshNode, "colors", "yes");

	// calculate size per vertex
	vuint vertexSize = 0;

	const vuint coordSize = sizeof(VVertex3f) / sizeof(vfloat32);
	const vuint colorSize = sizeof(VColor4f) / sizeof(vfloat32);

	if( bCoordinates )
		vertexSize += coordSize;

	if( bColors )
		vertexSize += colorSize;

	// set data format
	VVertexFormat format;
	vuint dataEnd = 0;

	if( bCoordinates )
	{
		format.SetCoordinateFormat(
			VDataFormat(dataEnd, vertexCount, coordSize));
        dataEnd += coordSize * vertexCount;
	}

	if( bColors )
	{
		format.SetColorFormat(
			VDataFormat(dataEnd, vertexCount, colorSize));
		dataEnd += colorSize * vertexCount;
	}

	V3D_ASSERT(dataEnd == vertexSize * vertexCount);

	// create buffer
	const bufferSize = vertexSize * vertexCount * sizeof(vfloat32);
	VByteBuffer vertices(new vbyte[bufferSize], bufferSize);

	// read all vertices
	vuint nVertexId = 0;
	for(IVXMLElement::NodeIter vertexNode = in_pMeshNode->ChildBegin();
		vertexNode != in_pMeshNode->ChildEnd();
		++vertexNode)
	{
		IVXMLElement* pVertexNode = ToElement(&*vertexNode);

		if( pVertexNode != 0 )
		{
			// get vertex data and write it to the buffer
			if( bCoordinates )
			{
				VVertex3f v = ReadCoordinate(pVertexNode);
				SetCoordinate(vertices, nVertexId, format, v);
			}
			if( bColors )
			{
				VColor4f color = ReadColor(pVertexNode);
				//VColor4f color(1, 0, 0, 1);
				SetColor(vertices, nVertexId, format, color);
			}

			++nVertexId;
		}
		else
		{
			std::stringstream msg;
			msg << "Error while parsing file '" << m_strCurrentFile
				<< "': expected 'vertex' element";

			V3D_THROW(VModelLoadingException, msg.str().c_str());
		}
	}

	// add vertex buffer and mesh description to resource
	in_pResource->AddData(new VVertexBuffer(vertices, format));
	VMeshDescription* pMeshDescription = 
		new VMeshDescription(format);
	
	// get geometry type
	std::string strGeometryType = in_pMeshNode->GetAttribute("type")->GetValue().Get<std::string>();
	pMeshDescription->SetGeometryType(GetGeometryType(strGeometryType));

	// set resource references
	if( bCoordinates )
		pMeshDescription->SetCoordinateResource(in_pResource->GetQualifiedName());
	if( bColors )
		pMeshDescription->SetColorResource(in_pResource->GetQualifiedName());

	in_pResource->AddData(pMeshDescription);

	VFloatBuffer v(vertices);
}

VMeshDescription::GeometryType VModelLoader::GetGeometryType(
	const std::string& in_strName)
{
	std::map<std::string, VMeshDescription::GeometryType>::iterator it
		= m_PrimitiveNames.find(in_strName);

	if( it != m_PrimitiveNames.end() )
	{
		return it->second;
	}
	else
	{
		std::stringstream msg;
		msg << "Failed to parse xml model file '" << m_strCurrentFile;
		msg << "': primitive type '" << in_strName << "' unknown";
		V3D_THROW(VModelLoadingException, msg.str().c_str());
	}
}

void VModelLoader::GetFormat(
	VVertexFormat& out_Format, 
	xml::IVXMLElement* in_pMeshNode)
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

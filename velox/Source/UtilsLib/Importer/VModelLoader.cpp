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
	m_PrimitiveNames["triangles"] =		VMeshDescription::Triangles;
	m_PrimitiveNames["triangleStrip"] =	VMeshDescription::TriangleStrip;
	m_PrimitiveNames["triangleFan"] =	VMeshDescription::TriangleFan;
	m_PrimitiveNames["points"] =		VMeshDescription::Points;
	m_PrimitiveNames["lines"] =			VMeshDescription::Lines;
	m_PrimitiveNames["lineStrip"] =		VMeshDescription::LineStrip;
	m_PrimitiveNames["quads"] =			VMeshDescription::Quads;
	m_PrimitiveNames["quadStrip"] =		VMeshDescription::QuadStrip;
}

/**
 * d'tor
 */
VModelLoader::~VModelLoader()
{
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
	V3D_ASSERT( (offset+sizeof(in_Coordinate)) <= io_Buffer.GetSize() );

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
	V3D_ASSERT( (offset+sizeof(in_Color)) <= io_Buffer.GetSize() );

	memcpy(io_Buffer.GetDataAddress()+offset, &in_Color, sizeof(in_Color));
}

void SetTexCoord(
	vuint in_nTexCoordNum,
	VByteBuffer& io_Buffer,
	vuint in_nIndex,
	const VVertexFormat& in_Format,
	const VTexCoord2f& in_TexCoord)
{
	V3D_ASSERT( in_nTexCoordNum == 0 );

	const vuint offset = CalculateOffsetInBytes(
		in_nIndex, in_Format.GetTexCoordFormat(in_nTexCoordNum));

	V3D_ASSERT( offset >= 0 );
	V3D_ASSERT( (offset+sizeof(in_TexCoord)) <= io_Buffer.GetSize() );

	memcpy(io_Buffer.GetDataAddress()+offset, &in_TexCoord, sizeof(in_TexCoord));
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

VTexCoord2f ReadTexCoord(IVXMLElement* in_pElement, vuint in_nTexCoordNum)
{
	std::stringstream name;
	name << "u" << in_nTexCoordNum;

	vfloat32 u = in_pElement->GetAttributeValue<vfloat32>(name.str().c_str());

	// clear string stream
	name.str("");
	name << "v" << in_nTexCoordNum;

	vfloat32 v = in_pElement->GetAttributeValue<vfloat32>(name.str().c_str());

	return VTexCoord2f(u, v);
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

vuint CountNodesWithName(
	IVXMLElement::NodeIter in_Begin,
	IVXMLElement::NodeIter in_End,
	std::string in_Name
	)
{
	vuint nodeCount = 0;
	const VString countedName(in_Name.c_str());

	for(IVXMLElement::NodeIter node = in_Begin; node != in_End; ++node)
	{
		IVXMLElement* pNode = ToElement(&*node);

		if( pNode != 0 && pNode->GetName() == countedName )
		{
			++nodeCount;
		}
	}

	return nodeCount;
}

void VModelLoader::CreateMeshNode(
	xml::IVXMLElement* in_pMeshNode, 
	resource::VResourceId in_pResource)
{
	// get format and size
	// get vertex count
	const vuint vertexCount = CountNodesWithName(
			in_pMeshNode->ChildBegin(), in_pMeshNode->ChildEnd(),
			"vertex");
//		Count(in_pMeshNode->ChildBegin(), in_pMeshNode->ChildEnd());

	// get contained vertex elements
	const vbool bCoordinates = HasAttributeWithValue<std::string>(
		in_pMeshNode, "coords", "yes");
	const vbool bColors = HasAttributeWithValue<std::string>(
		in_pMeshNode, "colors", "yes");
	const vuint nTexCoordCount = 
		in_pMeshNode->GetAttributeValue<vuint>("texCoords");

	// calculate size per vertex
	vuint vertexSize = 0;

	const vuint coordSize = sizeof(VVertex3f) / sizeof(vfloat32);
	const vuint colorSize = sizeof(VColor4f) / sizeof(vfloat32);
	const vuint texCoordSize = sizeof(VTexCoord2f) / sizeof(vfloat32);

	if( bCoordinates )
		vertexSize += coordSize;

	if( bColors )
		vertexSize += colorSize;

	vertexSize += nTexCoordCount * texCoordSize;

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

	format.SetTexCoordCount(nTexCoordCount);
	for(vuint i = 0; i < nTexCoordCount; ++i)
	{
		format.SetTexCoordFormat(i, VDataFormat(dataEnd, vertexCount, texCoordSize));
		dataEnd += texCoordSize * vertexCount;
	}

	V3D_ASSERT(dataEnd == vertexSize * vertexCount);

	// create buffer
	const bufferSize = vertexSize * vertexCount * sizeof(vfloat32);
	VByteBuffer vertices(new vbyte[bufferSize], bufferSize);

	IVXMLElement::NodeIter meshChildNode = in_pMeshNode->ChildBegin();

	// read all vertices
	vuint nVertexId = 0;
	vbool bReadingVertices = true;
	//for(vbool bReadingVertices = true;
	//	bReadingVertices && meshChildNode != in_pMeshNode->ChildEnd();
	//	++meshChildNode)
	while( bReadingVertices && meshChildNode != in_pMeshNode->ChildEnd() )
	{
		IVXMLElement* pVertexNode = ToElement(&*meshChildNode);

		if( pVertexNode != 0 && pVertexNode->GetName() == VString("vertex") )
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

			for(vuint i = 0; i < nTexCoordCount; ++i)
			{
				VTexCoord2f texCoord = ReadTexCoord(pVertexNode, i);
				SetTexCoord(i, vertices, nVertexId, format, texCoord);
			}

			++nVertexId;
			++meshChildNode;
		}
		else
		{
			bReadingVertices = false;
		}
	}

	// add vertex buffer and mesh description to resource
	in_pResource->AddData(new VVertexBuffer(vertices, format));
	VMeshDescription* pMeshDescription = 
		new VMeshDescription(format);
	
	// get geometry type
	std::string strGeometryType = 
		in_pMeshNode->GetAttribute("type")->GetValue().Get<std::string>();
	pMeshDescription->SetGeometryType(GetGeometryType(strGeometryType));

	// set resource references
	if( bCoordinates )
		pMeshDescription->SetCoordinateResource(in_pResource->GetQualifiedName());
	if( bColors )
		pMeshDescription->SetColorResource(in_pResource->GetQualifiedName());
	for(vuint i = 0; i < nTexCoordCount; ++i)
		pMeshDescription->SetTexCoordResource(i, in_pResource->GetQualifiedName());

	// if indices are present, read them now
	if( HasAttributeWithValue<std::string>(in_pMeshNode, "indices", "yes") )
	{
		const vuint indexCount = CountNodesWithName(
			in_pMeshNode->ChildBegin(), in_pMeshNode->ChildEnd(), "index");

		const vuint indexBufferSize = indexCount * sizeof(vuint);

		VBuffer<vuint> indices(new vuint[indexBufferSize], indexBufferSize);

		vuint indexNum = 0;
		for( ; meshChildNode != in_pMeshNode->ChildEnd(); ++meshChildNode)
		{
			IVXMLElement* pIndexNode = ToElement(&*meshChildNode);

			if( pIndexNode != 0 )
			{
				if( pIndexNode->GetName() == VString("index") )
				{
					vuint nVertex = pIndexNode->GetAttributeValue<vuint>("id");
					V3D_ASSERT(nVertex <= vertexCount);
					indices[indexNum] = nVertex;

					++indexNum;
				}
				else
				{
					std::stringstream msg;
					msg << "Error when parsing xml model file '"
						<< m_strCurrentFile << "': ";
					msg << "found invalid node '" << pIndexNode->GetName() 
						<< "' expected 'index'";

					V3D_THROW(VModelLoadingException, msg.str().c_str());
				}
			}
		}

		// add index buffer
		VResourceId indexRes = in_pResource->AddSubResource("indices");
		VVertexFormat indexFormat;
		indexFormat.SetIndexFormat(VDataFormat(0, indexCount, 0));
		pMeshDescription->SetIndexFormat(indexFormat.GetIndexFormat());
		pMeshDescription->SetIndexResource(indexRes->GetQualifiedName());
        indexRes->AddData(new VVertexBuffer(indices, indexFormat));
	}

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

#include "VImmediateVertexStream.h"
//-----------------------------------------------------------------------------
#include <V3d/OpenGL.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

namespace 
{
	vbool TypeSetIn(
		VVertexFormat::DataTypes type, 
		VVertexFormat::DataTypes flags)
	{
		return (int(type) & int(flags)) != 0;
	}
} // anonymous namespace

VImmediateVertexStream::VImmediateVertexStream(VertexDataPtr in_pVertexData)
{
	m_pVertexData = in_pVertexData;
}

VImmediateVertexStream::~VImmediateVertexStream()
{
}

vbool VImmediateVertexStream::CanProvideStream(VVertexFormat::DataTypes in_DataTypes) const
{
	//TODO: evtl eine passende util funktion in VVertexFormat einbauen --sheijk
	if( TypeSetIn(VVertexFormat::Coordinates, in_DataTypes) &&
		m_pVertexData->GetFormat().GetCoordinateFormat().GetCount() <= 0 )
	{
		return false;
	}

	if( TypeSetIn(VVertexFormat::Colors, in_DataTypes) &&
		m_pVertexData->GetFormat().GetColorFormat().GetCount() <= 0 )
	{
		return false;
	}

	if( TypeSetIn(VVertexFormat::Normals, in_DataTypes) &&
		m_pVertexData->GetFormat().GetNormalFormat().GetCount() <= 0 )
	{
		return false;
	}

	if( TypeSetIn(VVertexFormat::Indices, in_DataTypes) &&
		m_pVertexData->GetFormat().GetIndexFormat().GetCount() <= 0 )
	{
		return false;
	}

	if( TypeSetIn(VVertexFormat::TexCoords, in_DataTypes) )
	if(
		m_pVertexData->GetFormat().GetTexCoordCount() < 1 &&
		m_pVertexData->GetFormat().GetTexCoordFormat(0).GetCount() <= 0
		)
	{
		return false;
	}

	return true;
}

vbool VImmediateVertexStream::Bind(VVertexFormat::DataTypes in_StreamTypes) const
{
	const VVertexFormat& format(m_pVertexData->GetFormat());

	// check whether all requested streams exists and whether they
	// have enough data
	if( !CanProvideStream(in_StreamTypes) )
	{
		return false;
	}

	// bind all streams
	const vfloat32* pBuffer = 
		reinterpret_cast<const vfloat32*>(m_pVertexData->GetBufferAddress());

	if( TypeSetIn(VVertexFormat::Coordinates, in_StreamTypes) && 
		format.GetCoordinateFormat().GetCount() > 0 )
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(
			3,
			GL_FLOAT,
			format.GetCoordinateFormat().GetStride() * sizeof(vfloat32),
			pBuffer + format.GetCoordinateFormat().GetFirstIndex()
			);
	}

	if( TypeSetIn(VVertexFormat::Colors, in_StreamTypes) && 
		format.GetColorFormat().GetCount() > 0 )
	{
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(
			4,
			GL_FLOAT,
			format.GetColorFormat().GetStride() * sizeof(vfloat32),
			pBuffer + format.GetColorFormat().GetFirstIndex()
			);
	}

	if( TypeSetIn(VVertexFormat::Normals, in_StreamTypes) &&
		format.GetNormalFormat().GetCount() > 0 )
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(
			GL_FLOAT,
			format.GetNormalFormat().GetStride() * sizeof(vfloat32),
			pBuffer + format.GetNormalFormat().GetFirstIndex()
			);
	}

	if( 
		TypeSetIn(VVertexFormat::TexCoords, in_StreamTypes) && 
		format.GetTexCoordCount() >= 1 &&
		format.GetTexCoordFormat(0).GetCount() > 0 
		)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(
			2,
			GL_FLOAT,
			format.GetTexCoordFormat(0).GetStride() * sizeof(vfloat32),
			pBuffer + format.GetTexCoordFormat(0).GetFirstIndex()
			);
	}

	return true;
}

void VImmediateVertexStream::UnbindAll() const
{
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

const void* VImmediateVertexStream::GetIndexAddress() const
{
	if( CanProvideStream(VVertexFormat::Indices) )
	{
		return m_pVertexData->GetBufferAddress() + 
//			m_pVertexData->GetFormat().GetIndexFormat().GetFirstIndex();
			(m_pVertexData->GetFormat().GetIndexFormat().GetFirstIndex() * 4);
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

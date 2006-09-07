/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VVERTEXFORMAT_2005_02_02_H
#define V3D_VVERTEXFORMAT_2005_02_02_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3d/Graphics/VDataFormat.h>

#include <vector>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/** 
 * Describes the format of vertices. Describes which information is present
 * and how it is aligned in the buffer
 *
 * @author sheijk
 */
class VVertexFormat
{
public:
	enum DataTypes
	{
		Coordinates	= 1,
		Colors		= 2,
		Normals		= 4,
		Indices		= 8,
		TexCoords	= 16
	};

	VVertexFormat();
	VVertexFormat(
		DataTypes in_DataTypes, 
		vuint in_nVertexCount, 
		vuint in_nIndexCount);

	VDataFormat GetCoordinateFormat() const;
	void SetCoordinateFormat(VDataFormat in_Format);

	VDataFormat GetColorFormat() const;
	void SetColorFormat(VDataFormat in_Format);

	VDataFormat GetNormalFormat() const;
	void SetNormalFormat(VDataFormat in_Format);

	VDataFormat GetIndexFormat() const;
	void SetIndexFormat(VDataFormat in_Format);

	vuint GetTexCoordCount() const;
	virtual void SetTexCoordCount(vuint in_nNewCount);
	VDataFormat GetTexCoordFormat(vuint in_nCoord) const;
	void SetTexCoordFormat(vuint in_nCoord, VDataFormat in_Format);

	vbool Contains(DataTypes in_DataTypes) const;

private:
	VDataFormat m_CoordinateFormat;
	VDataFormat m_ColorFormat;
	VDataFormat m_NormalFormat;
	VDataFormat m_IndexFormat;
	std::vector<VDataFormat> m_TexCoordFormats;
};

/**
 * Provide a 'clean' way to or-combine several data type flags
 */
inline VVertexFormat::DataTypes operator|(
	VVertexFormat::DataTypes l, VVertexFormat::DataTypes r)
{
	return VVertexFormat::DataTypes(int(l) | int(r));
}

/**
 * Provides a 'clean' way to and-combine several data type flags
 */
inline VVertexFormat::DataTypes operator&(
	VVertexFormat::DataTypes l, VVertexFormat::DataTypes r)
{
	return VVertexFormat::DataTypes(int(l) & int(r));
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VVERTEXFORMAT_2005_02_02_H


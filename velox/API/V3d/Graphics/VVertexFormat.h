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
	VDataFormat GetCoordinateFormat() const;
	void SetCoordinateFormat(VDataFormat in_Format);

	VDataFormat GetColorFormat() const;
	void SetColorFormat(VDataFormat in_Format);

	VDataFormat GetIndexFormat() const;
	void SetIndexFormat(VDataFormat in_Format);

	vuint GetTexCoordCount() const;
	VDataFormat GetTexCoordFormat(vuint in_nCoord) const;
	void SetTexCoordFormat(vuint in_nCoord, VDataFormat in_Format);

protected:
	virtual void SetTexCoordCount(vuint in_nNewCount);

private:
	VDataFormat m_CoordinateFormat;
	VDataFormat m_ColorFormat;
	VDataFormat m_IndexFormat;
	std::vector<VDataFormat> m_TexCoordFormats;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VVERTEXFORMAT_2005_02_02_H

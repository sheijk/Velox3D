//TODO: add file creation date to file guard
#ifndef V3D_VDATAFORMAT_2005_02_02_H
#define V3D_VDATAFORMAT_2005_02_02_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Specifies the data format of some data within an interleaved buffer
 * At FirstIndex-th byte come Count element every Stride bytes
 * 
 * @author sheijk
 */
class VDataFormat
{
	vuint m_nFirstIndex;
	vuint m_nCount;
	vuint m_nStride;

public:
	VDataFormat() : m_nStride(0), m_nFirstIndex(0), m_nCount(0) {}

	VDataFormat(vuint first, vuint count, vuint stride) :
		m_nFirstIndex(first), m_nCount(count), m_nStride(stride) {}

	vuint GetFirstIndex() const	{ return m_nFirstIndex; }
	vuint GetCount() const		{ return m_nCount; }
	vuint GetStride() const		{ return m_nStride; }

	void SetFirstIndex(vuint f)	{ m_nFirstIndex = f; }
	void SetCount(vuint c)		{ m_nCount = c; }
	void SetStride(vuint s)		{ m_nStride = s; }

	vuint GetOffset(vuint in_nNum) const
	{
		return m_nFirstIndex + (m_nStride * in_nNum);
	}
};

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_VDATAFORMAT_2005_02_02_H

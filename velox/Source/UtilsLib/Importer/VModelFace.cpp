#include "VModelFace.h"
//-----------------------------------------------------------------------------
namespace v3d{
namespace utils{
namespace importer{
//-----------------------------------------------------------------------------
VModelFace::VModelFace()
{
	m_iVertexIndex[0] = 0;
	m_iVertexIndex[1] = 0;
	m_iVertexIndex[2] = 0;

	m_iTextureUVIndex[0] = 0;
	m_iTextureUVIndex[1] = 0;
	m_iTextureUVIndex[2] = 0;

}
//-----------------------------------------------------------------------------
VModelFace::~VModelFace()
{

}
//-----------------------------------------------------------------------------
} // namespace v3d
} // namespace util
} // namespace v3d
//-----------------------------------------------------------------------------

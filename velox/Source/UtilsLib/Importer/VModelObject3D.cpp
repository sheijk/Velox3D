#include "VModelObject3D.h"
//-----------------------------------------------------------------------------
namespace v3d{
namespace utils{
namespace importer{
//-----------------------------------------------------------------------------
VModelObject3D::VModelObject3D()
{
	m_iNumFaces = 0;
	m_iNumVertices = 0;
	m_iNumTexCoords2f = 0;
	m_ModelFaces = 0;
	m_TextureCoordsList = 0;
	m_VerticesList = 0;
	m_pVertexIndex = 0;

}
//-----------------------------------------------------------------------------

VModelObject3D::~VModelObject3D()
{
	if(m_ModelFaces)
		delete m_ModelFaces;
	if(m_TextureCoordsList)
		delete m_TextureCoordsList;
	if(m_VerticesList)
		delete m_VerticesList;


}
//-----------------------------------------------------------------------------
} // namespace importer
} // namespace util
} // namespace v3d
//-----------------------------------------------------------------------------

template <typename VertexStructure>
vuint VCircleMesh<VertexStructure>::CalculateVertexNumber( vuint in_nDetail )
{
	return 3*in_nDetail;
}


template <typename VertexStructure> 
void VCircleMesh<VertexStructure>::CreateCoordinates()
{
	vfloat32 fTheta = 0.0f;
	vfloat32 fDelta = 6.29f / m_nDetail;

	for ( vuint i=0; i<m_nDetail*3; i+=3 )
	{
		buffer[i].position = VVector3f( 0.0f, 0.0f, 0.0f );
		buffer[i+1].position = VVector3f( m_fRadius*cos(fTheta), 0.0f, m_fRadius*sin(fTheta) );
		fTheta += fDelta;
		buffer[i+2].position = VVector3f( m_fRadius*cos(fTheta), 0.0f, m_fRadius*sin(fTheta) );
	}
}
template <typename VertexStructure>
vuint VCylinder<VertexStructure>::CalculateVertexNumber( vuint in_nDetail )
{
	return 12*in_nDetail;
}


template <typename VertexStructure> 
void VCylinder<VertexStructure>::CreateCoordinates()
{
	vfloat32 fTheta = 0.0f;
	vfloat32 fDelta = 6.29f / m_nDetail;

	// bottom
	for ( vuint i=0; i<m_nDetail*3; i+=3 )
	{
		buffer[i].position = VVector3f( 0.0f, -m_fHeight/2.0f, 0.0f );
		buffer[i+1].position = VVector3f( m_fRadius*cos(fTheta), -m_fHeight/2.0f, m_fRadius*sin(fTheta) );
		fTheta += fDelta;
		buffer[i+2].position = VVector3f( m_fRadius*cos(fTheta), -m_fHeight/2.0f, m_fRadius*sin(fTheta) );
	}

	//top
	fTheta = 0.0f;
	for ( vuint i=m_nDetail*3; i<2*m_nDetail*3; i+=3 )
	{
		buffer[i].position = VVector3f( 0.0f, +m_fHeight/2.0f, 0.0f );
		buffer[i+2].position = VVector3f( m_fRadius*cos(fTheta), +m_fHeight/2.0f, m_fRadius*sin(fTheta) );
		fTheta += fDelta;
		buffer[i+1].position = VVector3f( m_fRadius*cos(fTheta), +m_fHeight/2.0f, m_fRadius*sin(fTheta) );
	}

	fTheta = 0.0f;
	for ( vuint i=m_nDetail*6; i<m_nDetail*12; i+=6 )
	{
		buffer[i  ].position = VVector3f( m_fRadius*cos(fTheta), -m_fHeight/2.0f, m_fRadius*sin(fTheta) );
		buffer[i+1].position = VVector3f( m_fRadius*cos(fTheta), +m_fHeight/2.0f, m_fRadius*sin(fTheta) );
		buffer[i+2].position = VVector3f( m_fRadius*cos(fTheta+fDelta), +m_fHeight/2.0f, m_fRadius*sin(fTheta+fDelta) );

		buffer[i+3].position = VVector3f( m_fRadius*cos(fTheta), -m_fHeight/2.0f, m_fRadius*sin(fTheta) );
		buffer[i+4].position = VVector3f( m_fRadius*cos(fTheta+fDelta), +m_fHeight/2.0f, m_fRadius*sin(fTheta+fDelta) );
		buffer[i+5].position = VVector3f( m_fRadius*cos(fTheta+fDelta), -m_fHeight/2.0f, m_fRadius*sin(fTheta+fDelta) );
		fTheta += fDelta;
	}
}
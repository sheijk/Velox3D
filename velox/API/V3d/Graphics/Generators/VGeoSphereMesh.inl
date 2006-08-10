template <typename VertexStructure>
vuint VGeoSphereMesh<VertexStructure>::CalculateVertexNumber( vuint in_nLevel )
{
	return 24 * std::pow(4, in_nLevel-1);
}


template <typename VertexStructure> 
void VGeoSphereMesh<VertexStructure>::CreateCoordinates()
{
	vbool bIterations = false;

	Triangle octahedron[] =
	{
		( Triangle(VVertex3f(+1.0f, +0.0f, +0.0f), VVertex3f(+0.0f, +1.0f, +0.0f), VVertex3f(+0.0f, +0.0f, -1.0f) )),
		( Triangle(VVertex3f(+1.0f, +0.0f, +0.0f), VVertex3f(+0.0f, +0.0f, +1.0f), VVertex3f(+0.0f, +1.0f, +0.0f) )),
		( Triangle(VVertex3f(+0.0f, -1.0f, +0.0f), VVertex3f(+1.0f, +0.0f, +0.0f), VVertex3f(+0.0f, +0.0f, -1.0f) )),
		( Triangle(VVertex3f(+0.0f, -1.0f, +0.0f), VVertex3f(+0.0f, +0.0f, +1.0f), VVertex3f(+1.0f, +0.0f, +0.0f) )),
		( Triangle(VVertex3f(-1.0f, +0.0f, +0.0f), VVertex3f(+0.0f, -1.0f, +0.0f), VVertex3f(+0.0f, +0.0f, -1.0f) )),
		( Triangle(VVertex3f(+0.0f, +1.0f, +0.0f), VVertex3f(+0.0f, +0.0f, +1.0f), VVertex3f(-1.0f, +0.0f, +0.0f) )),
		( Triangle(VVertex3f(-1.0f, +0.0f, +0.0f), VVertex3f(+0.0f, +0.0f, +1.0f), VVertex3f(+0.0f, -1.0f, +0.0f) )),
		( Triangle(VVertex3f(+0.0f, +1.0f, +0.0f), VVertex3f(-1.0f, +0.0f, +0.0f), VVertex3f(+0.0f, +0.0f, -1.0f) )),
		
        
	};

	Triangle* pStart = &octahedron[0];
	Triangle* pEnd = 0;
	vuint nNumberOfTriangles = 8;

	vuint n=0;
	for( n=1; n<m_nLevel; n++)
	{
		bIterations = true;
		nNumberOfTriangles*= 4;
        
		//Allocate memory
		pEnd = new Triangle[nNumberOfTriangles];

		for ( vuint i=0; i<nNumberOfTriangles/4; i++)
		{
			Triangle* pOldTriangle = &pStart[i];
			Triangle* pNewTriangle = &pEnd[i*4];

			VVertex3f a = Normalize( GetMidPoint(pOldTriangle->tri[0], pOldTriangle->tri[2]) );
			VVertex3f b = Normalize( GetMidPoint(pOldTriangle->tri[0], pOldTriangle->tri[1]) );
			VVertex3f c = Normalize( GetMidPoint(pOldTriangle->tri[1], pOldTriangle->tri[2]) );

			pNewTriangle[0].tri[0] = pOldTriangle->tri[0];
			pNewTriangle[0].tri[1] = b;
			pNewTriangle[0].tri[2] = a;

			pNewTriangle[1].tri[0] = b;
			pNewTriangle[1].tri[1] = pOldTriangle->tri[1];
			pNewTriangle[1].tri[2] = c;

			pNewTriangle[2].tri[0] = a;
			pNewTriangle[2].tri[1] = b;
			pNewTriangle[2].tri[2] = c;

			pNewTriangle[3].tri[0] = a;
			pNewTriangle[3].tri[1] = c;
			pNewTriangle[3].tri[2] = pOldTriangle->tri[2];

		}
		if (n>1)
			delete [] pStart;
		
        pStart = pEnd;
	}

	if (!bIterations)
		pEnd = &octahedron[0];

	VertexStructure* pVertexBuffer = buffer.GetDataAddress();
	
	vuint nIndex = 0;
	for (vuint i=0; i<buffer.GetSize(); i+=3)
	{
		buffer[i].position.v[0] = pEnd[nIndex].tri[0].v[0] * m_fRadius;
		buffer[i].position.v[1] = pEnd[nIndex].tri[0].v[1] * m_fRadius;
		buffer[i].position.v[2] = pEnd[nIndex].tri[0].v[2] * m_fRadius;

		buffer[i+1].position.v[0] = pEnd[nIndex].tri[1].v[0] * m_fRadius;
		buffer[i+1].position.v[1] = pEnd[nIndex].tri[1].v[1] * m_fRadius;
		buffer[i+1].position.v[2] = pEnd[nIndex].tri[1].v[2] * m_fRadius;
		
		buffer[i+2].position.v[0] = pEnd[nIndex].tri[2].v[0] * m_fRadius;
		buffer[i+2].position.v[1] = pEnd[nIndex].tri[2].v[1] * m_fRadius;
		buffer[i+2].position.v[2] = pEnd[nIndex].tri[2].v[2] * m_fRadius;

		nIndex++;
	}
//  This bug took 5h
//	for (vuint i=0; i<nNumberOfTriangles; i++)
//	{
//		pVertexBuffer->position = pEnd[i].tri[0];
//		pVertexBuffer++;
//		pVertexBuffer->position = pEnd[i].tri[1];
//		pVertexBuffer++;
//		pVertexBuffer->position = pEnd[i].tri[2];
//		pVertexBuffer++;
//	}
	
	if (bIterations)
        delete[] pEnd;
	pEnd = 0;
}

template <typename VertexStructure> 
void VGeoSphereMesh<VertexStructure>::CreateColor(
	v3d::graphics::VColor4f in_Colors[8]
	)
{
	vbool bIterations = false;

	TriangleColor octahedron[] =
	{
		( TriangleColor(in_Colors[0], in_Colors[1], in_Colors[2] )),
		( TriangleColor(in_Colors[0], in_Colors[3], in_Colors[1] )),
		( TriangleColor(in_Colors[4], in_Colors[0], in_Colors[2] )),
		( TriangleColor(in_Colors[4], in_Colors[3], in_Colors[0] )),
		( TriangleColor(in_Colors[5], in_Colors[4], in_Colors[2] )),
		( TriangleColor(in_Colors[1], in_Colors[3], in_Colors[5] )),
		( TriangleColor(in_Colors[5], in_Colors[3], in_Colors[4] )),
		( TriangleColor(in_Colors[1], in_Colors[5], in_Colors[2] )),
	};

	TriangleColor* pStart = &octahedron[0];
	TriangleColor* pEnd = 0;
	vuint nNumberOfTriangles = 8;

	vuint n=0;
	for( n=1; n<m_nLevel; n++)
	{
		bIterations = true;
		nNumberOfTriangles*= 4;

		//Allocate memory
		pEnd = new TriangleColor[nNumberOfTriangles];

		for ( vuint i=0; i<nNumberOfTriangles/4; i++)
		{
			TriangleColor* pOldTriangleColor = &pStart[i];
			TriangleColor* pNewTriangleColor = &pEnd[i*4];

			


			VColor4f a = VColor4f( (pOldTriangleColor->color[0].red   + pOldTriangleColor->color[2].red  ) *0.5f,
								   (pOldTriangleColor->color[0].green + pOldTriangleColor->color[2].green) *0.5f,
                                   (pOldTriangleColor->color[0].blue  + pOldTriangleColor->color[2].blue ) *0.5f,
                                   (pOldTriangleColor->color[0].alpha + pOldTriangleColor->color[2].alpha) *0.5f );

			VColor4f b = VColor4f( (pOldTriangleColor->color[0].red   + pOldTriangleColor->color[1].red  ) *0.5f,
								   (pOldTriangleColor->color[0].green + pOldTriangleColor->color[1].green) *0.5f,
								   (pOldTriangleColor->color[0].blue  + pOldTriangleColor->color[1].blue ) *0.5f,
								   (pOldTriangleColor->color[0].alpha + pOldTriangleColor->color[1].alpha) *0.5f );

			VColor4f c =  VColor4f( (pOldTriangleColor->color[1].red   + pOldTriangleColor->color[2].red  ) *0.5f,
									(pOldTriangleColor->color[1].green + pOldTriangleColor->color[2].green) *0.5f,
									(pOldTriangleColor->color[1].blue  + pOldTriangleColor->color[2].blue ) *0.5f,
									(pOldTriangleColor->color[1].alpha + pOldTriangleColor->color[2].alpha) *0.5f );


			pNewTriangleColor[0].color[0] = pOldTriangleColor->color[0];
			pNewTriangleColor[0].color[1] = b;
			pNewTriangleColor[0].color[2] = a;

			pNewTriangleColor[1].color[0] = b;
			pNewTriangleColor[1].color[1] = pOldTriangleColor->color[1];
			pNewTriangleColor[1].color[2] = c;

			pNewTriangleColor[2].color[0] = a;
			pNewTriangleColor[2].color[1] = b;
			pNewTriangleColor[2].color[2] = c;

			pNewTriangleColor[3].color[0] = a;
			pNewTriangleColor[3].color[1] = c;
			pNewTriangleColor[3].color[2] = pOldTriangleColor->color[2];
		}
		if (n>1)
			delete [] pStart;

		pStart = pEnd;
	}

	if (!bIterations)
		pEnd = &octahedron[0];

	VertexStructure* pVertexBuffer = buffer.GetDataAddress();
	vuint nIndex = 0;
	for (vuint i=0; i<buffer.GetSize(); i+=3)
	{
		buffer[i].color = pEnd[nIndex].color[0];
		buffer[i+1].color = pEnd[nIndex].color[1];
		buffer[i+2].color = pEnd[nIndex].color[2];
		
		nIndex++;
	}

	if (bIterations)
		delete[] pEnd;
	pEnd = 0;
}

template <typename VertexStructure> 
VVertex3f VGeoSphereMesh<VertexStructure>::Normalize( VVertex3f in_Vector)
{
	vfloat32 fMagnitude = in_Vector.v[0] * in_Vector.v[0]
						  + in_Vector.v[1] * in_Vector.v[1]
						  + in_Vector.v[2] * in_Vector.v[2];
	if ( fMagnitude != 0.0 )
	{
		vfloat32 fInverseMagnitude = 1.0f / sqrt(fMagnitude);
		return VVertex3f( in_Vector.v[0] * fInverseMagnitude,
						  in_Vector.v[1] * fInverseMagnitude,
						  in_Vector.v[2] * fInverseMagnitude );
	}

	return in_Vector;
}

/* Return the average of two points */
template <typename VertexStructure>
VVertex3f VGeoSphereMesh<VertexStructure>::GetMidPoint( VVertex3f in_vecA, VVertex3f in_vecB)
{
	return VVertex3f( (in_vecA.v[0] + in_vecB.v[0]) * 0.5,
					  (in_vecA.v[1] + in_vecB.v[1]) * 0.5,
                      (in_vecA.v[2] + in_vecB.v[2]) * 0.5 );
}

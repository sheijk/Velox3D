template<typename Array2d>
void GenerateNoise(Array2d& out_Area, vfloat32 in_fMin, vfloat32 in_fMax)
{
	vint randomIndex = 0;

	for(vuint y = 0; y < out_Area.GetHeight(); ++y)
	for(vuint x = 0; x < out_Area.GetWidth(); ++x)
	{
		out_Area(x,y) = PseudoRandom(randomIndex, in_fMin, in_fMax);
		++randomIndex;
	}
}

template<typename Array2d>
void Interpolate2nm1(Array2d& out_Smooth, const Array2d& in_Source)
{
	V3D_ASSERT(2 * in_Source.GetWidth() - 1 == out_Smooth.GetWidth());
	V3D_ASSERT(2 * in_Source.GetHeight() - 1 == out_Smooth.GetHeight());

	// a---b---a--
	// |   |   |  
	// c---d---c--
	// |   |   |  
	//
	// a sits at 2x,2y, b at 2x+1,2y, c at 2x,2y+1, and d at 2x+1, 2y+1

	// set all a's
	for(vuint y = 0; y < in_Source.GetHeight(); ++y)
	for(vuint x = 0; x < in_Source.GetWidth(); ++x)
	{
        out_Smooth(2*x, 2*y) = in_Source(x,y);
	}

	// set all b's
	for(vuint y = 0; y < in_Source.GetHeight(); ++y)
	for(vuint x = 0; x < in_Source.GetWidth()-1; ++x)
	{
		typename Array2d::ElementType a = in_Source(x, y);
		typename Array2d::ElementType b = in_Source(x+1, y);

		out_Smooth(2*x+1, 2*y) = (a+b)/2;
	}

	// set all c's
	for(vuint y = 0; y < in_Source.GetHeight()-1; ++y)
	for(vuint x = 0; x < in_Source.GetWidth(); ++x)
	{
		typename Array2d::ElementType a = in_Source(x,y);
		typename Array2d::ElementType b = in_Source(x,y+1);

		out_Smooth(2*x, 2*y+1) = (a+b)/2;
	}

	// set all d's
	for(vuint y = 0; y < in_Source.GetHeight()-1; ++y)
	for(vuint x = 0; x < in_Source.GetWidth()-1; ++x)
	{
		typename Array2d::ElementType a = in_Source(x+1, y);
		typename Array2d::ElementType b = in_Source(x, y+1);

		out_Smooth(2*x+1, 2*y+1) = (a+b)/2;
	}
}

template<typename Array2d>
void Stretch(
	Array2d& out_Stretched, 
	const Array2d& in_Source, 
	vuint in_nFactorX,
	vuint in_nFactorY
	)
{
}

template<typename Array2d>
void Stretch(
	Array2d& out_Stretched, 
	const Array2d& in_Source,
	vuint in_nFactor)
{
	Stretch(out_Stretched, in_Source, in_nFactor, in_nFactor);
}

template<typename Array2d>
void Add2dArray(Array2d& io_Array, const Array2d& in_Summand)
{
	V3D_ASSERT(io_Array.GetWidth() == in_Summand.GetWidth());
	V3D_ASSERT(io_Array.GetHeight() == in_Summand.GetHeight());

	for(vuint y = 0; y < io_Array.GetHeight(); ++y)
	for(vuint x = 0; x < io_Array.GetWidth(); ++x)
	{
		io_Array(x,y) += in_Summand(x,y);
	}
}

template<typename Array2d>
void GeneratePerlinNoisePow2(
	Array2d& out_Array, 
	vuint in_nSteps, 
	vfloat32 in_fPersistence)
{
	Array2d temp1;
	Array2d temp2;
	Array2d* pNoise = &temp1;
	Array2d* pStretched = &temp2;

	pNoise->Resize(3, 3, Array2d::FillZero);
	
	vfloat32 scale = 1.0f;

	// while size <= dest size
	for(vuint step = 0; step < in_nSteps; ++step)
	{
		// increase resolution of noise
		pStretched->Resize(2*pNoise->GetWidth()-1, 2*pNoise->GetHeight()-1);
		Interpolate2nm1(*pStretched, *pNoise);

		// create new noise layer
		pNoise->Resize(pStretched->GetWidth(), pStretched->GetHeight());
		GenerateNoise(*pNoise, -scale, scale);

		// add new noise layer
		Add2dArray(*pStretched, *pNoise);

		std::swap(pNoise, pStretched);

		scale /= in_fPersistence;
	}

	// copy to dest array
	out_Array.Resize(pStretched->GetWidth(), pStretched->GetHeight());

	for(vuint y = 0; y < out_Array.GetHeight(); ++y)
	for(vuint x = 0; x < out_Array.GetWidth(); ++x)
	{
		out_Array(x,y) = (*pNoise)(x,y);
	}
}

template<typename Array2d>
void GeneratePerlinNoise(Array2d& io_Array, vfloat32 in_fPersistence)
{
	vuint height = io_Array.GetWidth();
	vuint width = io_Array.GetHeight();

	// calculate param for other noise gen func
	vuint steps = 0;
	vuint size = 3;
	while(size < std::max(height, width))
	{
		size = 2 * size - 1;
		steps++;
	}

	VArray2d<vfloat32, vuint> temp;
	GeneratePerlinNoisePow2(temp, steps, in_fPersistence);

	V3D_ASSERT(temp.GetWidth() >= io_Array.GetWidth());
	V3D_ASSERT(temp.GetHeight() >= io_Array.GetHeight());

    // copy data
	for(vuint y = 0; y < height; ++y)
	for(vuint x = 0; x < width; ++x)
	{
		io_Array.Set(x,y, temp(x,y));
	}
}

/**
 * Generates a smaller version of the source array
 * source.size == 2 * dest.size - 1 must be valid
 */
template<typename Array2d>
void SampleDown(Array2d& io_Dest, const Array2d& in_Source)
{
	V3D_ASSERT(2 * io_Dest.GetWidth() - 1 == in_Source.GetWidth());
	V3D_ASSERT(2 * io_Dest.GetHeight() - 1 == in_Source.GetHeight());

	for(vuint y = 0; y < io_Dest.GetHeight(); ++y)
	for(vuint x = 0; x < io_Dest.GetWidth(); ++x)
	{
		io_Dest(x,y) = in_Source(2*x, 2*y);
	}
}



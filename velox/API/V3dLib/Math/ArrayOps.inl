template<typename Array2d>
void GenerateNoise(Array2d& out_Area)
{
	vint randomIndex = 0;

	for(vuint y = 0; y < out_Area.GetHeight(); ++y)
	for(vuint x = 0; x < out_Area.GetWidth(); ++x)
	{
		out_Area(x,y) = PseudoRandom(randomIndex);
		++randomIndex;
	}
}

template<typename Array2d>
void Interpolate2nm1(Array2d& out_Smooth, const Array2d& in_Source)
{
	V3D_ASSERT(2 * in_Source.GetWidth() - 1 == out_Smooth.GetWidth());
	V3D_ASSERT(2 * in_Source.GetHeight() - 1 == out_Smooth.GetHeight()):

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
void GeneratePerlinNoisePow2(Array2d& out_Array, vuint in_nSteps)
{
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



#ifndef V3D_ARRAYOPS_H_H
#define V3D_ARRAYOPS_H_H
//-----------------------------------------------------------------------------
#include <algorithm>

#include <v3d/Core/VCoreLib.h>

#include <V3dLib/Containers/VArray2d.h>
#include <v3d/Math/Numerics.h>
//-----------------------------------------------------------------------------
namespace v3d { 
namespace math {
//-----------------------------------------------------------------------------

/**
 * Fills the give array with pseudo random numbers based on the PseudoRandom
 * function
 *
 * @author sheijk
 */
template<typename Array2d>
void GenerateNoise(
	Array2d& out_Area, 
	vfloat32 in_fMin = -1.0f, 
	vfloat32 in_fMax = 1.0f);

/**
 * Interpolates. smooth.size must be 2 * source.size + 1
 */
template<typename Array2d>
void Interpolate2nm1(Array2d& out_Smooth, const Array2d& in_Source);

/**
 * Creates a new heightmap of greater size.
 */
template<typename Array2d>
void Stretch(
	Array2d& out_Stretched, 
	const Array2d& in_Source, 
	vuint in_nFactorX,
	vuint in_nFactorY
	);

/**
 * Redirects to Stretch(out_Stretched, in_Source, in_nFactor, in_nFactor)
 *
 * @author sheijk
 */
template<typename Array2d>
void Stretch(
	Array2d& out_Stretched, 
	const Array2d& in_Source,
	vuint in_nFactor);

template<typename Array2d>
void Add2dArray(Array2d& io_Array, const Array2d& in_Summand);

/**
 * Will fill the given array with perlin noise in the range of 
 * +- 2-(1/(in_fPersistent^in_nSteps))
 *
 * @author sheijk
 */
template<typename Array2d>
void GeneratePerlinNoisePow2(
	Array2d& out_Array, 
	vuint in_nSteps,
	vfloat32 in_fPersistance = 2.0f);

template<typename Array2d>
void GeneratePerlinNoise(
	Array2d& out_Array,
	vfloat32 in_fPersistance = 2.0f
	);

/**
 * Generates a smaller version of the source array
 * source.size == 2 * dest.size - 1 must be valid
 *
 * @author sheijk
 */
template<typename Array2d>
void SampleDown(Array2d& io_Dest, const Array2d& in_Source);

//-----------------------------------------------------------------------------
#include "ArrayOps.inl"
//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_ARRAYOPS_H_H

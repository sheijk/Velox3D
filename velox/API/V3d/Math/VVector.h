/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VVECTOR_H
#define V3D_VVECTOR_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//typedefs are at end of file
 
//-----------------------------------------------------------------------------
	
template<typename Scalar, vuint RowCount, vuint ColumnCount>
class VMatrix;

/**
	* a simple n-dimensional vector in the mathematical sense
	*/
template<typename Scalar, vuint Dimension>
class VVector
{
public:
	// do not use members and functions in this block as they are only
	// public because of some problem with friend declarations
	typedef gmtl::Vec<Scalar, Dimension> VecImpl;

	VecImpl m_Vec;

#ifndef SWIG	
	VVector(const VecImpl& implv) : m_Vec(implv) {}
#endif

public:
	VVector() {}
	~VVector() {}
	VVector(const VVector& source) : m_Vec(source.m_Vec) {}

	void Set(vuint in_Pos, Scalar in_Val)
	{
		m_Vec[in_Pos] = in_Val;
	}

	Scalar Get(vuint in_Pos) const
	{
		return m_Vec[in_Pos];
	}

	Scalar& operator[](vuint in_Pos)
	{
		return m_Vec[in_Pos];
	}

	const Scalar& operator[](vuint in_Pos) const
	{
		return m_Vec[in_Pos];
	}

	static vuint GetDimension()
	{
		return Dimension;
	}

	VVector& operator=(const VVector& source)
	{
		m_Vec = source.m_Vec;
		return *this;
	}
};

//------------------------------------------------------------------------------
#ifndef SWIG

template<typename Scalar>
class VVector<Scalar, 3>
{
public:
	// do not use members and functions in this block as they are only
	// public because of some problem with friend declarations
	typedef gmtl::Vec<Scalar, 3> VecImpl;

	VecImpl m_Vec;

	VVector(const VecImpl& implv) : m_Vec(implv) {}
public:
	VVector() {}
	~VVector() {}
	VVector(const VVector& source) : m_Vec(source.m_Vec) {}

	VVector(Scalar in_X, Scalar in_Y, Scalar in_Z)
	{
		Set(0, in_X);
		Set(1, in_Y);
		Set(2, in_Z);
	}

	void Set(vuint in_Pos, Scalar in_Val)
	{
		m_Vec[in_Pos] = in_Val;
	}
	
	void Set(Scalar x, Scalar y, Scalar z)
	{
		SetX(x);
		SetY(y);
		SetZ(z);
	}

	Scalar Get(vuint in_Pos) const
	{
		return m_Vec[in_Pos];
	}

	Scalar GetX() const { return m_Vec[0]; }
	Scalar GetY() const { return m_Vec[1]; }
	Scalar GetZ() const { return m_Vec[2]; }

	void SetX(Scalar x) { m_Vec[0] = x; }
	void SetY(Scalar y) { m_Vec[1] = y; }
	void SetZ(Scalar z) { m_Vec[2] = z; }

	Scalar& operator[](vuint in_Pos)
	{
		return m_Vec[in_Pos];
	}

	const Scalar& operator[](vuint in_Pos) const
	{
		return m_Vec[in_Pos];
	}

	static vuint GetDimension()
	{
		return 3;
	}

	VVector& operator=(const VVector& source)
	{
		m_Vec = source.m_Vec;
		return *this;
	}
};

#endif // SWIG
		
typedef VVector<vfloat32, 2> VVector2f;
typedef VVector<vfloat32, 3> VVector3f;
typedef VVector<vfloat32, 4> VVector4f;

VVector2f ToVector2f(float x, float y);
VVector3f ToVector3f(float x, float y, float z);
VVector3f XYZToVector3f(const VVector4f& vec4);
VVector3f DeHomogenize(const VVector4f& vec4);
VVector4f ToVector4f(float x, float y, float z, float w);
VVector4f ToVector4f(const VVector3f& vec3, float w);

typedef VVector<vfloat64, 2> VVector2d;
typedef VVector<vfloat64, 3> VVector3d;
typedef VVector<vfloat64, 4> VVector4d;

//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VVECTOR_H


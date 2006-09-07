/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VRECT_2004_06_19_H
#define V3D_VRECT_2004_06_19_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace math {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
 * A simple rectangle
 *
 * @author sheijk
 */
template<typename Scalar>
class VRect
{
public:
	typedef Scalar ScalarType;

	VRect(ScalarType l, ScalarType t, ScalarType r, Scalar b)
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}

	ScalarType GetWidth() const		{ return right - left; }
	ScalarType GetHeight() const	{ return bottom - top; }

	Scalar GetLeft() const		{ return left; }
	Scalar GetRight() const		{ return right; }
	Scalar GetTop()	const		{ return top; }
	Scalar GetBottom() const	{ return bottom; }

	void SetLeft(Scalar l)		{ left = l; }
	void SetRight(Scalar r)		{ right = r; }
	void SetTop(Scalar t)		{ top = t; }
	void SetBottom(Scalar b)	{ bottom = b; }

private:
	ScalarType left;
	ScalarType top;
	ScalarType right;
	ScalarType bottom;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::math
//-----------------------------------------------------------------------------
#endif // V3D_VRECT_2004_06_19_H


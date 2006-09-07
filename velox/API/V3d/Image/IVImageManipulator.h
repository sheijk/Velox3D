/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVIMAGEMANIPULATOR_04_07_23_H
#define V3D_IVIMAGEMANIPULATOR_04_07_23_H
//-------------------------------------------------------------------------
#include <v3d/Image/VImage.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace image{
//-----------------------------------------------------------------------------

/* Interface for image manipulating routines
 * @author: ins
 */

class IVImageManipulator
{
public:

	virtual void Scale(VImage& in_ImageSource, VImage& in_ImageDest) = 0;
	virtual void Convert(VImage& in_ImageSource, VImage& in_ImageDest) = 0;

protected:

	/* Call this method to register the saver to the factory */
	virtual void Register() = 0;

};
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVIMAGEMANIPULATOR_04_07_23_H

/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VDEVICEMATRIX_H
#define V3D_VDEVICEMATRIX_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Math/VMatrix.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A 4 x 4 float matrix. Layout (row/column major) depends on the device and
 * therefore no access to it's elements is granted. Only thing allowed is
 * accessing it's elements without knowing it's meaning (for device) and
 * transform from and to device
 *
 * @author sheijk
 */
class VDeviceMatrix
{
	float m_afElements[16];

public:
	typedef math::VMatrix<float, 4, 4> TransformMatrix;

	/** Standard c'tor, loads the identity matrix */
	VDeviceMatrix()
	{
		for(int index = 0; index < 16; ++index)
		{
			m_afElements[index] = 0;
		}

		m_afElements[0] = 1;
		m_afElements[5] = 1;
		m_afElements[10] = 1;
		m_afElements[15] = 1;
	}

	/**
	 * Build the matrix from an array of 16 float values
	 * Note that the array has to be in the matrix order of the device
	 * with which the matrix shall be used
	 */
	VDeviceMatrix(const float* in_pData)
	{
		memcpy(m_afElements, in_pData, 16 * sizeof(float));
	}

	/**
	 * Returns a pointer to the first element of the matrix. All elements
	 * are guaranteed to be in linear order
	 */
	float* GetElements()
	{
		return m_afElements;
	}

	/** Access the n-th element of the array */
	float& operator[](const vuint in_nIndex)
	{
		V3D_ASSERT(in_nIndex < 16);

		return m_afElements[in_nIndex];
	}

	float operator[](const vuint in_nIndex) const
	{
		V3D_ASSERT(in_nIndex < 16);

		return m_afElements[in_nIndex];
	}

	/**
	 * Builds a device dependent matrix from a mathlib matrix. The device
	 * matrix's value ordering will depend on the device format
	 */
	static void ConvertFromTransform(
		VDeviceMatrix* out_pDevMat,
		const TransformMatrix& in_TransformMat,
		const IVDevice& in_Device
		)
	{
		//TODO: device dafuer benutzen (und fkt in device tun) -- sheijk
		int index = 0;
		for(int col = 0; col < 4; ++col)
		for(int row = 0; row < 4; ++row)
		{
			out_pDevMat->m_afElements[index] = in_TransformMat.Get(row, col);
			++index;            
		}
	}

	/**
	 * Build a mathlib matrix from a device matrix using the device
	 * float ordering
	 */
	static void ConvertToTransform(
		TransformMatrix* out_pTransformMat,
		const VDeviceMatrix& in_DeviceMat,
		const IVDevice& in_Device
		)
	{
		//TODO: device dafuer ben. (und device entspr. erweitern) -- sheijk
		int index = 0;
		for(int col = 0; col < 4; ++col)
		for(int row = 0; row < 4; ++row)
		{
			out_pTransformMat->Set(row, col, in_DeviceMat[index]);
			++index;            
		}
	}
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDEVICEMATRIX_H


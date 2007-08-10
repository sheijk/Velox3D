/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VSKYDOMEGENERATOR_2007_08_10_H
#define V3D_VSKYDOMEGENERATOR_2007_08_10_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Generates a dome or a plane for the VSkyPart
 * @author ins
 */

class VSkyDomeGenerator
{
public:

	enum Mode
	{
		Dome,
		Plane
	};
	

	VSkyDomeGenerator(
		Mode in_Mode,
		vuint in_Slices,
		vuint in_Sides,
		vuint in_DivSteps,
		vfloat32 in_fRadius,
		vfloat32 in_fWidth,
		vfloat32 in_fHeight);

	~VSkyDomeGenerator();

	vfloat32* GetVertexBuffer();
	vuint* GetIndexBuffer();
	vuint GetIndexCount();
	vuint GetVertexCount();

	void SetRadius(vfloat32 in_fRadius);
	void SetSlices(vuint in_Slices);
	void SetSides(vuint in_Sides);

	vfloat32 GetRadius() const;
	vuint GetSlices() const;
	vuint GetSides() const;

private:
	void Generate();
	void GenerateVertices();
	void GeneratePlaneVertices();

	vuint* m_pIndexBuffer;
	vfloat32* m_pVertexBuffer;

	vfloat32 m_fRadius;
	vuint m_nSides;
	vuint m_nSlices;
	vuint m_nIndexCount;
	vuint m_nVertexCount;
	Mode m_Mode;


	//Plane vars go here
	vuint m_DivSteps;
	vfloat32 m_fWidth;
	vfloat32 m_fHeight;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
#endif // V3D_VSKYDOMEGENERATOR_2007_08_10_H

inline VMatrix4f& VMatrix4f::operator = (const VMatrix4f& in_rMatrix)
{
	m_pfMatrix[0][0] = in_rMatrix.m_pfMatrix[0][0];
	m_pfMatrix[0][1] = in_rMatrix.m_pfMatrix[0][1];
	m_pfMatrix[0][2] = in_rMatrix.m_pfMatrix[0][2];
	m_pfMatrix[0][3] = in_rMatrix.m_pfMatrix[0][3];
	m_pfMatrix[1][0] = in_rMatrix.m_pfMatrix[1][0];
	m_pfMatrix[1][1] = in_rMatrix.m_pfMatrix[1][1];
	m_pfMatrix[1][2] = in_rMatrix.m_pfMatrix[1][2];
	m_pfMatrix[1][3] = in_rMatrix.m_pfMatrix[1][3];
	m_pfMatrix[2][0] = in_rMatrix.m_pfMatrix[2][0];
	m_pfMatrix[2][1] = in_rMatrix.m_pfMatrix[2][1];
	m_pfMatrix[2][2] = in_rMatrix.m_pfMatrix[2][2];
	m_pfMatrix[2][3] = in_rMatrix.m_pfMatrix[2][3];
	m_pfMatrix[3][0] = in_rMatrix.m_pfMatrix[3][0];
	m_pfMatrix[3][1] = in_rMatrix.m_pfMatrix[3][1];
	m_pfMatrix[3][2] = in_rMatrix.m_pfMatrix[3][2];
	m_pfMatrix[3][3] = in_rMatrix.m_pfMatrix[3][3];
}

inline vbool VMatrix4f::operator == (const VMatrix4f& in_rMatrix)
{
	vint i = 0;
	vint j = 0;

	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
		{
			if (m_pfMatrix[i][j] != in_rMatrix.m_pfMatrix[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

inline vbool VMatrix4f::operator != (const VMatrix4f& in_rMatrix)
{
	vint i = 0;
	vint j = 0;

	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
		{
			if (m_pfMatrix[i][j] != in_rMatrix.m_pfMatrix[i][j])
			{
				return true;
			}
		}
	}

	return false;
}

inline vfloat32 VMatrix4f::Det(void) const
{
	return (m_pfMatrix[0][0] * m_pfMatrix[1][1] - m_pfMatrix[0][1] * m_pfMatrix[1][0]) * (m_pfMatrix[2][2] * m_pfMatrix[3][3] - m_pfMatrix[2][3] * m_pfMatrix[3][2]) -
		   (m_pfMatrix[0][0] * m_pfMatrix[1][2] - m_pfMatrix[0][2] * m_pfMatrix[1][0]) * (m_pfMatrix[2][1] * m_pfMatrix[3][3] - m_pfMatrix[2][3] * m_pfMatrix[3][1]) +
		   (m_pfMatrix[0][0] * m_pfMatrix[1][3] - m_pfMatrix[0][3] * m_pfMatrix[1][0]) * (m_pfMatrix[2][1] * m_pfMatrix[3][2] - m_pfMatrix[2][2] * m_pfMatrix[3][1]) +
		   (m_pfMatrix[0][1] * m_pfMatrix[1][2] - m_pfMatrix[0][2] * m_pfMatrix[1][1]) * (m_pfMatrix[2][0] * m_pfMatrix[3][3] - m_pfMatrix[2][3] * m_pfMatrix[3][0]) -
		   (m_pfMatrix[0][1] * m_pfMatrix[1][3] - m_pfMatrix[0][3] * m_pfMatrix[1][1]) * (m_pfMatrix[2][0] * m_pfMatrix[3][2] - m_pfMatrix[2][2] * m_pfMatrix[3][0]) +
		   (m_pfMatrix[0][2] * m_pfMatrix[1][3] - m_pfMatrix[0][3] * m_pfMatrix[1][2]) * (m_pfMatrix[2][0] * m_pfMatrix[3][1] - m_pfMatrix[2][1] * m_pfMatrix[3][0]);
}

inline void VMatrix4f::Identity(void)
{
	m_pfMatrix[0][0] = 1.0f; m_pfMatrix[0][1] = 0.0f; m_pfMatrix[0][2] = 0.0f; m_pfMatrix[0][3] = 0.0f;
	m_pfMatrix[1][0] = 0.0f; m_pfMatrix[1][1] = 1.0f; m_pfMatrix[1][2] = 0.0f; m_pfMatrix[1][3] = 0.0f;
	m_pfMatrix[2][0] = 0.0f; m_pfMatrix[2][1] = 0.0f; m_pfMatrix[2][2] = 1.0f; m_pfMatrix[2][3] = 0.0f;
	m_pfMatrix[3][0] = 0.0f; m_pfMatrix[3][1] = 0.0f; m_pfMatrix[3][2] = 0.0f; m_pfMatrix[3][3] = 1.0f;
}

inline void VMatrix4f::Set(const VMatrix4f& in_rMatrix)
{
	m_pfMatrix[0][0] = in_rMatrix.m_pfMatrix[0][0];
	m_pfMatrix[0][1] = in_rMatrix.m_pfMatrix[0][1];
	m_pfMatrix[0][2] = in_rMatrix.m_pfMatrix[0][2];
	m_pfMatrix[0][3] = in_rMatrix.m_pfMatrix[0][3];
	m_pfMatrix[1][0] = in_rMatrix.m_pfMatrix[1][0];
	m_pfMatrix[1][1] = in_rMatrix.m_pfMatrix[1][1];
	m_pfMatrix[1][2] = in_rMatrix.m_pfMatrix[1][2];
	m_pfMatrix[1][3] = in_rMatrix.m_pfMatrix[1][3];
	m_pfMatrix[2][0] = in_rMatrix.m_pfMatrix[2][0];
	m_pfMatrix[2][1] = in_rMatrix.m_pfMatrix[2][1];
	m_pfMatrix[2][2] = in_rMatrix.m_pfMatrix[2][2];
	m_pfMatrix[2][3] = in_rMatrix.m_pfMatrix[2][3];
	m_pfMatrix[3][0] = in_rMatrix.m_pfMatrix[3][0];
	m_pfMatrix[3][1] = in_rMatrix.m_pfMatrix[3][1];
	m_pfMatrix[3][2] = in_rMatrix.m_pfMatrix[3][2];
	m_pfMatrix[3][3] = in_rMatrix.m_pfMatrix[3][3];
}

inline void VMatrix4f::Translate(const VVector3f& in_rV)
{
	m_pfMatrix[3][0] += in_rV[0];
	m_pfMatrix[3][1] += in_rV[1];
	m_pfMatrix[3][2] += in_rV[2];
}

inline void VMatrix4f::RotateX(const vfloat32& fX)
{
	Identity();

	vfloat32 cosX = cosf(fX);
	vfloat32 sinX = sinf(fX);

	m_pfMatrix[1][1] =  cosX;
	m_pfMatrix[1][2] =  sinX;
	m_pfMatrix[2][1] = -sinX;
	m_pfMatrix[2][2] = cosX;

	
}

inline void VMatrix4f::RotateY(const vfloat32& fY)
{
	Identity();

	vfloat32 cosY = cosf(fY);
	vfloat32 sinY = sinf(fY);

	m_pfMatrix[0][0] =  cosY;
	m_pfMatrix[0][2] = -sinY;
	m_pfMatrix[2][0] = sinY;
	m_pfMatrix[2][2] = cosY;


}

inline void VMatrix4f::RotateZ(const vfloat32& fZ)
{
	Identity();

	vfloat32 cosZ = cosf(fZ);
	vfloat32 sinZ = sinf(fZ);

	m_pfMatrix[0][0] =  cosZ;
	m_pfMatrix[0][1] = sinZ;
	m_pfMatrix[1][0] = -sinZ;
	m_pfMatrix[1][1] = cosZ;

}

inline void VMatrix4f::Multiply(const VMatrix4f& in_rMatrix, const VMatrix4f& in_rMatrix2)
{


	m_pfMatrix[0][0] = (in_rMatrix.m_pfMatrix[0][0] * in_rMatrix2.m_pfMatrix[0][0])
				      +(in_rMatrix.m_pfMatrix[0][1] * in_rMatrix2.m_pfMatrix[1][0])
					  +(in_rMatrix.m_pfMatrix[0][2] * in_rMatrix2.m_pfMatrix[2][0])
					  +(in_rMatrix.m_pfMatrix[0][3] * in_rMatrix2.m_pfMatrix[3][0]);

	m_pfMatrix[0][1] = (in_rMatrix.m_pfMatrix[0][0] * in_rMatrix2.m_pfMatrix[0][1])
				      +(in_rMatrix.m_pfMatrix[0][1] * in_rMatrix2.m_pfMatrix[1][1])
					  +(in_rMatrix.m_pfMatrix[0][2] * in_rMatrix2.m_pfMatrix[2][1])
					  +(in_rMatrix.m_pfMatrix[0][3] * in_rMatrix2.m_pfMatrix[3][2]);

	m_pfMatrix[0][2] = (in_rMatrix.m_pfMatrix[0][0] * in_rMatrix2.m_pfMatrix[0][2])
				      +(in_rMatrix.m_pfMatrix[0][1] * in_rMatrix2.m_pfMatrix[1][2])
					  +(in_rMatrix.m_pfMatrix[0][2] * in_rMatrix2.m_pfMatrix[2][2])
					  +(in_rMatrix.m_pfMatrix[0][3] * in_rMatrix2.m_pfMatrix[3][2]);

	m_pfMatrix[0][3] = (in_rMatrix.m_pfMatrix[0][0] * in_rMatrix2.m_pfMatrix[0][3])
				      +(in_rMatrix.m_pfMatrix[0][1] * in_rMatrix2.m_pfMatrix[1][3])
					  +(in_rMatrix.m_pfMatrix[0][2] * in_rMatrix2.m_pfMatrix[2][3])
					  +(in_rMatrix.m_pfMatrix[0][3] * in_rMatrix2.m_pfMatrix[3][3]);



	m_pfMatrix[1][0] = (in_rMatrix.m_pfMatrix[1][0] * in_rMatrix2.m_pfMatrix[0][0])
				      +(in_rMatrix.m_pfMatrix[1][1] * in_rMatrix2.m_pfMatrix[1][0])
					  +(in_rMatrix.m_pfMatrix[1][2] * in_rMatrix2.m_pfMatrix[2][0])
					  +(in_rMatrix.m_pfMatrix[1][3] * in_rMatrix2.m_pfMatrix[3][0]);

	m_pfMatrix[1][1] = (in_rMatrix.m_pfMatrix[1][0] * in_rMatrix2.m_pfMatrix[0][1])
				      +(in_rMatrix.m_pfMatrix[1][1] * in_rMatrix2.m_pfMatrix[1][1])
					  +(in_rMatrix.m_pfMatrix[1][2] * in_rMatrix2.m_pfMatrix[2][1])
					  +(in_rMatrix.m_pfMatrix[1][3] * in_rMatrix2.m_pfMatrix[3][1]);

	m_pfMatrix[1][2] = (in_rMatrix.m_pfMatrix[1][0] * in_rMatrix2.m_pfMatrix[0][2])
				      +(in_rMatrix.m_pfMatrix[1][1] * in_rMatrix2.m_pfMatrix[1][2])
					  +(in_rMatrix.m_pfMatrix[1][2] * in_rMatrix2.m_pfMatrix[2][2])
					  +(in_rMatrix.m_pfMatrix[1][3] * in_rMatrix2.m_pfMatrix[3][2]);

	m_pfMatrix[1][3] = (in_rMatrix.m_pfMatrix[1][0] * in_rMatrix2.m_pfMatrix[0][3])
				      +(in_rMatrix.m_pfMatrix[1][1] * in_rMatrix2.m_pfMatrix[1][3])
					  +(in_rMatrix.m_pfMatrix[1][2] * in_rMatrix2.m_pfMatrix[2][3])
					  +(in_rMatrix.m_pfMatrix[1][3] * in_rMatrix2.m_pfMatrix[3][3]);

	m_pfMatrix[2][0] = (in_rMatrix.m_pfMatrix[2][0] * in_rMatrix2.m_pfMatrix[0][0])
				      +(in_rMatrix.m_pfMatrix[2][1] * in_rMatrix2.m_pfMatrix[1][3])
					  +(in_rMatrix.m_pfMatrix[2][2] * in_rMatrix2.m_pfMatrix[2][0])
					  +(in_rMatrix.m_pfMatrix[2][3] * in_rMatrix2.m_pfMatrix[3][0]);
	
	m_pfMatrix[2][1] = (in_rMatrix.m_pfMatrix[2][0] * in_rMatrix2.m_pfMatrix[0][1])
				      +(in_rMatrix.m_pfMatrix[2][1] * in_rMatrix2.m_pfMatrix[2][0])
					  +(in_rMatrix.m_pfMatrix[2][2] * in_rMatrix2.m_pfMatrix[2][1])
					  +(in_rMatrix.m_pfMatrix[2][3] * in_rMatrix2.m_pfMatrix[3][1]);

	m_pfMatrix[2][2] = (in_rMatrix.m_pfMatrix[2][0] * in_rMatrix2.m_pfMatrix[0][2])
				      +(in_rMatrix.m_pfMatrix[2][1] * in_rMatrix2.m_pfMatrix[2][1])
					  +(in_rMatrix.m_pfMatrix[2][2] * in_rMatrix2.m_pfMatrix[2][2])
					  +(in_rMatrix.m_pfMatrix[2][3] * in_rMatrix2.m_pfMatrix[3][2]);

	m_pfMatrix[2][3] = (in_rMatrix.m_pfMatrix[2][0] * in_rMatrix2.m_pfMatrix[0][3])
				      +(in_rMatrix.m_pfMatrix[2][1] * in_rMatrix2.m_pfMatrix[2][2])
					  +(in_rMatrix.m_pfMatrix[2][2] * in_rMatrix2.m_pfMatrix[2][3])
					  +(in_rMatrix.m_pfMatrix[2][3] * in_rMatrix2.m_pfMatrix[3][3]);

	m_pfMatrix[3][0] = (in_rMatrix.m_pfMatrix[3][0] * in_rMatrix2.m_pfMatrix[0][0])
				      +(in_rMatrix.m_pfMatrix[3][1] * in_rMatrix2.m_pfMatrix[1][0])
					  +(in_rMatrix.m_pfMatrix[3][2] * in_rMatrix2.m_pfMatrix[2][0])
					  +(in_rMatrix.m_pfMatrix[3][3] * in_rMatrix2.m_pfMatrix[3][0]);

	m_pfMatrix[3][1] = (in_rMatrix.m_pfMatrix[3][0] * in_rMatrix2.m_pfMatrix[0][1])
				      +(in_rMatrix.m_pfMatrix[3][1] * in_rMatrix2.m_pfMatrix[1][1])
					  +(in_rMatrix.m_pfMatrix[3][2] * in_rMatrix2.m_pfMatrix[2][1])
					  +(in_rMatrix.m_pfMatrix[3][3] * in_rMatrix2.m_pfMatrix[3][1]);

	m_pfMatrix[3][2] = (in_rMatrix.m_pfMatrix[3][0] * in_rMatrix2.m_pfMatrix[0][2])
				      +(in_rMatrix.m_pfMatrix[3][1] * in_rMatrix2.m_pfMatrix[1][2])
					  +(in_rMatrix.m_pfMatrix[3][2] * in_rMatrix2.m_pfMatrix[2][2])
					  +(in_rMatrix.m_pfMatrix[3][3] * in_rMatrix2.m_pfMatrix[3][2]);

	m_pfMatrix[3][3] = (in_rMatrix.m_pfMatrix[3][0] * in_rMatrix2.m_pfMatrix[0][3])
				      +(in_rMatrix.m_pfMatrix[3][1] * in_rMatrix2.m_pfMatrix[1][3])
					  +(in_rMatrix.m_pfMatrix[3][2] * in_rMatrix2.m_pfMatrix[2][3])
					  +(in_rMatrix.m_pfMatrix[3][3] * in_rMatrix2.m_pfMatrix[3][3]);

}
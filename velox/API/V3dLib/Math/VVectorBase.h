#ifndef V3D_VVECTORBASE_01_19_04_H
#define V3D_VVECTORBASE_01_19_04_H
//-----------------------------------------------------------------------------
namespace v3d {
namespace math {
//-----------------------------------------------------------------------------
/**
 * Defines a 3D base for spanning a vector space
 *
 * @author: ins
 * TODO: in cpp verschieben
 */

template<typename Scalar>
class VVectorBase
{
public:

	/**
	 * Default constructor. we are using a standard righthanded system
	 * with i pointing towards us, j pointing to the right and k pointing up
	 */
	VVectorBase()
	{
		m_i[0] = 1.0f;
		m_i[1] = 0.0f;
		m_i[2] = 0.0f;
	
		m_j[0] = 0.0f;
		m_j[1] = 1.0f;
		m_j[2] = 0.0f;

		m_k[0] = 0.0f;
		m_k[1] = 0.0f;
		m_k[2] = 1.0f;
	}

	VVectorBase(const VVector<Scalar, 3>& in_I,
		const VVector<Scalar, 3>& in_J,
		const VVector<Scalar, 3>& in_K)
	{
		m_i = in_I;
		m_j = in_J;
		m_k = in_K;
	}

	VVectorBase(const VVectorBase& in_VectorBase)
	{
		m_i = in_VectorBase.m_i;
		m_j = in_VectorBase.m_j;
		m_k = in_VectorBase.m_k;
	}

	VVectorBase& operator= (const VVectorBase& in_VectorBase)
	{
		this->m_i = in_VectorBase.m_i;
		this->m_j = in_VectorBase.m_j;
		this->m_k = in_VectorBase.m_k;

		return *this;
	}

	vbool IsRightHanded()
	{
		Scalar f = Dot(m_i,(Cross(m_j, m_k)));
		if(f > 0)
			return true;
		else
			return false;
	}

	vbool IsLeftHanded()
	{
		if(IsRightHanded())
			return false;
		else
			return true;
	}

	/**
	 * checks if vectors are forming a base
	 * @param: tolerance - floating point tolerance default: 0.0001
	 * @return returns true if vectors spanning a space false otherwise
	 */
	vbool IsOrthogonal(Scalar tolerance = 0.0001f)
	{
		//if we have normalized vectors we can do
		//a fast check with the dot product
		//@note: normalization check rules out dot operation fastness :/
		if(IsNormalized())
		{
			Scalar s = Dot(m_i, m_j);
			//we consider this as parallel
            if((s <= tolerance) && (s >= -tolerance))
			{
				//ok, so far i and j are perpendicular
				s = Dot(m_i, m_k);
					if((s <= tolerance) && (s >= -tolerance) )
					{
						//so far i and k are perpendicular
						//now check j and k
						s = Dot(m_j, m_k);
                        if((s <= tolerance) && (s >= -tolerance))
                            return true;
						else
							return false;
					}
					else
						return false;
			}
			else
				return false;

		}

		//ok, no cheap check available, let's do it with cross product
		else
		{
			VVector<Scalar, 3> r = Cross(m_i, m_j);
			Scalar s = 1 - Dot(r,r);

			//check if i and j are orthogonal
			if((s <= tolerance) && (s >= -tolerance))
			{
				r = Cross(m_i, m_k);
				s = 1 - Dot(r,r);
				
				//check if i and k are orthogonal 
				if((s <= tolerance) && (s >= -tolerance))
				{
					//now we need to know if j and k are orthogonal
					r = Cross(m_j, m_k);
					s = 1 - Dot(r,r);

					if((s <= tolerance) && (s >= -tolerance))
						return true;
					else
						return false;
				}
				else
					return false;
			}
			else
				return false;
		}
	}
	
	/**
	 * checks if all 3 vectors forming the base are unit length
	 * @param tolerance - float precision tolerance default: 0.0001
	 * @return: true if all are unit length false otherwise
	 */
	vbool IsNormalized(Scalar tolerance = 0.0001 )
	{
		return (v3d::IsNormalized(m_i) &&
			v3d::IsNormalized(m_j) &&
			v3d::IsNormalized(m_k));
	}

	/**
	 * construct the closest base (linear independant vectors) for
	 * a non unit length and/or orthogonal set of vectors using the
	 * Gram-Schmidt algorithm
	 *
     * @note: useful for a base that got linear dependant by precession lost
	 * @note: doesnt work if we have 2 parallel vectors
	 */
	void Orthogonalize()
	{
		//take the first vector as the first basis triple
		VVector<Scalar, 3> w0 = m_i;

		//now we construct the second base triple by projecting
		//the given one onto w0. note that we are normalize
		//the resulting dot*w0 vector so that the projection is easily
		//(m_j dot w0)*w0
		VVector<Scalar, 3> w1 = m_j - (Dot(m_j, w0)/LengthSquared(w0))*w0;

		//now we construct the last one of our triple
		VVector<Scalar, 3> w2 = m_k - ((Dot(m_k, w0)/LengthSquared(w0))*w0
			- (Dot(m_k, w1)/LengthSquared(w1))*w1);

		//save the triple as our new base
		Normalize(w0);
		Normalize(w1);
		Normalize(w2);

		m_i = w0; 
		m_j = w1;
		m_k	= w2;
	}

	void SetI(const VVector<Scalar, 3>& in_Vector)
	{
		m_i = in_Vector;
	}

	void SetI(const Scalar in_X, const Scalar in_Y, const Scalar in_Z)
	{
		m_i[0] = in_X;
		m_i[1] = in_Y;
		m_i[2] = in_Z;
	}

	void SetJ(const VVector<Scalar, 3>& in_Vector)
	{
		m_j = in_Vector;
	}

	void SetJ(const Scalar in_X, const Scalar in_Y, const Scalar in_Z)
	{
		m_j[0] = in_X;
		m_j[1] = in_Y;
		m_j[2] = in_Z;
	}

	void SetK(const VVector<Scalar, 3>& in_Vector)
	{
		m_k = in_Vector; 
	}

	void SetK(const Scalar in_X, const Scalar in_Y, const Scalar in_Z)
	{
		m_k[0] = in_X;
		m_k[1] = in_Y;
		m_k[2] = in_Z;
	}

	void Set(const VVector<Scalar, 3>& in_VectorI,
		const VVector<Scalar, 3>& in_VectorJ,
		const VVector<Scalar, 3>& in_VectorK
		)
	{
		m_i = in_VectorI;
		m_j = in_VectorJ;
		m_k = in_VectorK;
	}

	VVector<Scalar, 3> GetI()
	{
		return m_i;
	}

	VVector<Scalar, 3> GetJ()
	{
		return m_j;
	}
	VVector<Scalar, 3> GetK()
	{
		return m_k;
	}

private:

	VVector<Scalar, 3> m_i;
	VVector<Scalar, 3> m_j;
	VVector<Scalar, 3> m_k;
};

typedef VVectorBase<vfloat32> VVectorBase3f;
typedef VVectorBase<vfloat64> VVectorBase3d;
//-----------------------------------------------------------------------------
} // namespace math
} // namespace v3d
//-----------------------------------------------------------------------------
#endif V3D_VVECTORBASE_01_19_04_H
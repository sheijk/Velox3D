#ifndef V3D_VSWINGFUNTION_2005_01_30_H
#define V3D_VSWINGFUNTION_2005_01_30_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
 * A simple function. The value will move between min and max, each time it
 * is update it will change by diff * in_amout
 */
class VSwingFunction
{
	vfloat32 m_fValue;
	vfloat32 m_fDifference;

	const vfloat32 m_fMin;
	const vfloat32 m_fMax;

public:
	VSwingFunction(vfloat32 diff, vfloat32 minval, vfloat32 maxval)
		: m_fDifference(diff), m_fMin(minval), m_fMax(maxval)
	{
		m_fValue = (m_fMax+m_fMin)/2.0f;

		V3D_ASSERT(m_fMin <= m_fValue);
		V3D_ASSERT(m_fValue <= m_fMax);
	}

	vfloat32 GetValue() const { return m_fValue; }

	void Update(vfloat32 in_fAmount)
	{
		m_fValue += in_fAmount * m_fDifference;

		if( m_fMax < m_fValue )
		{
			m_fDifference = - m_fDifference;
			m_fValue = m_fMax;
		}
		else if( m_fValue < m_fMin ) 
		{
			m_fDifference = - m_fDifference;
			m_fValue = m_fMin;
		}

		V3D_ASSERT(m_fMin <= m_fValue);
		V3D_ASSERT(m_fValue <= m_fMax);
	}
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSWINGFUNTION_2005_01_30_H

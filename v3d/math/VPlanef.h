#ifndef V3D_VPLANEF_H
#define V3D_VPLANEF_H

#include <Math/VVector3f.h>

class VPlanef
{
private :

	VVector3f m_Normal;
	vfloat32 m_fDistance;

public :

	VPlanef(void);

	inline vfloat32	GetDistance(void) const;
	inline VVector3f& GetNormal(void);
	inline void GetNormal(VVector3f& in_rNormal) const;
	inline void	SetDistance(const vfloat32 in_fDistance);
	inline void	SetNormal(const VVector3f& in_rNormal);
};

#include <Math/VPlanef.inl>

#endif
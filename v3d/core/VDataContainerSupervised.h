#ifndef V3D_VDATACONTAINERSUPERVISED_H
#define V3D_VDATACONTAINERSUPERVISED_H
//---------------------------------------------------------------------------
#pragma warning(disable: 4786)

#include <Core/VDataContainer.h>

// *** VDataContainerSupervised ***
// Synopsis:
//    - same like data container but a callback function will be called when
//    a value is changed
class VDataContainerSupervised :public VDataContainer
{
public:
   typedef vbool (*SupervisorFunc)(VDataContainerSupervised* pData, DataId id);

   // *** VDataContainerSupervised ***
   // Synopsis:
   //    - constructor
   // Inputs:
   //    - SupervisorFunc pFunc: pointer to a callback function that will be
   //    called when an option is changed 
   VDataContainerSupervised(SupervisorFunc pFunc);

   void SetText(DataId id, std::string strVal);
   void SetBool(DataId id, vbool bVal);
   void SetNumber(DataId id, vint bNumber);
private:
   VDataContainerSupervised();
protected:
   SupervisorFunc m_pSupervisorFunc;
};
//---------------------------------------------------------------------------
#endif
 
#include <v3d/Core/VIOStream.h>
#include "VSystemManager.h"
#include "../UtilsLib/CPUDetect/VDetectProcessor.h"
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
namespace v3d {
namespace system {
//-----------------------------------------------------------------------------

VSystemManager::VSystemManager(VStringParam in_Name) :
													VNamedObject (in_Name, 0)
{
	m_bIsRunning = false;
}
//-----------------------------------------------------------------------------

VSystemManager::~VSystemManager()
{
}
//-----------------------------------------------------------------------------

void VSystemManager::GetCPU()
{
	utils::VDetectProcessor CPUInfo;
	CPUInfo.GetCPUInfo();
	vout << "Detetcting CPU:" << vendl;
	vout << "Name: " << CPUInfo.m_cCPUName << vendl;
	vout << "Vendor: " << CPUInfo.m_CPUInfo.strVendor << vendl;
	vout << "Family: " << CPUInfo.m_CPUInfo.strFamily << vendl;
	vout << "Model: " << CPUInfo.m_CPUInfo.strModel << vendl;
	vout << "Serial: " << CPUInfo.m_CPUInfo.strProcessorSerial << vendl;
	vout << "BrandID: " << CPUInfo.m_CPUInfo.strBrandID << vendl;
	vout << "Type: " << CPUInfo.m_CPUInfo.strType << vendl;
	vout << "L1 Cache: " << CPUInfo.m_CPUInfo._L1.Data.strCache << vendl;
	vout << "L2 Cache: " << CPUInfo.m_CPUInfo._L2.strCache << vendl;
	vout << "Trace: " << CPUInfo.m_CPUInfo._Trace.strCache << vendl;
    vout << "Instructions: " << CPUInfo.m_CPUInfo._Instruction.strTLB << vendl;
	vout << "Data: " << CPUInfo.m_CPUInfo._Data.strTLB << vendl;
	vout << "-------------------------------------------------------" << vendl;
}
//-----------------------------------------------------------------------------

void VSystemManager::SetStatus(vbool in_Param)
{
	m_bIsRunning = in_Param;
}
//-----------------------------------------------------------------------------

vbool VSystemManager::GetStatus()
{
	return m_bIsRunning;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
} // namespace system
} // namespace v3d
//-----------------------------------------------------------------------------

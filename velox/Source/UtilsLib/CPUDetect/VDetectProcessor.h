#ifndef V3D_VDETECTPROCESSOR_H
#define V3D_VDETECTPROCESSOR_H
//-----------------------------------------------------------------------------
#include <windows.h>

// *raeusper* cstdio, cstring, cmemory, dann sind die fkten auch alle
// brav im std namepace - wir programmieren schliesslich C++ und nicht
// C ;) -sheijk
// 2.: muessen die alle hier included werden anstatt in der .cpp? -sheijk
#include <stdio.h>
#include <string.h>
#include <memory.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
//-----------------------------------------------------------------------------
// *nochmal.raeusper* V3D_CAPS fuer makros. + fuer sowas reicht ne inline
// fkt voellig aus -sheijk
#define CheckBit(var, bit)   ((var & (1 << bit)) ? true : false)
//-----------------------------------------------------------------------------

/**
 * VDetectProcessor
 *
 * Synopsis: gets the processor data of the target machine
 *
 * History: based upon code from Benjamin Jurke
 *
 */
//-----------------------------------------------------------------------------
namespace v3d{
namespace util{
//-----------------------------------------------------------------------------

class VDetectProcessor
{

private:

	class VProcessorExtensions
	{
	public:
		vbool FPU_FloatingPointUnit;
		vbool VME_Virtual8086ModeEnhancements;
		vbool DE_DebuggingExtensions;
		vbool PSE_PageSizeExtensions;
		vbool TSC_TimeStampCounter;
		vbool MSR_ModelSpecificRegisters;
		vbool PAE_PhysicalAddressExtension;
		vbool MCE_MachineCheckException;
		vbool CX8_COMPXCHG8B_Instruction;
		vbool APIC_AdvancedProgrammableInterruptController;
		vuint APIC_ID;
		vbool SEP_FastSystemCall;
		vbool MTRR_MemoryTypeRangeRegisters;
		vbool PGE_PTE_GlobalFlag;
		vbool MCA_MachineCheckArchitecture;
		vbool CMOV_ConditionalMoveAndCompareInstructions;
		vbool FGPAT_PageAttributeTable;
		vbool PSE36_36bitPageSizeExtension;
		vbool PN_ProcessorSerialNumber;
		vbool CLFSH_CFLUSH_Instruction;
		vuint CLFLUSH_InstructionCacheLineSize;
		vbool DS_DebugStore;
		vbool ACPI_ThermalMonitorAndClockControl;
		vbool EMMX_MultimediaExtensions;
		vbool MMX_MultimediaExtensions;
		vbool FXSR_FastStreamingSIMD_ExtensionsSaveRestore;
		vbool SSE_StreamingSIMD_Extensions;
		vbool SSE2_StreamingSIMD2_Extensions;
		vbool SS_SelfSnoop;
		vbool HT_HyperThreading;
		vuint HT_HyterThreadingSiblings;
		vbool TM_ThermalMonitor;
		vbool IA64_Intel64BitArchitecture;
		vbool _3DNOW_InstructionExtensions;
		vbool _E3DNOW_InstructionExtensions;
		vbool AA64_AMD64BitArchitecture;
	};

	class VProcessorCache
	{
	public:

		vbool bPresent;
		vchar strSize[32];
		vuint uiAssociativeWays;
		vuint uiLineSize;
		vbool bSectored;
		vchar strCache[128];

	};

	class VProcessorL1Cache
	{
	public:
		VProcessorCache Instruction;
		VProcessorCache Data;
	};

	class VProcessorTLB
	{
	public:
		vbool bPresent;
		vchar strPageSize[32];
		vuint uiAssociativeWays;
		vuint uiEntries;
		vchar strTLB[128];
	};

	class VProcessorInfo
	{
	public:
		vchar strVendor[16];
		vuint uiFamily;
		vuint uiExtendedFamily;
		vchar strFamily[64];
		vuint uiModel;
		vuint uiExtendedModel;
		vchar strModel[128];
		vuint uiStepping;
		vuint uiType;
		vchar strType[64];
		vuint uiBrandID;
		vchar strBrandID[64];
		vchar strProcessorSerial[64];
		vulong MaxSupportedLevel;
		vulong MaxSupportedExtendedLevel;
		VProcessorExtensions _Ext;
		VProcessorL1Cache _L1;
		VProcessorCache _L2;
		VProcessorCache _L3;
		VProcessorCache _Trace;
		VProcessorTLB _Instruction;
		VProcessorTLB _Data;
	};

	public:

	vint64 m_iFrequency;
	vchar m_cCPUName[128];
	VProcessorInfo m_CPUInfo;

	private:

	vbool AnalyzeIntelProcessor();
	vbool AnalyzeAMDProcessor();
	vbool AnalyzeUnknownProcessor();
	vbool CheckCPUIDPresence();
	vchar* VDetectProcessor::TranslateAssociativeWays(vuint uiWays, vchar *buf);
	void DecodeProcessorConfiguration(vuint Cfg);
	void TranslateProcessorConfiguration();
	void GetStandardProcessorConfiguration();
	void GetStandardProcessorExtensions();
	void TranslateTLB(VProcessorTLB *tlb);
	void TranslateCache(VProcessorCache *cache);


public:

	VDetectProcessor(void);
	
	vint64 GetCPUFrequency(vuint uiMeasureMSecs);
	void  GetCPUInfo();
	
};

//-----------------------------------------------------------------------------
} // namespace util
} // namespace v3d
//-----------------------------------------------------------------------------

#endif //V3D_VDETECTPROCESSOR_H

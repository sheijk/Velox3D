#include "VDetectProcessor.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d{
namespace util{
//-----------------------------------------------------------------------------

VDetectProcessor::VDetectProcessor()
{
	m_iFrequency = 0;
	memset(&m_CPUInfo, 0, sizeof(VProcessorInfo));
}
//-----------------------------------------------------------------------------

vbool VDetectProcessor::CheckCPUIDPresence()
{
	vulong BitChanged;
	
	// We've to check if we can toggle the flag register bit 21
	// If we can't the processor does not support the CPUID command
	__asm
	{
		pushfd
		pop eax
		mov ebx, eax
		xor eax, 0x00200000 
		push eax
		popfd
		pushfd
		pop eax
		xor eax,ebx 
		mov BitChanged, eax
	}

	return ((BitChanged) ? true : false);
}
//-----------------------------------------------------------------------------

void VDetectProcessor::GetStandardProcessorExtensions()
{
	vulong ebxreg, edxreg;

	// We check if the CPUID command is available
	if (!CheckCPUIDPresence())
		return;
	// We just get the standard CPUID level 0x00000001 which should be
	// available on every x86 processor
	__asm
	{
		mov eax, 1
			cpuid
			mov ebxreg, ebx
			mov edxreg, edx
	}

	// Then we mask some bits
	m_CPUInfo._Ext.FPU_FloatingPointUnit				= CheckBit(edxreg, 0);
	m_CPUInfo._Ext.VME_Virtual8086ModeEnhancements		= CheckBit(edxreg, 1);
	m_CPUInfo._Ext.DE_DebuggingExtensions				= CheckBit(edxreg, 2);
	m_CPUInfo._Ext.PSE_PageSizeExtensions				= CheckBit(edxreg, 3);
	m_CPUInfo._Ext.TSC_TimeStampCounter					= CheckBit(edxreg, 4);
	m_CPUInfo._Ext.MSR_ModelSpecificRegisters			= CheckBit(edxreg, 5);
	m_CPUInfo._Ext.PAE_PhysicalAddressExtension			= CheckBit(edxreg, 6);
	m_CPUInfo._Ext.MCE_MachineCheckException			= CheckBit(edxreg, 7);
	m_CPUInfo._Ext.CX8_COMPXCHG8B_Instruction			= CheckBit(edxreg, 8);
	m_CPUInfo._Ext.APIC_AdvancedProgrammableInterruptController
														= CheckBit(edxreg, 9);
	m_CPUInfo._Ext.APIC_ID = (ebxreg >> 24) & 0xFF;
	m_CPUInfo._Ext.SEP_FastSystemCall					= CheckBit(edxreg, 11);
	m_CPUInfo._Ext.MTRR_MemoryTypeRangeRegisters		= CheckBit(edxreg, 12);
	m_CPUInfo._Ext.PGE_PTE_GlobalFlag					= CheckBit(edxreg, 13);
	m_CPUInfo._Ext.MCA_MachineCheckArchitecture			= CheckBit(edxreg, 14);
	m_CPUInfo._Ext.CMOV_ConditionalMoveAndCompareInstructions
														= CheckBit(edxreg, 15);
	m_CPUInfo._Ext.FGPAT_PageAttributeTable				= CheckBit(edxreg, 16);
	m_CPUInfo._Ext.PSE36_36bitPageSizeExtension			= CheckBit(edxreg, 17);
	m_CPUInfo._Ext.PN_ProcessorSerialNumber				= CheckBit(edxreg, 18);
	m_CPUInfo._Ext.CLFSH_CFLUSH_Instruction				= CheckBit(edxreg, 19);
	m_CPUInfo._Ext.CLFLUSH_InstructionCacheLineSize = (ebxreg >> 8) & 0xFF;
	m_CPUInfo._Ext.DS_DebugStore						= CheckBit(edxreg, 21);
	m_CPUInfo._Ext.ACPI_ThermalMonitorAndClockControl	= CheckBit(edxreg, 22);
	m_CPUInfo._Ext.MMX_MultimediaExtensions				= CheckBit(edxreg, 23);
	m_CPUInfo._Ext.FXSR_FastStreamingSIMD_ExtensionsSaveRestore
														= CheckBit(edxreg, 24);
	m_CPUInfo._Ext.SSE_StreamingSIMD_Extensions			= CheckBit(edxreg, 25);
	m_CPUInfo._Ext.SSE2_StreamingSIMD2_Extensions		= CheckBit(edxreg, 26);
	m_CPUInfo._Ext.SS_SelfSnoop							= CheckBit(edxreg, 27);
	m_CPUInfo._Ext.HT_HyperThreading					= CheckBit(edxreg, 28);
	m_CPUInfo._Ext.HT_HyterThreadingSiblings = (ebxreg >> 16) & 0xFF;
	m_CPUInfo._Ext.TM_ThermalMonitor					= CheckBit(edxreg, 29);
	m_CPUInfo._Ext.IA64_Intel64BitArchitecture			= CheckBit(edxreg, 30);
}
//-----------------------------------------------------------------------------

vbool VDetectProcessor::AnalyzeUnknownProcessor()
{
	vulong eaxreg, ebxreg;

	// We check if the CPUID command is available
	if (!CheckCPUIDPresence())
		return false;

	// First of all we read the standard CPUID level 0x00000001
	// This level should be available on every x86-processor clone
	__asm
	{
        mov eax, 1
		cpuid
		mov eaxreg, eax
		mov ebxreg, ebx
	}
	// Then we mask the processor model, family, type and stepping
	m_CPUInfo.uiStepping = eaxreg & 0xF;
	m_CPUInfo.uiModel    = (eaxreg >> 4) & 0xF;
	m_CPUInfo.uiFamily   = (eaxreg >> 8) & 0xF;
	m_CPUInfo.uiType     = (eaxreg >> 12) & 0x3;

	// To have complete information we also mask the brand id
	m_CPUInfo.uiBrandID  = ebxreg & 0xF;

	// Then we get the standard processor extensions
	GetStandardProcessorExtensions();

	// Now we mark everything we do not know as unknown
	strcpy(m_cCPUName, "Unknown");

	strcpy(m_CPUInfo._Data.strTLB, "Unknown");
	strcpy(m_CPUInfo._Instruction.strTLB, "Unknown");
	
	strcpy(m_CPUInfo._Trace.strCache, "Unknown");
	strcpy(m_CPUInfo._L1.Data.strCache, "Unknown");
	strcpy(m_CPUInfo._L1.Instruction.strCache, "Unknown");
	strcpy(m_CPUInfo._L2.strCache, "Unknown");
	strcpy(m_CPUInfo._L3.strCache, "Unknown");

	strcpy(m_CPUInfo.strProcessorSerial, "Unknown / Not supported");

	// For the family, model and brand id we can only print the numeric value
	sprintf(m_CPUInfo.strBrandID, "Brand-ID number %d", m_CPUInfo.uiBrandID);
	sprintf(m_CPUInfo.strFamily, "Family number %d", m_CPUInfo.uiFamily);
	sprintf(m_CPUInfo.strModel, "Model number %d", m_CPUInfo.uiModel);

	// Nevertheless we can determine the processor type
    switch (m_CPUInfo.uiType)
	{
		case 0:
			strcpy(m_CPUInfo.strType, "Original OEM");
			break;
		case 1:
			strcpy(m_CPUInfo.strType, "Overdrive");
			break;
		case 2:
			strcpy(m_CPUInfo.strType, "Dual-capable");
			break;
		case 3:
			strcpy(m_CPUInfo.strType, "Reserved");
			break;
		default:
			strcpy(m_CPUInfo.strType, "Unknown");
			break;
    }

	// And thats it
	return true;
}
//-----------------------------------------------------------------------------

void VDetectProcessor::TranslateProcessorConfiguration()
{
	// We just call the small functions defined above
	TranslateTLB(&m_CPUInfo._Data);
	TranslateTLB(&m_CPUInfo._Instruction);

	TranslateCache(&m_CPUInfo._Trace);

	TranslateCache(&m_CPUInfo._L1.Instruction);
	TranslateCache(&m_CPUInfo._L1.Data);
	TranslateCache(&m_CPUInfo._L2);
	TranslateCache(&m_CPUInfo._L3);
}
//-----------------------------------------------------------------------------

void VDetectProcessor::GetStandardProcessorConfiguration()
{
	vulong eaxreg, ebxreg, ecxreg, edxreg;

	// We check if the CPUID function is available
	if (!CheckCPUIDPresence())
		return;

	// First we check if the processor supports the standard
	// CPUID level 0x00000002
	if (m_CPUInfo.MaxSupportedLevel >= 2)
	{
		// Now we go read the std. CPUID level 0x00000002 the first time
		vulong count, num = 255;
		for (count = 0; count < num; count++)
		{
			__asm
			{
				mov eax, 2
				cpuid
				mov eaxreg, eax
				mov ebxreg, ebx
				mov ecxreg, ecx
				mov edxreg, edx
			}
			// We have to repeat this reading for 'num' times
			num = eaxreg & 0xFF;

			// Then we call the big decode switch function
			DecodeProcessorConfiguration(eaxreg >> 8);
			DecodeProcessorConfiguration(eaxreg >> 16);
			DecodeProcessorConfiguration(eaxreg >> 24);

			// If ebx contains additional data we also decode it
			if ((ebxreg & 0x80000000) == 0)
			{
				DecodeProcessorConfiguration(ebxreg);
				DecodeProcessorConfiguration(ebxreg >> 8);
				DecodeProcessorConfiguration(ebxreg >> 16);
				DecodeProcessorConfiguration(ebxreg >> 24);
			}
			// And also the ecx register
			if ((ecxreg & 0x80000000) == 0)
			{
				DecodeProcessorConfiguration(ecxreg);
				DecodeProcessorConfiguration(ecxreg >> 8);
				DecodeProcessorConfiguration(ecxreg >> 16);
				DecodeProcessorConfiguration(ecxreg >> 24);
			}
			// At last the edx processor register
			if ((edxreg & 0x80000000) == 0)
			{
				DecodeProcessorConfiguration(edxreg);
				DecodeProcessorConfiguration(edxreg >> 8);
				DecodeProcessorConfiguration(edxreg >> 16);
				DecodeProcessorConfiguration(edxreg >> 24);
			}
		}
	}
}
//-----------------------------------------------------------------------------

void VDetectProcessor::GetCPUInfo()
{
	vulong eaxreg, ebxreg, ecxreg, edxreg;
 
	// First of all we check if the CPUID command is available
	if (!CheckCPUIDPresence())
		return;

	// We read the standard CPUID level 0x00000000 which should
	// be available on every x86 processor
	__asm
	{
		mov eax, 0
		cpuid
		mov eaxreg, eax
		mov ebxreg, ebx
		mov edxreg, edx
		mov ecxreg, ecx
	}
	// Then we connect the single register values to the vendor string
	*((vulong *) m_CPUInfo.strVendor) = ebxreg;
	*((vulong *) (m_CPUInfo.strVendor+4)) = edxreg;
	*((vulong *) (m_CPUInfo.strVendor+8)) = ecxreg;

	// We can also read the max. supported standard CPUID level
	m_CPUInfo.MaxSupportedLevel = eaxreg & 0xFFFF;

	// Then we read the ext. CPUID level 0x80000000
	__asm
	{
        mov eax, 0x80000000
		cpuid
		mov eaxreg, eax
	}
	// ...to check the max. supportted extended CPUID level
	m_CPUInfo.MaxSupportedExtendedLevel = eaxreg;

	// Then we switch to the specific processor vendors
	switch (ebxreg)
	{
		case 0x756E6547:	// GenuineIntel
			AnalyzeIntelProcessor();
			break;
		case 0x68747541:	// AuthenticAMD
			AnalyzeAMDProcessor();
			break;
		case 0x69727943:	// CyrixInstead
			// I really do not know anyone owning such a piece of crab
			// So we analyze it as an unknown processor *ggggg*
		default:
			AnalyzeUnknownProcessor();
			break;
	}

}
//-----------------------------------------------------------------------------

void VDetectProcessor::DecodeProcessorConfiguration(vuint cfg)
{
	// First we ensure that there's only one single byte
	cfg &= 0xFF;

	// Then we do a big switch
	switch(cfg)
	{
		case 0:			// cfg = 0:  Unused
			break;
		// cfg = 0x1:  code TLB present, 4 KB pages, 4 ways, 32 entries
		case 0x1: 
			m_CPUInfo._Instruction.bPresent = true;
			strcpy(m_CPUInfo._Instruction.strPageSize, "4 KB");
			m_CPUInfo._Instruction.uiAssociativeWays = 4;
			m_CPUInfo._Instruction.uiEntries = 32;
			break;
		// cfg = 0x2:  code TLB present, 4 MB pages, fully associative, 2 entries
		case 0x2:
			m_CPUInfo._Instruction.bPresent = true;
			strcpy(m_CPUInfo._Instruction.strPageSize, "4 MB");
			m_CPUInfo._Instruction.uiAssociativeWays = 4;
			m_CPUInfo._Instruction.uiEntries = 2;
			break;
		// cfg = 0x3:  data TLB present, 4 KB pages, 4 ways, 64 entries
		case 0x3:
			m_CPUInfo._Data.bPresent = true;
			strcpy(m_CPUInfo._Data.strPageSize, "4 KB");
			m_CPUInfo._Data.uiAssociativeWays = 4;
			m_CPUInfo._Data.uiEntries = 64;
			break;
		// cfg = 0x4:  data TLB present, 4 MB pages, 4 ways, 8 entries
		case 0x4:
			m_CPUInfo._Data.bPresent = true;
			strcpy(m_CPUInfo._Data.strPageSize, "4 MB");
			m_CPUInfo._Data.uiAssociativeWays = 4;
			m_CPUInfo._Data.uiEntries = 8;
			break;
		// cfg = 0x6:  code L1 cache present, 8 KB, 4 ways, 32 byte lines
		case 0x6:
			m_CPUInfo._L1.Instruction.bPresent = true;
			strcpy(m_CPUInfo._L1.Instruction.strSize, "8 KB");
			m_CPUInfo._L1.Instruction.uiAssociativeWays = 4;
			m_CPUInfo._L1.Instruction.uiLineSize = 32;
			break;
		// cfg = 0x8:  code L1 cache present, 16 KB, 4 ways, 32 byte lines
		case 0x8:
			m_CPUInfo._L1.Instruction.bPresent = true;
			strcpy(m_CPUInfo._L1.Instruction.strSize, "16 KB");
			m_CPUInfo._L1.Instruction.uiAssociativeWays = 4;
			m_CPUInfo._L1.Instruction.uiLineSize = 32;
			break;
		// cfg = 0xA:  data L1 cache present, 8 KB, 2 ways, 32 byte lines
		case 0xA:
			m_CPUInfo._L1.Data.bPresent = true;
			strcpy(m_CPUInfo._L1.Data.strSize, "8 KB");
			m_CPUInfo._L1.Data.uiAssociativeWays = 2;
			m_CPUInfo._L1.Data.uiLineSize = 32;
			break;
		// cfg = 0xC:  data L1 cache present, 16 KB, 4 ways, 32 byte lines
		case 0xC:
			m_CPUInfo._L1.Data.bPresent = true;
			strcpy(m_CPUInfo._L1.Data.strSize, "16 KB");
			m_CPUInfo._L1.Data.uiAssociativeWays = 4;
			m_CPUInfo._L1.Data.uiLineSize = 32;
			break;
		// cfg = 0x22:  code and data L3 cache present, 512 KB, 4 ways,
		// 64 byte lines, sectored
		case 0x22:			m_CPUInfo._L3.bPresent = true;
			strcpy(m_CPUInfo._L3.strSize, "512 KB");
			m_CPUInfo._L3.uiAssociativeWays = 4;
			m_CPUInfo._L3.uiLineSize = 64;
			m_CPUInfo._L3.bSectored = true;
			break;
		// cfg = 0x23:  code and data L3 cache present, 1024 KB, 8 ways,
		// 64 byte lines, sectored
		case 0x23:
			m_CPUInfo._L3.bPresent = true;
			strcpy(m_CPUInfo._L3.strSize, "1024 KB");
			m_CPUInfo._L3.uiAssociativeWays = 8;
			m_CPUInfo._L3.uiLineSize = 64;
			m_CPUInfo._L3.bSectored = true;
			break;
		// cfg = 0x25:  code and data L3 cache present, 2048 KB, 8 ways,
		// 64 byte lines, sectored
		case 0x25:
			m_CPUInfo._L3.bPresent = true;
			strcpy(m_CPUInfo._L3.strSize, "2048 KB");
			m_CPUInfo._L3.uiAssociativeWays = 8;
			m_CPUInfo._L3.uiLineSize = 64;
			m_CPUInfo._L3.bSectored = true;
			break;
		// cfg = 0x29:  code and data L3 cache present, 4096 KB, 8 ways,
		// 64 byte lines, sectored
		case 0x29:
			m_CPUInfo._L3.bPresent = true;
			strcpy(m_CPUInfo._L3.strSize, "4096 KB");
			m_CPUInfo._L3.uiAssociativeWays = 8;
			m_CPUInfo._L3.uiLineSize = 64;
			m_CPUInfo._L3.bSectored = true;
			break;
		// cfg = 0x40:  no integrated L2 cache (P6 core) or L3 cache (P4 core)
		case 0x40:
			break;
		// cfg = 0x41:  code and data L2 cache present, 128 KB, 4 ways,
		// 32 byte lines
		case 0x41:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "128 KB");
			m_CPUInfo._L2.uiAssociativeWays = 4;
			m_CPUInfo._L2.uiLineSize = 32;
			break;
		// cfg = 0x42:  code and data L2 cache present, 256 KB, 4 ways,
		// 32 byte lines
		case 0x42:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "256 KB");
			m_CPUInfo._L2.uiAssociativeWays = 4;
			m_CPUInfo._L2.uiLineSize = 32;
			break;
		// cfg = 0x43:  code and data L2 cache present, 512 KB, 4 ways,
		// 32 byte lines
		case 0x43:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "512 KB");
			m_CPUInfo._L2.uiAssociativeWays = 4;
			m_CPUInfo._L2.uiLineSize = 32;
			break;
		// cfg = 0x44:  code and data L2 cache present, 1024 KB, 4 ways,
		// 32 byte lines
		case 0x44:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "1 MB");
			m_CPUInfo._L2.uiAssociativeWays = 4;
			m_CPUInfo._L2.uiLineSize = 32;
			break;
		// cfg = 0x45:  code and data L2 cache present, 2048 KB, 4 ways,
		// 32 byte lines
		case 0x45:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "2 MB");
			m_CPUInfo._L2.uiAssociativeWays = 4;
			m_CPUInfo._L2.uiLineSize = 32;
			break;
		// cfg = 0x50:  code TLB present, 4 KB / 4 MB / 2 MB pages,
		// fully associative, 64 entries
		case 0x50:
			m_CPUInfo._Instruction.bPresent = true;
			strcpy(m_CPUInfo._Instruction.strPageSize, "4 KB / 2 MB / 4 MB");
			m_CPUInfo._Instruction.uiAssociativeWays = (vuint) -1;
			m_CPUInfo._Instruction.uiEntries = 64;
			break;
		// cfg = 0x51:  code TLB present, 4 KB / 4 MB / 2 MB pages,
		// fully associative, 128 entries
		case 0x51:
			m_CPUInfo._Instruction.bPresent = true;
			strcpy(m_CPUInfo._Instruction.strPageSize, "4 KB / 2 MB / 4 MB");
			m_CPUInfo._Instruction.uiAssociativeWays = (vuint) -1;
			m_CPUInfo._Instruction.uiEntries = 128;
			break;
		// cfg = 0x52:  code TLB present, 4 KB / 4 MB / 2 MB pages,
		// fully associative, 256 entries
		case 0x52:
			m_CPUInfo._Instruction.bPresent = true;
			strcpy(m_CPUInfo._Instruction.strPageSize, "4 KB / 2 MB / 4 MB");
			m_CPUInfo._Instruction.uiAssociativeWays = (vuint) -1;
			m_CPUInfo._Instruction.uiEntries = 256;
			break;
		// cfg = 0x5B:  data TLB present, 4 KB / 4 MB pages, fully associative,
		// 64 entries
		case 0x5B:
			m_CPUInfo._Data.bPresent = true;
			strcpy(m_CPUInfo._Data.strPageSize, "4 KB / 4 MB");
			m_CPUInfo._Data.uiAssociativeWays = (vuint) -1;
			m_CPUInfo._Data.uiEntries = 64;
			break;
		// cfg = 0x5C:  data TLB present, 4 KB / 4 MB pages, fully associative,
		// 128 entries
		case 0x5C:
			m_CPUInfo._Data.bPresent = true;
			strcpy(m_CPUInfo._Data.strPageSize, "4 KB / 4 MB");
			m_CPUInfo._Data.uiAssociativeWays = (vuint) -1;
			m_CPUInfo._Data.uiEntries = 128;
			break;
		// cfg = 0x5D:  data TLB present, 4 KB / 4 MB pages, fully associative,
		// 256 entries
		case 0x5d:
			m_CPUInfo._Data.bPresent = true;
			strcpy(m_CPUInfo._Data.strPageSize, "4 KB / 4 MB");
			m_CPUInfo._Data.uiAssociativeWays = (vuint) -1;
			m_CPUInfo._Data.uiEntries = 256;
			break;
		// cfg = 0x66:  data L1 cache present, 8 KB, 4 ways, 64 byte lines,
		// sectored
		case 0x66:
			m_CPUInfo._L1.Data.bPresent = true;
			strcpy(m_CPUInfo._L1.Data.strSize, "8 KB");
			m_CPUInfo._L1.Data.uiAssociativeWays = 4;
			m_CPUInfo._L1.Data.uiLineSize = 64;
			break;
		// cfg = 0x67:  data L1 cache present, 16 KB, 4 ways, 64 byte lines,
		// sectored
		case 0x67:
			m_CPUInfo._L1.Data.bPresent = true;
			strcpy(m_CPUInfo._L1.Data.strSize, "16 KB");
			m_CPUInfo._L1.Data.uiAssociativeWays = 4;
			m_CPUInfo._L1.Data.uiLineSize = 64;
			break;
		// cfg = 0x68:  data L1 cache present, 32 KB, 4 ways, 64 byte lines,
		// sectored
		case 0x68:
			m_CPUInfo._L1.Data.bPresent = true;
			strcpy(m_CPUInfo._L1.Data.strSize, "32 KB");
			m_CPUInfo._L1.Data.uiAssociativeWays = 4;
			m_CPUInfo._L1.Data.uiLineSize = 64;
			break;
		// cfg = 0x70:  trace L1 cache present, 12 KµOPs, 4 ways
		case 0x70:
			m_CPUInfo._Trace.bPresent = true;
			strcpy(m_CPUInfo._Trace.strSize, "12 K-micro-ops");
			m_CPUInfo._Trace.uiAssociativeWays = 4;
			break;
		// cfg = 0x71:  trace L1 cache present, 16 KµOPs, 4 ways
		case 0x71:
			m_CPUInfo._Trace.bPresent = true;
			strcpy(m_CPUInfo._Trace.strSize, "16 K-micro-ops");
			m_CPUInfo._Trace.uiAssociativeWays = 4;
			break;
		// cfg = 0x72:  trace L1 cache present, 32 KµOPs, 4 ways
		case 0x72:
			m_CPUInfo._Trace.bPresent = true;
			strcpy(m_CPUInfo._Trace.strSize, "32 K-micro-ops");
			m_CPUInfo._Trace.uiAssociativeWays = 4;
			break;
		// cfg = 0x79:  code and data L2 cache present, 128 KB, 8 ways,
		// 64 byte lines, sectored
		case 0x79:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "128 KB");
			m_CPUInfo._L2.uiAssociativeWays = 8;
			m_CPUInfo._L2.uiLineSize = 64;
			m_CPUInfo._L2.bSectored = true;
			break;
		// cfg = 0x7A:  code and data L2 cache present, 256 KB, 8 ways,
		// 64 byte lines sectored
		case 0x7A:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "256 KB");
			m_CPUInfo._L2.uiAssociativeWays = 8;
			m_CPUInfo._L2.uiLineSize = 64;
			m_CPUInfo._L2.bSectored = true;
			break;
		// cfg = 0x7B:  code and data L2 cache present, 512 KB, 8 ways,
		// 64 byte lines, sectored
		case 0x7B:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "512 KB");
			m_CPUInfo._L2.uiAssociativeWays = 8;
			m_CPUInfo._L2.uiLineSize = 64;
			m_CPUInfo._L2.bSectored = true;
			break;
		// cfg = 0x7C:  code and data L2 cache present, 1024 KB, 8 ways,
		// 64 byte lines, sectored
		case 0x7C:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "1 MB");
			m_CPUInfo._L2.uiAssociativeWays = 8;
			m_CPUInfo._L2.uiLineSize = 64;
			m_CPUInfo._L2.bSectored = true;
			break;
		// cfg = 0x81:  code and data L2 cache present, 128 KB, 8 ways,
		// 32 byte lines
		case 0x81:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "128 KB");
			m_CPUInfo._L2.uiAssociativeWays = 8;
			m_CPUInfo._L2.uiLineSize = 32;
			break;
		// cfg = 0x82:  code and data L2 cache present, 256 KB, 8 ways,
		// 32 byte lines
		case 0x82:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "256 KB");
			m_CPUInfo._L2.uiAssociativeWays = 8;
			m_CPUInfo._L2.uiLineSize = 32;
			break;
		// cfg = 0x83:  code and data L2 cache present, 512 KB, 8 ways,
		// 32 byte lines
		case 0x83:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "512 KB");
			m_CPUInfo._L2.uiAssociativeWays = 8;
			m_CPUInfo._L2.uiLineSize = 32;
			break;
		// cfg = 0x84:  code and data L2 cache present, 1024 KB, 8 ways,
		// 32 byte lines
		case 0x84:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "1 MB");
			m_CPUInfo._L2.uiAssociativeWays = 8;
			m_CPUInfo._L2.uiLineSize = 32;
			break;
		// cfg = 0x85:  code and data L2 cache present, 2048 KB, 8 ways,
		// 32 byte lines
		case 0x85:
			m_CPUInfo._L2.bPresent = true;
			strcpy(m_CPUInfo._L2.strSize, "2 MB");
			m_CPUInfo._L2.uiAssociativeWays = 8;
			m_CPUInfo._L2.uiLineSize = 32;
			break;
	}
}
//-----------------------------------------------------------------------------

vint64 VDetectProcessor::GetCPUFrequency(vuint uiMeasureMSecs)
{

	// If there are invalid measure time parameters, zero msecs for example,
	// we've to exit the function
	if (uiMeasureMSecs < 1)
	{
		// If theres already a measured frequency available, we return it
        if (m_iFrequency > 0)
			return m_iFrequency;
		else
			return 0;
	}

	// Now we check if the CPUID command is available
	if (!CheckCPUIDPresence())
		return 0;

	// First we get the CPUID standard level 0x00000001
	vulong reg;
	__asm
	{
		mov eax, 1
        cpuid
		mov reg, edx
	}

	// Then we check, if the RDTSC (Real Date Time Stamp Counter) is available.
	// This function is necessary for our measure process.
	if (!(reg & (1 << 4)))
		return 0;

	// After that we declare some vars and check the frequency of the high
	// resolution timer for the measure process.
	// If there's no high-res timer, we exit.
	vuint64 starttime, endtime, timedif, freq, start, end, dif;
	
	if (!QueryPerformanceFrequency((LARGE_INTEGER *) &freq))
		return 0;

	// Now we can init the measure process. We set the process and thread 
	// priority to the highest available level (Realtime priority). Also we 
	// focus the first processor in the multiprocessor system.
	HANDLE hProcess = GetCurrentProcess();
	HANDLE hThread = GetCurrentThread();
	vulong dwCurPriorityClass = GetPriorityClass(hProcess);
	vint iCurThreadPriority = GetThreadPriority(hThread);
	vulong dwProcessMask, dwSystemMask, dwNewMask = 1;
	
	GetProcessAffinityMask(hProcess, &dwProcessMask, &dwSystemMask);

	SetPriorityClass(hProcess, REALTIME_PRIORITY_CLASS);
	SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
	SetProcessAffinityMask(hProcess, dwNewMask);

	// Now we call a CPUID to ensure, that all other prior called functions are
	// completed now (serialization)
	__asm cpuid

	// We ask the high-res timer for the start time
	QueryPerformanceCounter((LARGE_INTEGER *) &starttime);

	// Then we get the current cpu clock and store it
	__asm 
	{
		rdtsc
		mov dword ptr [start+4], edx
		mov dword ptr [start], eax
	}

	// Now we wart for some msecs
	Sleep(uiMeasureMSecs);

	// We ask for the end time
	QueryPerformanceCounter((LARGE_INTEGER *) &endtime);

	// And also for the end cpu clock
	__asm 
	{
		rdtsc
		mov dword ptr [end+4], edx
		mov dword ptr [end], eax
	}

	// Now we can restore the default process and thread priorities
	SetProcessAffinityMask(hProcess, dwProcessMask);
	SetThreadPriority(hThread, iCurThreadPriority);
	SetPriorityClass(hProcess, dwCurPriorityClass);

	// Then we calculate the time and clock differences
	dif = end - start;
	timedif = endtime - starttime;

	// And finally the frequency is the clock difference divided by the time
	// difference. 
	
	//m_iFrequency =(vuint64)(((vfloat64) dif) /(((vfloat64) timedif) / freq));
	m_iFrequency = (vint64) 
	   (((vfloat64)(vlong) dif) / (((vfloat64)(vlong) timedif) / (vlong)freq));

	// At last we just return the frequency that is also stored in the call
	// member var uqwFrequency
	return m_iFrequency;
}
//-----------------------------------------------------------------------------

void VDetectProcessor::TranslateTLB(VProcessorTLB *tlb)
{
	vchar buf[64];

	// We just check if the TLB is present
	if (tlb->bPresent)
        sprintf(tlb->strTLB, "%s page size, %s, %d entries", tlb->strPageSize,
		TranslateAssociativeWays(tlb->uiAssociativeWays, buf), tlb->uiEntries);
	else
        strcpy(tlb->strTLB, "Not present");
}
//-----------------------------------------------------------------------------

void VDetectProcessor::TranslateCache(VProcessorCache *cache)
{
	vchar buf[64];

	// We just check if the cache is present
    if (cache->bPresent)
	{
		// If present we construct the string
		sprintf(cache->strCache, "%s cache size, %s, %d bytes line size",
			cache->strSize, TranslateAssociativeWays(cache->uiAssociativeWays,
			buf), cache->uiLineSize);
		if (cache->bSectored)
			strcat(cache->strCache, ", sectored");
	}
	else
	{
		// Else we just say "Not present"
		strcpy(cache->strCache, "Not present");
	}
}
//-----------------------------------------------------------------------------

vchar* VDetectProcessor::TranslateAssociativeWays(vuint uiWays, vchar *buf)
{
	// We define 0xFFFFFFFF (= -1) as fully associative
    if (uiWays == ((vuint) -1))
		strcpy(buf, "fully associative");
	else
	{
		if (uiWays == 1) // A one way associative cache is just direct mapped
			strcpy(buf, "direct mapped");
		else if (uiWays == 0)		// This should not happen...
			strcpy(buf, "unknown associative ways");
		else						// The x-way associative cache
			sprintf(buf, "%d ways associative", uiWays);
	}
	// To ease the function use we return the buffer
	return buf;
}
//-----------------------------------------------------------------------------

vbool VDetectProcessor::AnalyzeIntelProcessor()
{
	vulong eaxreg, ebxreg, edxreg;

	// First we check if the CPUID command is available
	if (!CheckCPUIDPresence())
		return false;

	// Now we get the CPUID standard level 0x00000001
	__asm
	{
		mov eax, 1
		cpuid
		mov eaxreg, eax
		mov ebxreg, ebx
		mov edxreg, edx
	}
    
	// Then get the cpu model, family, type, stepping and brand id by masking
	// the eax and ebx register
	m_CPUInfo.uiStepping = eaxreg & 0xF;
	m_CPUInfo.uiModel    = (eaxreg >> 4) & 0xF;
	m_CPUInfo.uiFamily   = (eaxreg >> 8) & 0xF;
	m_CPUInfo.uiType     = (eaxreg >> 12) & 0x3;
	m_CPUInfo.uiBrandID  = ebxreg & 0xF;

	// Now we can translate the type number to a more 
	// understandable string format
    switch (m_CPUInfo.uiType)
	{
		case 0:			// Type = 0:  Original OEM processor
			strcpy(m_CPUInfo.strType, "Original OEM");
			strcpy(m_cCPUName, m_CPUInfo.strType);
			strcat(m_cCPUName, " ");
			break;
		case 1:		// Type = 1:  Overdrive processor
			strcpy(m_CPUInfo.strType, "Overdrive");
			strcpy(m_cCPUName, m_CPUInfo.strType);
			strcat(m_cCPUName, " ");
			break;
		case 2:		// Type = 2:  Dual-capable processor
			strcpy(m_CPUInfo.strType, "Dual-capable");
			strcpy(m_cCPUName, m_CPUInfo.strType);
			strcat(m_cCPUName, " ");
			break;
		case 3:		// Type = 3:  Reserved for future use
			strcpy(m_CPUInfo.strType, "Reserved");
			break;
		default:  // This should be never called, cause we just mask 2 bits
			strcpy(m_CPUInfo.strType, "Unknown");
			break;
    }

	// Then we translate the brand id:
	switch (m_CPUInfo.uiBrandID)
	{
		case 0:		// Brand id = 0:  Brand id not supported on this processor
			strcpy(m_CPUInfo.strBrandID, "Not supported");
			break;
		case 1:		// Brand id = 1:  Intel Celeron (0.18 µm) processor
			strcpy(m_CPUInfo.strBrandID, "0.18 µm Intel Celeron");
			break;
		case 2:		// Brand id = 2:  Intel Pentium III (0.18 µm) processor
			strcpy(m_CPUInfo.strBrandID, "0.18 µm Intel Pentium III");
			break;
		case 3:		// Brand id = 3:  Model dependent
			// If the cpu model is Celeron (well, I'm NOT SURE!!!)
			if (m_CPUInfo.uiModel == 6)	
				strcpy(m_CPUInfo.strBrandID, "0.13 µm Intel Celeron");
			else
				strcpy(m_CPUInfo.strBrandID, "0.18 µm Intel Pentium III Xeon");
			break;
		// Brand id = 4:  Intel Pentium III Tualatin (0.13 µm) processor
		case 4:	
			strcpy(m_CPUInfo.strBrandID, "0.13 µm Intel Pentium III");
			break;
		// Brand id = 6:  Intel Pentium III mobile (0.13 µm) processor
		case 6:
			strcpy(m_CPUInfo.strBrandID, "0.13 µm Intel Pentium III mobile");
			break;
		// Brand id = 7:  Intel Celeron mobile (0.13 µm) processor
		case 7:
			strcpy(m_CPUInfo.strBrandID, "0.13 µm Intel Celeron mobile");
			break;
		// Brand id = 8:  Intel Pentium 4 Willamette (0.18 µm) processor
		case 8:
			strcpy(m_CPUInfo.strBrandID, "0.18 µm Intel Pentium 4");
			break;
		// Brand id = 9:  Intel Pentium 4 Northwood (0.13 µm) processor
		case 9:
			strcpy(m_CPUInfo.strBrandID, "0.13 µm Intel Pentium 4");
			break;
		// Brand id = 0xA:  Intel Pentium 4 Northwood (0.13 µm processor) 
		case 0xA:
			strcpy(m_CPUInfo.strBrandID, "0.13 µm Intel Pentium 4");
			break;		// No idea, where the difference to id=9 is
		// Brand id = 0xB:  Intel Pentium 4 Northwood Xeon (0.13 µm processor)
		case 0xB:
			strcpy(m_CPUInfo.strBrandID, "0.13 µm Intel Pentium 4 Xeon");
			break;
		// Brand id = 0xE:  Intel Pentium 4 Willamette Xeon (0.18 µm processor)
		case 0xE:
			strcpy(m_CPUInfo.strBrandID, "0.18 µm Intel Pentium 4 Xeon");
			break;
		// Should be never called, but sure is sure
		default:
			strcpy(m_CPUInfo.strBrandID, "Unknown");
			break;
	}

	// Then we translate the cpu family
    switch (m_CPUInfo.uiFamily)
	{
		case 3:			// Family = 3:  i386 (80386) processor family
			strcpy(m_CPUInfo.strFamily, "Intel i386");
			break;
		case 4:			// Family = 4:  i486 (80486) processor family
			strcpy(m_CPUInfo.strFamily, "Intel i486");
			break;
		case 5:			// Family = 5:  Pentium (80586) processor family
			strcpy(m_CPUInfo.strFamily, "Intel Pentium");
			break;
		case 6:			// Family = 6:  Pentium Pro (80686) processor family
			strcpy(m_CPUInfo.strFamily, "Intel Pentium Pro");
			break;
		case 15:		// Family = 15:  Extended family specific
			// Masking the extended family
			m_CPUInfo.uiExtendedFamily = (eaxreg >> 20) & 0xFF;
			switch (m_CPUInfo.uiExtendedFamily)
			{
				// Family = 15, Ext. Family = 0:  Pentium 4 (80786 ??)
				// processor family
				case 0:
					strcpy(m_CPUInfo.strFamily, "Intel Pentium 4");
					break;
				// Family = 15, Ext. Family = 1:  McKinley (64-bit) 
				// processor family
				case 1:
					strcpy(m_CPUInfo.strFamily, "Intel McKinley (IA-64)");
					break;
				// Sure is sure
				default:
					strcpy(m_CPUInfo.strFamily, "Unknown Intel Pentium 4+");
					break;
			}
			break;
		// Failsave
		default:
			strcpy(m_CPUInfo.strFamily, "Unknown");
			break;
    }

	// Now we come to the big deal, the exact model name
	switch (m_CPUInfo.uiFamily)
	{
		case 3:			// i386 (80386) processor family
			strcpy(m_CPUInfo.strModel, "Unknown Intel i386");
			strcat(m_cCPUName, "Intel i386");
			break;
		case 4:			// i486 (80486) processor family
			switch (m_CPUInfo.uiModel)
			{
				case 0:			// Model = 0:  i486 DX-25/33 processor model
					strcpy(m_CPUInfo.strModel, "Intel i486 DX-25/33");
					strcat(m_cCPUName, "Intel i486 DX-25/33");
					break;
				case 1:			// Model = 1:  i486 DX-50 processor model
					strcpy(m_CPUInfo.strModel, "Intel i486 DX-50");
					strcat(m_cCPUName, "Intel i486 DX-50");
					break;
				case 2:			// Model = 2:  i486 SX processor model
					strcpy(m_CPUInfo.strModel, "Intel i486 SX");
					strcat(m_cCPUName, "Intel i486 SX");
					break;
				// Model = 3:  i486 DX2 (with i487 numeric coprocessor)
				// processor model
				case 3:
					strcpy(m_CPUInfo.strModel, "Intel i486 487/DX2");
					strcat(m_cCPUName,
						"Intel i486 DX2 with i487 numeric coprocessor");
					break;
				// Model = 4:  i486 SL processor model (never heard ?!?)
				case 4:
					strcpy(m_CPUInfo.strModel, "Intel i486 SL");
					strcat(m_cCPUName, "Intel i486 SL");
					break;
				case 5:			// Model = 5:  i486 SX2 processor model
					strcpy(m_CPUInfo.strModel, "Intel i486 SX2");
					strcat(m_cCPUName, "Intel i486 SX2");
					break;
				// Model = 7:  i486 write-back enhanced DX2 processor model
				case 7:
					strcpy(m_CPUInfo.strModel,
						"Intel i486 write-back enhanced DX2");
					strcat(m_cCPUName, "Intel i486 write-back enhanced DX2");
					break;
				case 8:			// Model = 8:  i486 DX4 processor model
					strcpy(m_CPUInfo.strModel, "Intel i486 DX4");
					strcat(m_cCPUName, "Intel i486 DX4");
					break;
				// Model = 9:  i486 write-back enhanced DX4 processor model
				case 9:
					strcpy(m_CPUInfo.strModel,
						"Intel i486 write-back enhanced DX4");
					strcat(m_cCPUName, "Intel i486 DX4");
					break;
				default:		// ...
					strcpy(m_CPUInfo.strModel, "Unknown Intel i486");
					strcat(m_cCPUName, "Intel i486 (Unknown model)");
					break;
			}
			break;
		case 5:			// Pentium (80586) processor family
			switch (m_CPUInfo.uiModel)
			{
				case 0:		// Model = 0:  Pentium (P5 A-Step) processor model
					strcpy(m_CPUInfo.strModel, "Intel Pentium (P5 A-Step)");
					strcat(m_cCPUName, "Intel Pentium (P5 A-Step core)");
					break;		// Famous for the DIV bug, as far as I know
				case 1:			// Model = 1:  Pentium 60/66 processor model
					strcpy(m_CPUInfo.strModel, "Intel Pentium 60/66 (P5)");
					strcat(m_cCPUName, "Intel Pentium 60/66 (P5 core)");
					break;
				case 2:	 // Model = 2:  Pentium 75-200 (P54C) processor model
					strcpy(m_CPUInfo.strModel, "Intel Pentium 75-200 (P54C)");
					strcat(m_cCPUName, "Intel Pentium 75-200 (P54C core)");
					break;
				case 3:	 // Model = 3:  Pentium overdrive for 486 systems
					     //processor model
					strcpy(m_CPUInfo.strModel,
						"Intel Pentium for 486 system (P24T Overdrive)");
					strcat(m_cCPUName,
						"Intel Pentium for 486 (P24T overdrive core)");
					break;
				case 4:			// Model = 4:  Pentium MMX processor model
					strcpy(m_CPUInfo.strModel, "Intel Pentium MMX (P55C)");
					strcat(m_cCPUName, "Intel Pentium MMX (P55C core)");
					break;
				case 7:	  // Model = 7:  Pentium processor model
					strcpy(m_CPUInfo.strModel, "Intel Pentium (P54C)");
					strcat(m_cCPUName, "Intel Pentium (P54C core)");
					break;
				case 8:	// Model = 8:  Pentium MMX (0.25 µm) processor model
					strcpy(m_CPUInfo.strModel,
						"Intel Pentium MMX (P55C), 0.25 µm");
					strcat(m_cCPUName,
						"Intel Pentium MMX (P55C core), 0.25 µm");
					break;
				default:		// ...
					strcpy(m_CPUInfo.strModel, "Unknown Intel Pentium");
					strcat(m_cCPUName, "Intel Pentium (Unknown P5-model)");
					break;
			}
			break;
		case 6:			// Pentium Pro (80686) processor family
			switch (m_CPUInfo.uiModel)
			{
				case 0:	// Model = 0:  Pentium Pro (P6 A-Step) processor model
					strcpy(m_CPUInfo.strModel,
						"Intel Pentium Pro (P6 A-Step)");
					strcat(m_cCPUName, "Intel Pentium Pro (P6 A-Step core)");
					break;
				case 1:			// Model = 1:  Pentium Pro
					strcpy(m_CPUInfo.strModel, "Intel Pentium Pro (P6)");
					strcat(m_cCPUName, "Intel Pentium Pro (P6 core)");
					break;
				case 3:	// Model = 3:  Pentium II (66 MHz FSB, I think)
					// processor model
					strcpy(m_CPUInfo.strModel,
						"Intel Pentium II Model 3, 0.28 µm");
					strcat(m_cCPUName,
						"Intel Pentium II (Model 3 core, 0.28 µm process)");
					break;
				case 5:	// Model = 5:  Pentium II/Xeon/Celeron (0.25 µm)
						// processor model
					strcpy(m_CPUInfo.strModel,
						"Intel Pentium II Model 5/Xeon/Celeron, 0.25 µm");
					strcat(m_cCPUName,
						"Intel Pentium II/Xeon/Celeron (Model 5 core, 0.25 µm process)");
					break;
				case 6:		// Model = 6:  Pentium II with internal L2 cache
					strcpy(m_CPUInfo.strModel,
						"Intel Pentium II - internal L2 cache");
					strcat(m_cCPUName,
						"Intel Pentium II with internal L2 cache");
					break;
				case 7:	// Model = 7:  Pentium III/Xeon (extern L2 cache
					strcpy(m_CPUInfo.strModel,
					 "Intel Pentium III/Pentium III Xeon - external L2 cache, 0.25 µm");
					strcat(m_cCPUName,
					 "Intel Pentium III/Pentium III Xeon (0.25 µm process) with external L2 cache");
					break;
				case 8:	// Model = 8:  Pentium III/Xeon/Celeron 
						// (256 KB on-die L2 cache) processor model
					strcpy(m_CPUInfo.strModel,
					 "Intel Pentium III/Celeron/Pentium III Xeon - internal L2 cache, 0.18 µm");
					// We want to know it exactly:
					switch (m_CPUInfo.uiBrandID)
					{
						case 1:	// Model = 8, Brand id = 1:
								// Celeron (on-die L2 cache) processor model
							strcat(m_cCPUName,
								"Intel Celeron (0.18 µm process) with internal L2 cache");
							break;
                        case 2:	// Model = 8, Brand id = 2:
								//Pentium III (on-die L2 cache) processor model
							strcat(m_cCPUName,
							 "Intel Pentium III (0.18 µm process) with internal L2 cache");
							break;
						case 3:	// Model = 8, Brand id = 3:  Pentium III Xeon
								//(on-die L2 cache) processor model
                            strcat(m_cCPUName,
							 "Intel Pentium III Xeon (0.18 µm process) with internal L2 cache");
							break;
						default:		// ...²
							strcat(m_cCPUName,
							 "Intel Pentium III core (unknown model, 0.18 µm process) with internal L2 cache");
							break;
					}
					break;
				case 0xA: // Model = 0xA:  Pentium III/Xeon/Celeron
						  //(1 or 2 MB on-die L2 cache) processor model
					strcpy(m_CPUInfo.strModel,
					 "Intel Pentium III/Celeron/Pentium III Xeon - internal L2 cache, 0.18 µm");
					// Exact detection:
					switch (m_CPUInfo.uiBrandID)
					{
						case 1:	// Model = 0xA, Brand id = 1:
								// Celeron (1 or 2 MB on-die L2 cache 
							strcat(m_cCPUName,
							 "Intel Celeron (0.18 µm process) with internal L2 cache");
							break;
                        case 2: // Model = 0xA, Brand id = 2:  Pentium III
								//(1 or 2 MB on-die L2 cache (never seen...))
							strcat(m_cCPUName,
							 "Intel Pentium III (0.18 µm process) with internal L2 cache");
							break;
						case 3:	// Model = 0xA, Brand id = 3:
								// Pentium III Xeon (1 or 2 MB on-die L2 cache)
                            strcat(m_cCPUName,
							 "Intel Pentium III Xeon (0.18 µm process) with internal L2 cache");
							break;
						default:
							strcat(m_cCPUName,
							 "Intel Pentium III core (unknown model, 0.18 µm process) with internal L2 cache");
							break;
					}
					break;
				case 0xB: // Model = 0xB: Pentium III/Xeon/Celeron
						  // (Tualatin core, on-die cache) processor model
					strcpy(m_CPUInfo.strModel,
					 "Intel Pentium III/Celeron/Pentium III Xeon - internal L2 cache, 0.13 µm");
					switch (m_CPUInfo.uiBrandID)
					{
						case 3:	// Model = 0xB, Brand id = 3:
								// Celeron (Tualatin core) processor model
							strcat(m_cCPUName,
							 "Intel Celeron (Tualatin core, 0.13 µm process) with internal L2 cache");
							break;
                        case 4: // Model = 0xB, Brand id = 4:
								// Pentium III (Tualatin core) processor model
							strcat(m_cCPUName,
								"Intel Pentium III (Tualatin core, 0.13 µm process) with internal L2 cache");
							break;
						case 7:	// Model = 0xB, Brand id = 7:
								// Celeron mobile (Tualatin core) processor model
                            strcat(m_cCPUName,
								"Intel Celeron mobile (Tualatin core, 0.13 µm process) with internal L2 cache");
							break;
						default:
							strcat(m_cCPUName,
								"Intel Pentium III Tualatin core (unknown model, 0.13 µm process) with internal L2 cache");
							break;
					}
					break;
				default:
					strcpy(m_CPUInfo.strModel, "Unknown Intel Pentium Pro");
					strcat(m_cCPUName, "Intel Pentium Pro (Unknown model)");
					break;
			}
			break;
		case 15:		// Extended processor family
			// Masking the extended model
			m_CPUInfo.uiExtendedModel = (eaxreg >> 16) & 0xFF;
			switch (m_CPUInfo.uiModel)
			{
				case 0:		// Model = 0:  Pentium 4 Willamette (A-Step) core
					if ((m_CPUInfo.uiBrandID) == 8)	//Brand id=8: P4 Willamette
					{
						strcpy(m_CPUInfo.strModel,
							"Intel Pentium 4 Willamette (A-Step)");
						strcat(m_cCPUName,
							"Intel Pentium 4 Willamette (A-Step)");
					}
					else							// else Xeon
					{
						strcpy(m_CPUInfo.strModel,
							"Intel Pentium 4 Willamette Xeon (A-Step)");
						strcat(m_cCPUName,
							"Intel Pentium 4 Willamette Xeon (A-Step)");
					}
					break;
				case 1:			// Model = 1:  Pentium 4 Willamette core
					if ((m_CPUInfo.uiBrandID) == 8)	//Brand id=8: P4 Willamette
					{
						strcpy(m_CPUInfo.strModel,
							"Intel Pentium 4 Willamette");
						strcat(m_cCPUName, "Intel Pentium 4 Willamette");
					}
					else		// else Xeon
					{
						strcpy(m_CPUInfo.strModel,
							"Intel Pentium 4 Willamette Xeon");
						strcat(m_cCPUName, "Intel Pentium 4 Willamette Xeon");
					}
					break;
				case 2:		// Model = 2:  Pentium 4 Northwood core
					if (((m_CPUInfo.uiBrandID) == 9) ||
						((m_CPUInfo.uiBrandID) == 0xA))	// P4 Willamette
					{
						strcpy(m_CPUInfo.strModel, "Intel Pentium 4 Northwood");
						strcat(m_cCPUName, "Intel Pentium 4 Northwood");
					}
					else	// Xeon
					{
						strcpy(m_CPUInfo.strModel,
							"Intel Pentium 4 Northwood Xeon");
						strcat(m_cCPUName, "Intel Pentium 4 Northwood Xeon");
					}
					break;
				default:		// Silly stupid never used failsave option
					strcpy(m_CPUInfo.strModel, "Unknown Intel Pentium 4");
					strcat(m_cCPUName, "Intel Pentium 4 (Unknown model)");
					break;
			}
			break;
		default:
			strcpy(m_CPUInfo.strModel, "Unknown Intel model");
			strcat(m_cCPUName, "Intel (Unknown model)");
			break;
    }

	// After the long processor model block we come to the processors serial
	// number.
	// First of all we check if the processor supports the serial number
	if (m_CPUInfo.MaxSupportedLevel >= 3)
	{
		//If it supports the serial number CPUID level 0x00000003 read the data
		vulong sig1, sig2, sig3;
		__asm
		{
			mov eax, 1
			cpuid
			mov sig1, eax
			mov eax, 3
			cpuid
			mov sig2, ecx
			mov sig3, edx
		}
		// Then we convert the data to an readable string
		sprintf(m_CPUInfo.strProcessorSerial,
			"%04lX-%04lX-%04lX-%04lX-%04lX-%04lX",
			sig1 >> 16, sig1 & 0xFFFF, sig3 >> 16,
			sig3 & 0xFFFF, sig2 >> 16, sig2 & 0xFFFF);
	}
	else
	{
		//If there's no serial number support just mark put "No serial number"
		strcpy(m_CPUInfo.strProcessorSerial, "No Processor Serial Number");
	}

	// Now we get the standard processor extensions
	GetStandardProcessorExtensions();

	// And finally the processor configuration (caches, TLBs, ..) and translate
	// the data to readable strings
	GetStandardProcessorConfiguration();
	TranslateProcessorConfiguration();

	// At last...
	return true;
}
//-----------------------------------------------------------------------------

vbool VDetectProcessor::AnalyzeAMDProcessor()
{
	vulong eaxreg, ebxreg, ecxreg, edxreg;

	// First of all we check if the CPUID command is available
	if (!CheckCPUIDPresence())
		return false;

	// Now we get the CPUID standard level 0x00000001
	__asm
	{
		mov eax, 1
		cpuid
		mov eaxreg, eax
		mov ebxreg, ebx
		mov edxreg, edx
	}
    
	// Then we mask the model, family, stepping and type 
	// (AMD does not support brand id)
	m_CPUInfo.uiStepping = eaxreg & 0xF;
	m_CPUInfo.uiModel    = (eaxreg >> 4) & 0xF;
	m_CPUInfo.uiFamily   = (eaxreg >> 8) & 0xF;
	m_CPUInfo.uiType     = (eaxreg >> 12) & 0x3;

	// After that, we translate the processor type
    switch (m_CPUInfo.uiType)
	{
		case 0:
			strcpy(m_CPUInfo.strType, "Original OEM");
			strcpy(m_cCPUName, m_CPUInfo.strType);
			strcat(m_cCPUName, " ");
			break;
		case 1:
			strcpy(m_CPUInfo.strType, "Overdrive");
			strcpy(m_cCPUName, m_CPUInfo.strType);
			strcat(m_cCPUName, " ");
			break;
		case 2:
			strcpy(m_CPUInfo.strType, "Dual-capable");
			strcpy(m_cCPUName, m_CPUInfo.strType);
			strcat(m_cCPUName, " ");
			break;
		case 3:
			strcpy(m_CPUInfo.strType, "Reserved");
			break;
		default:
			strcpy(m_CPUInfo.strType, "Unknown");
			break;
    }

	// Now we check if the processor supports the brand id string extended
	// CPUID level
	if (m_CPUInfo.MaxSupportedExtendedLevel >= 0x80000004)
	{
		// If it supports the extended CPUID level 0x80000004 we read the data
		char tmp[52];
		memset(tmp, 0, sizeof(tmp));
        __asm
		{
			mov eax, 0x80000002
			cpuid
			mov dword ptr [tmp], eax
			mov dword ptr [tmp+4], ebx
			mov dword ptr [tmp+8], ecx
			mov dword ptr [tmp+12], edx
			mov eax, 0x80000003
			cpuid
			mov dword ptr [tmp+16], eax
			mov dword ptr [tmp+20], ebx
			mov dword ptr [tmp+24], ecx
			mov dword ptr [tmp+28], edx
			mov eax, 0x80000004
			cpuid
			mov dword ptr [tmp+32], eax
			mov dword ptr [tmp+36], ebx
			mov dword ptr [tmp+40], ecx
			mov dword ptr [tmp+44], edx
		}
		// And copy it to the brand id string
		strcpy(m_CPUInfo.strBrandID, tmp);
	}
	else
	{
		// Or just tell there is no brand id string support
		strcpy(m_CPUInfo.strBrandID, "Not supported");
	}

	// After that we translate the processor family
    switch(m_CPUInfo.uiFamily)
	{
		case 4:	// Family = 4:  486 (80486) or 5x86 (80486) processor family
			switch (m_CPUInfo.uiModel)
			{
				case 3:			// Thanks to AMD for this nice form of family
				case 7:			// detection.... *grmpf*
				case 8:
				case 9:
					strcpy(m_CPUInfo.strFamily, "AMD 80486");
					break;
				case 0xE:
				case 0xF:
					strcpy(m_CPUInfo.strFamily, "AMD 5x86");
					break;
				default:
					strcpy(m_CPUInfo.strFamily, "Unknown family");
					break;
			}
			break;
		case 5:			// Family = 5:  K5 or K6 processor family
			switch (m_CPUInfo.uiModel)
			{
				case 0:
				case 1:
				case 2:
				case 3:
					strcpy(m_CPUInfo.strFamily, "AMD K5");
					break;
				case 6:
				case 7:
				case 8:
				case 9:
					strcpy(m_CPUInfo.strFamily, "AMD K6");
					break;
				default:
					strcpy(m_CPUInfo.strFamily, "Unknown family");
					break;
			}
			break;
		case 6:			// Family = 6:  K7 (Athlon, ...) processor family
			strcpy(m_CPUInfo.strFamily, "AMD K7");
			break;
		default:		// For security
			strcpy(m_CPUInfo.strFamily, "Unknown family");
			break;
	}

	// After the family detection we come to the specific processor model
	// detection
	switch (m_CPUInfo.uiFamily)
	{
		case 4:	// Family = 4:  486 (80486) or 5x85 (80486) processor family
			switch (m_CPUInfo.uiModel)
			{
				case 3:			// Model = 3:  80486 DX2
					strcpy(m_CPUInfo.strModel, "AMD 80486 DX2");
					strcat(m_cCPUName, "AMD 80486 DX2");
					break;
				case 7:			// Model = 7:  80486 write-back enhanced DX2
					strcpy(m_CPUInfo.strModel,
						"AMD 80486 write-back enhanced DX2");
					strcat(m_cCPUName, "AMD 80486 write-back enhanced DX2");
					break;
				case 8:			// Model = 8:  80486 DX4
					strcpy(m_CPUInfo.strModel, "AMD 80486 DX4");
					strcat(m_cCPUName, "AMD 80486 DX4");
					break;
				case 9:			// Model = 9:  80486 write-back enhanced DX4
					strcpy(m_CPUInfo.strModel,
						"AMD 80486 write-back enhanced DX4");
					strcat(m_cCPUName, "AMD 80486 write-back enhanced DX4");
					break;
				case 0xE:		// Model = 0xE:  5x86
					strcpy(m_CPUInfo.strModel, "AMD 5x86");
					strcat(m_cCPUName, "AMD 5x86");
					break;
				case 0xF:		// Model = 0xF:  5x86 write-back enhanced
					strcpy(m_CPUInfo.strModel, "AMD 5x86 write-back enhanced");
					strcat(m_cCPUName, "AMD 5x86 write-back enhanced");
					break;
				default:		// ...
					strcpy(m_CPUInfo.strModel,
						"Unknown AMD 80486 or 5x86 model");
					strcat(m_cCPUName, "AMD 80486 or 5x86 (Unknown model)");
					break;
			}
			break;
		case 5:			// Family = 5:  K5 / K6 processor family
			switch (m_CPUInfo.uiModel)
			{
				case 0:	// Model = 0:  K5 SSA 5 (Pentium Rating 75, 90 and 100)
					strcpy(m_CPUInfo.strModel,
						"AMD K5 SSA5 (PR75, PR90, PR100)");
					strcat(m_cCPUName,
						"AMD K5 SSA5 (PR75, PR90, PR100)");
					break;
				case 1:			// Model = 1:  K5 5k86 (PR 120 and 133 MHz)
					strcpy(m_CPUInfo.strModel, "AMD K5 5k86 (PR120, PR133)");
					strcat(m_cCPUName, "AMD K5 5k86 (PR120, PR133)");
					break;
				case 2:			// Model = 2:  K5 5k86 (PR 166 MHz)
					strcpy(m_CPUInfo.strModel, "AMD K5 5k86 (PR166)");
					strcat(m_cCPUName, "AMD K5 5k86 (PR166)");
					break;
				case 3:			// Model = 3:  K5 5k86 (PR 200 MHz)
					strcpy(m_CPUInfo.strModel, "AMD K5 5k86 (PR200)");
					strcat(m_cCPUName, "AMD K5 5k86 (PR200)");
					break;
				case 6:			// Model = 6:  K6
					strcpy(m_CPUInfo.strModel, "AMD K6 (0.30 µm)");
					strcat(m_cCPUName, "AMD K6 (0.30 µm)");
					break;
				case 7:			// Model = 7:  K6 (0.25 µm)
					strcpy(m_CPUInfo.strModel, "AMD K6 (0.25 µm)");
					strcat(m_cCPUName, "AMD K6 (0.25 µm)");
					break;
				case 8:			// Model = 8:  K6-2
					strcpy(m_CPUInfo.strModel, "AMD K6-2");
					strcat(m_cCPUName, "AMD K6-2");
					break;
				case 9:			// Model = 9:  K6-III
					strcpy(m_CPUInfo.strModel, "AMD K6-III");
					strcat(m_cCPUName, "AMD K6-III");
					break;
				case 0xD:		// Model = 0xD:  K6-2+ / K6-III+
					strcpy(m_CPUInfo.strModel,
						"AMD K6-2+ or K6-III+ (0.18 µm)");
					strcat(m_cCPUName, "AMD K6-2+ or K6-III+ (0.18 µm)");
					break;
				default:		// ...
					strcpy(m_CPUInfo.strModel, "Unknown AMD K5 or K6 model");
					strcat(m_cCPUName, "AMD K5 or K6 (Unknown model)");
					break;
			}
			break;
		case 6:			// Family = 6:  K7 processor family
			switch (m_CPUInfo.uiModel)
			{
				case 1:			// Athlon
					strcpy(m_CPUInfo.strModel, "AMD Athlon (0.25 µm)");
					strcat(m_cCPUName, "AMD Athlon (0.25 µm)");
					break;
				case 2:			// Athlon (0.18 µm)
					strcpy(m_CPUInfo.strModel, "AMD Athlon (0.18 µm)");
					strcat(m_cCPUName, "AMD Athlon (0.18 µm)");
					break;
				case 3:			// Duron (Spitfire core)
					strcpy(m_CPUInfo.strModel, "AMD Duron (Spitfire)");
					strcat(m_cCPUName, "AMD Duron (Spitfire core)");
					break;
				case 4:			// Athlon (Thunderbird core)
					strcpy(m_CPUInfo.strModel, "AMD Athlon (Thunderbird)");
					strcat(m_cCPUName, "AMD Athlon (Thunderbird core)");
					break;
				case 6:			// Athlon MP / Mobile Athlon (Palomino core)
					strcpy(m_CPUInfo.strModel,
						"AMD Athlon MP/Mobile Athlon (Palomino)");
					strcat(m_cCPUName,
						"AMD Athlon MP/Mobile Athlon (Palomino core)");
					break;
				case 7:			// Mobile Duron (Morgan core)
					strcpy(m_CPUInfo.strModel, "AMD Mobile Duron (Morgan)");
					strcat(m_cCPUName, "AMD Mobile Duron (Morgan core)");
					break;
				default:		// ...
					strcpy(m_CPUInfo.strModel, "Unknown AMD K7 model");
					strcat(m_cCPUName, "AMD K7 (Unknown model)");
					break;
			}
			break;
		default:		// ...
			strcpy(m_CPUInfo.strModel, "Unknown AMD model");
			strcat(m_cCPUName, "AMD (Unknown model)");
			break;
    }

	// Now we read the standard processor extension that are stored in the same
	// way the Intel standard extensions are
	GetStandardProcessorExtensions();

	// Then we check if theres an extended CPUID level support
	if (m_CPUInfo.MaxSupportedExtendedLevel >= 0x80000001)
	{
		// If we can access the extended CPUID level 0x80000001 we get the
		// edx register
		__asm
		{
			mov eax, 0x80000001
			cpuid
			mov edxreg, edx
		}

		// Now we can mask some AMD specific cpu extensions
		m_CPUInfo._Ext.EMMX_MultimediaExtensions		= CheckBit(edxreg, 22);
		m_CPUInfo._Ext.AA64_AMD64BitArchitecture		= CheckBit(edxreg, 29);
		m_CPUInfo._Ext._E3DNOW_InstructionExtensions	= CheckBit(edxreg, 30);
		m_CPUInfo._Ext._3DNOW_InstructionExtensions		= CheckBit(edxreg, 31);
	}

	// After that we check if the processor supports the ext. CPUID level
	// 0x80000006
	if (m_CPUInfo.MaxSupportedExtendedLevel >= 0x80000006)
	{
		// If it's present, we read it out
        __asm
		{
            mov eax, 0x80000005
			cpuid
			mov eaxreg, eax
			mov ebxreg, ebx
			mov ecxreg, ecx
			mov edxreg, edx
		}

		// Then we mask the L1 Data TLB information
		if ((ebxreg >> 16) && (eaxreg >> 16))
		{
			m_CPUInfo._Data.bPresent = true;
			strcpy(m_CPUInfo._Data.strPageSize, "4 KB / 2 MB / 4MB");
			m_CPUInfo._Data.uiAssociativeWays = (eaxreg >> 24) & 0xFF;
			m_CPUInfo._Data.uiEntries = (eaxreg >> 16) & 0xFF;
		}
		else if (eaxreg >> 16)
		{
			m_CPUInfo._Data.bPresent = true;
			strcpy(m_CPUInfo._Data.strPageSize, "2 MB / 4MB");
			m_CPUInfo._Data.uiAssociativeWays = (eaxreg >> 24) & 0xFF;
			m_CPUInfo._Data.uiEntries = (eaxreg >> 16) & 0xFF;
		}
		else if (ebxreg >> 16)
		{
			m_CPUInfo._Data.bPresent = true;
			strcpy(m_CPUInfo._Data.strPageSize, "4 KB");
			m_CPUInfo._Data.uiAssociativeWays = (ebxreg >> 24) & 0xFF;
			m_CPUInfo._Data.uiEntries = (ebxreg >> 16) & 0xFF;
		}
		if (m_CPUInfo._Data.uiAssociativeWays == 0xFF)
			m_CPUInfo._Data.uiAssociativeWays = (vuint) -1;

		// Now the L1 Instruction/Code TLB information
		if ((ebxreg & 0xFFFF) && (eaxreg & 0xFFFF))
		{
			m_CPUInfo._Instruction.bPresent = true;
			strcpy(m_CPUInfo._Instruction.strPageSize, "4 KB / 2 MB / 4MB");
			m_CPUInfo._Instruction.uiAssociativeWays = (eaxreg >> 8) & 0xFF;
			m_CPUInfo._Instruction.uiEntries = eaxreg & 0xFF;
		}
		else if (eaxreg & 0xFFFF)
		{
			m_CPUInfo._Instruction.bPresent = true;
			strcpy(m_CPUInfo._Instruction.strPageSize, "2 MB / 4MB");
			m_CPUInfo._Instruction.uiAssociativeWays = (eaxreg >> 8) & 0xFF;
			m_CPUInfo._Instruction.uiEntries = eaxreg & 0xFF;
		}
		else if (ebxreg & 0xFFFF)
		{
			m_CPUInfo._Instruction.bPresent = true;
			strcpy(m_CPUInfo._Instruction.strPageSize, "4 KB");
			m_CPUInfo._Instruction.uiAssociativeWays = (ebxreg >> 8) & 0xFF;
			m_CPUInfo._Instruction.uiEntries = ebxreg & 0xFF;
		}
		if (m_CPUInfo._Instruction.uiAssociativeWays == 0xFF)
			m_CPUInfo._Instruction.uiAssociativeWays = (vuint) -1;
		
		// Then we read the L1 data cache information
		if ((ecxreg >> 24) > 0)
		{
			m_CPUInfo._L1.Data.bPresent = true;
			sprintf(m_CPUInfo._L1.Data.strSize, "%d KB", ecxreg >> 24);
			m_CPUInfo._L1.Data.uiAssociativeWays = (ecxreg >> 15) & 0xFF;
			m_CPUInfo._L1.Data.uiLineSize = ecxreg & 0xFF;
		}
		// After that we read the L2 instruction/code cache information
		if ((edxreg >> 24) > 0)
		{
			m_CPUInfo._L1.Instruction.bPresent = true;
			sprintf(m_CPUInfo._L1.Instruction.strSize, "%d KB", edxreg >> 24);
			m_CPUInfo._L1.Instruction.uiAssociativeWays =(edxreg >> 15) & 0xFF;
			m_CPUInfo._L1.Instruction.uiLineSize = edxreg & 0xFF;
		}

		// Note: I'm not absolutely sure that the L1 page size code (the
		// 'if/else if/else if' structs above) really detects the real page
		// size for the TLB. Somebody should check it....

		// Now we read the ext. CPUID level 0x80000006
        __asm
		{
			mov eax, 0x80000006
			cpuid
			mov eaxreg, eax
			mov ebxreg, ebx
			mov ecxreg, ecx
		}

		// We only mask the unified L2 cache masks (never heard of an
		// L2 cache that is divided in data and code parts)
		if (((ecxreg >> 12) & 0xF) > 0)
		{
			m_CPUInfo._L2.bPresent = true;
			sprintf(m_CPUInfo._L2.strSize, "%d KB", ecxreg >> 16);
			switch ((ecxreg >> 12) & 0xF)
			{
				case 1:
					m_CPUInfo._L2.uiAssociativeWays = 1;
					break;
				case 2:
					m_CPUInfo._L2.uiAssociativeWays = 2;
					break;
				case 4:
					m_CPUInfo._L2.uiAssociativeWays = 4;
					break;
				case 6:
					m_CPUInfo._L2.uiAssociativeWays = 8;
					break;
				case 8:
					m_CPUInfo._L2.uiAssociativeWays = 16;
					break;
				case 0xF:
					m_CPUInfo._L2.uiAssociativeWays = (vuint) -1;
					break;
				default:
					m_CPUInfo._L2.uiAssociativeWays = 0;
					break;
			}
			m_CPUInfo._L2.uiLineSize = ecxreg & 0xFF;
		}
	}
	else
	{
		// If we could not detect the ext. CPUID level 0x80000006 we
		// try to read the standard processor configuration.
		GetStandardProcessorConfiguration();
	}
	// After reading we translate the configuration to strings
	TranslateProcessorConfiguration();

	// And finally exit
	return true;
}

//-----------------------------------------------------------------------------
} // namespace util
} // namespace v3d
//-----------------------------------------------------------------------------

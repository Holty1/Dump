#include "stdafx.h"
#include "PatternScan.h"


 DWORD PatternScan::FindPattern(const char* pPattern)
{
	HMODULE handle = GetModuleHandle(NULL);
			PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER(handle);
			PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS((LONG)handle + pDsHeader->e_lfanew);
			PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pPeHeader->OptionalHeader;
			DWORD base = (ULONG)handle + pOptionalHeader->BaseOfCode;
			DWORD size = pOptionalHeader->SizeOfCode;
		
			unsigned int count = 0;
			return	PatternScan::Search(base, size, (unsigned char*)pPattern, count);
}
 MODULEINFO GetMainModuleInfo()
 {
	 MODULEINFO modinfo = { 0 };
	 HMODULE hModule = GetModuleHandle(NULL);
	 if (hModule == 0) return modinfo;
	 GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	 return modinfo;
 }
 DWORD GetModuleSize(DWORD processID, char* module)
 {

	 HANDLE hSnap;
	 MODULEENTRY32 xModule;
	 hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processID);
	 xModule.dwSize = sizeof(MODULEENTRY32);
	 if (Module32First(hSnap, &xModule)) {
		 while (Module32Next(hSnap, &xModule)) {
			 if (!strncmp((char*)xModule.szModule, module, 8)) {
				 CloseHandle(hSnap);
				 return (DWORD)xModule.modBaseSize;
			 }
		 }
	 }
	 CloseHandle(hSnap);
	 return 0;
 }
 DWORD PatternScan::FindPattern2(const char* pPattern)
 {
	 HMODULE handle = (HMODULE)MainCore::hEntryBaseAddress;
	 PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER(handle);
	 PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS((LONG)handle + pDsHeader->e_lfanew);
	 PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pPeHeader->OptionalHeader;
	 DWORD base = (ULONG)handle;/* + pOptionalHeader->BaseOfCode;*/


	 DWORD ApplicationPID = GetProcessId(GetCurrentProcess());
	/* DWORD User32Size = GetModuleSize(ApplicationPID, GetModuleName(hInstance));*/
	 DWORD size = pOptionalHeader->SizeOfImage;

	 unsigned int count = 0;
	 return	PatternScan::Search(base, size, (unsigned char*)pPattern, count);
 }

 DWORD PatternScan::Search(DWORD base, DWORD size, unsigned char* pattern, unsigned int &instances)
 {
	 //unsigned int opcodes = 0;			// edit out by lm
	 unsigned char *code = (unsigned char *)base;
	 int patternLength = strlen((char *)pattern);

	 if (pattern[0] == ' ')
		 return NULL;

	 // edit out by lm: HEX_NEG_MASK was nowhere to be found :)
	 //if( (size & Constants::HEX_NEG_MASK) ||
	 //	(base & Constants::HEX_NEG_MASK) )
	 //	return NULL;

	 //opcodes = GetNoOpcodes( (const char *)pattern );

	 //if( (size - opcodes) & Constants::HEX_NEG_MASK )
	 //	return NULL;
	 // end edit by lm.

	 for (unsigned int i(0); i < size; i++)
	 {
		 for (int j(0), k(0); j < patternLength && (i + k < size); k++)
		 {
			 unsigned char tempChar[3];
			 memset(tempChar, 0, sizeof(tempChar));

			 if (pattern[j] == (unsigned char)'?')
			 {
				 j += 2;
				 continue;
			 }

			 sprintf((char *)tempChar, "%02X", code[(i + k)]);

			 if (tempChar[0] != pattern[j] ||
				 tempChar[1] != pattern[j + 1])
				 break;

			 j += 3;

			 if (j > (patternLength - 2))
			 {
				 DWORD pointerLoc = (base + i + 1);

				 instances++;
				 // edited by lm: FindSignature would run outside of bounds, pointerLoc is off-by one.
				 //FindSignature( pointerLoc, (size - pointerLoc), pattern, instances );
				 --pointerLoc;
				 // end edit by lm

				 return pointerLoc;
			 }
		 }
	 }

	 return NULL;
 }
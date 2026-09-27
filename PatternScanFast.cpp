#include "stdafx.h"
#include "PatternScanFast.h"
DWORD Search(unsigned char* pData, unsigned int length, const unsigned char* pat, const char* msk)
{
	const unsigned char* end = pData + length - strlen(msk);
	int num_masks = ceil((float)strlen(msk) / (float)16);
	int masks[32]; //32*16 = enough masks for 512 bytes
	memset(masks, 0, num_masks * sizeof(int));
	for (int i = 0; i < num_masks; ++i)
		for (int j = strnlen(msk + i * 16, 16) - 1; j >= 0; --j)
			if (msk[i * 16 + j] == 'x')
				masks[i] |= 1 << j;

	__m128i xmm1 = _mm_loadu_si128((const __m128i*) pat);
	__m128i xmm2, xmm3, mask;
	for (; pData != end; _mm_prefetch((const char*)(++pData + 64), _MM_HINT_NTA)) {
		if (pat[0] == pData[0]) {
			xmm2 = _mm_loadu_si128((const __m128i*) pData);
			mask = _mm_cmpeq_epi8(xmm1, xmm2);
			if ((_mm_movemask_epi8(mask) & masks[0]) == masks[0]) {
				for (int i = 1; i < num_masks; ++i) {
					xmm2 = _mm_loadu_si128((const __m128i*) (pData + i * 16));
					xmm3 = _mm_loadu_si128((const __m128i*) (pat + i * 16));
					mask = _mm_cmpeq_epi8(xmm2, xmm3);
					if ((_mm_movemask_epi8(mask) & masks[i]) == masks[i]) {
						if ((i + 1) == num_masks)
							return (DWORD)pData;
					}
					else goto cont;
				}
				return (DWORD)pData;
			}
		}cont:;
	}
	return NULL;
}
std::vector<char> HexToBytes(const std::string& hex) {
	std::vector<char> bytes;

	for (unsigned int i = 0; i < hex.length(); i += 2) {
		std::string byteString = hex.substr(i, 2);
		char byte = (char)strtol(byteString.c_str(), NULL, 16);
		bytes.push_back(byte);
	}

	return bytes;
}

pair<DWORD, DWORD> PatternScanFast::SegmentDetails(string segment)
{
	HMODULE hModule = GetModuleHandle(NULL);
	char* dllImageBase = (char*)hModule;
	IMAGE_NT_HEADERS* pNtHdr = ImageNtHeader(hModule);
	IMAGE_SECTION_HEADER* pSectionHdr = (IMAGE_SECTION_HEADER*)(pNtHdr + 1);
	struct ImageSectionInfo
	{
		char SectionName[IMAGE_SIZEOF_SHORT_NAME]; //the macro is defined WinNT.h
		char* SectionAddress;
		int SectionSize;
		ImageSectionInfo(const char* name)
		{
			strcpy(SectionName, name);
		}
	};
	ImageSectionInfo* pSectionInfo = NULL;

	
	for (int i = 0; i < pNtHdr->FileHeader.NumberOfSections; i++)
	{
		char* name = (char*)pSectionHdr->Name;
		if (memcmp(name, segment.c_str(), 5) == 0)
		{
			pSectionInfo = new ImageSectionInfo(segment.c_str());
			pSectionInfo->SectionAddress = dllImageBase + pSectionHdr->VirtualAddress;


			pSectionInfo->SectionSize = pSectionHdr->Misc.VirtualSize;
			return make_pair<DWORD, DWORD>((DWORD)pSectionInfo->SectionAddress, (DWORD)pSectionInfo->SectionSize);
		}
		pSectionHdr++;
	}
	return make_pair<DWORD, DWORD>(0, 0);
}

vector<DWORD> PatternScanFast::FindPatternList(const char* pPattern,string segment )
{
	/*HMODULE handle = (HMODULE)MainCore::hEntryBaseAddress;
	PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER(handle);
	PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS((LONG)handle + pDsHeader->e_lfanew);
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pPeHeader->OptionalHeader;
	DWORD base = (ULONG)handle;*/


	DWORD base = NULL;
	DWORD size = NULL;
	if (segment=="text")
	{
		base = SegmentDetails(".text").first -1000;

		size = SegmentDetails(".text").second;
	}
	else if ((segment == "rdata"))
	{
		base = SegmentDetails(".rdata").first;

		size = SegmentDetails(".rdata").second;
	}
	


	

	/*DWORD size = pOptionalHeader->SizeOfImage;*/


	string pattern(pPattern);
	/*pattern = pattern + " 00";*/
	string insertString(pPattern);
	/*insertString = insertString + " 00";*/

	while (insertString.find("?") != std::string::npos)
		insertString.replace(insertString.find("?"), 1, "00");
	while (insertString.find(" ") != std::string::npos)
		insertString.replace(insertString.find(" "), 1, "\\x");
	insertString.insert(0, "\\x");


	while (pattern.find("?") != std::string::npos)
		pattern.replace(pattern.find("?"), 1, "00");
	while (pattern.find(" ") != std::string::npos)
		pattern.replace(pattern.find(" "), 1, "");
	pattern.insert(0, "");

	std::string mask = "";

	for (size_t i = 1; i <= insertString.length() / 4; i++)
	{
		int32_t index = i * 4 - 1;

		if (insertString.at(index) == '0' && insertString.at(index - 1) == '0')
			mask += "?";
		else
			mask += "x";
	}

	transform(insertString.begin(), insertString.end(), insertString.begin(), tolower);

	std::vector<char>  a = HexToBytes(pattern);
	const char* pattern2 = reinterpret_cast<const char*>(a.data());

	const char* mask2 = mask.c_str();
	vector<DWORD> addressList;

	while (base)
	{
		DWORD address = Search((unsigned char*)base, size, (const unsigned char* )pattern2, mask2);
		/*DWORD address = (DWORD)Search((const PBYTE)base, size, pPattern);*/
		if (address)
		{
			addressList.push_back(address);
			size = size - ((address + 1) - base);
			base = address + 1;
		}
		else
		{
			return addressList;
		}
		
	}
	return addressList;
}
DWORD PatternScanFast::FindPattern(const char* pPattern)
{
	HMODULE handle = (HMODULE)MainCore::hEntryBaseAddress;
	PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER(handle);
	PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS((LONG)handle + pDsHeader->e_lfanew);
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pPeHeader->OptionalHeader;
	DWORD base = (ULONG)handle;




	//MODULEINFO modinfo = { 0 };
	//HMODULE hModule = GetModuleHandle(NULL);
	//
	//GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	//modinfo;


	DWORD size = pOptionalHeader->SizeOfImage;


	string pattern(pPattern);
	string insertString(pPattern);


	/*while (insertString.find("?") != std::string::npos)
		insertString.replace(insertString.find("?"), 1, "00");
	while (insertString.find(" ") != std::string::npos)
		insertString.replace(insertString.find(" "), 1, "\\x");
	insertString.insert(0, "\\x");


	while (pattern.find("?") != std::string::npos)
		pattern.replace(pattern.find("?"), 1, "00");
	while (pattern.find(" ") != std::string::npos)
		pattern.replace(pattern.find(" "), 1, "");
	pattern.insert(0, "");

	std::string mask = "";

	for (size_t i = 1; i <= insertString.length() / 4; i++)
	{
		int32_t index = i * 4 - 1;

		if (insertString.at(index) == '0' && insertString.at(index - 1) == '0')
			mask += "?";
		else
			mask += "x";
	}
	 
	transform(insertString.begin(), insertString.end(), insertString.begin(), tolower);
	
	std::vector<char>  a = HexToBytes(pattern);
	const char* pattern2 = reinterpret_cast<const char*>(a.data());
		
	const char* mask2 = mask.c_str();*/

	
	return 0;/* (DWORD)Search((const PBYTE)base, size, pPattern);*/
	//return (DWORD)const_cast<LPVOID>(Search((const uint8_t*)base, size, reinterpret_cast<const uint8_t*>(pattern2), mask2));
}




//struct PartData
//{
//	int32_t mask = 0;
//	__m128i needle; //C2797: list initialization inside member initializer list or non-static data member initializer is not implemented
//
//
//	PartData()
//	{
//		memset(&needle, 0, sizeof(needle));
//	}
//};
//const void* PatternScanFast::Search(const uint8_t* data, const uint32_t size, const uint8_t* pattern, const char* mask)
//{
//	const uint8_t* result = nullptr;
//	auto len = strlen(mask);
//	auto first = strchr(mask, '?');
//	size_t len2 = (first != nullptr) ? (first - mask) : len;
//	auto firstlen = min(len2, 16);
//	intptr_t num_parts = (len < 16 || len % 16) ? (len / 16 + 1) : (len / 16);
//	PartData parts[399];
//
//	for (intptr_t i = 0; i < num_parts; ++i, len -= 16)
//	{
//		for (size_t j = 0; j < min(len, 16) - 1; ++j)
//			if (mask[16 * i + j] == 'x')
//				_bittestandset((LONG*)&parts[i].mask, j);
//
//		parts[i].needle = _mm_loadu_si128((const __m128i*)(pattern + i * 16));
//	}
//
//	bool abort = false;
//
//#pragma omp parallel for
//	for (intptr_t i = 0; i < static_cast<intptr_t>(size) / 32 - 1; ++i)
//	{
//#pragma omp flush (abort)
//		if (!abort)
//		{
//			auto block = _mm256_loadu_si256((const __m256i*)data + i);
//			if (_mm256_testz_si256(block, block))
//				continue;
//
//			auto offset = _mm_cmpestri(parts->needle, firstlen, _mm_loadu_si128((const __m128i*)(data + i * 32)), 16, _SIDD_CMP_EQUAL_ORDERED);
//			if (offset == 16)
//			{
//				offset += _mm_cmpestri(parts->needle, firstlen, _mm_loadu_si128((const __m128i*)(data + i * 32 + 16)), 16, _SIDD_CMP_EQUAL_ORDERED);
//				if (offset == 32)
//					continue;
//			}
//
//			for (intptr_t j = 0; j < num_parts; ++j)
//			{
//				auto hay = _mm_loadu_si128((const __m128i*)(data + (2 * i + j) * 16 + offset));
//				auto bitmask = _mm_movemask_epi8(_mm_cmpeq_epi8(hay, parts[j].needle));
//				if ((bitmask & parts[j].mask) != parts[j].mask)
//					goto next;
//			}
//
//			result = data + 32 * i + offset;
//			abort = true;
//#pragma omp flush (abort)
//		}
//		//break;  //C3010: 'break' : jump out of OpenMP structured block not allowed
//
//	next:;
//	}
//
//	return result;
//}

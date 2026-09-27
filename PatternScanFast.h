#pragma once
class PatternScanFast
{
public:
	static DWORD  FindPattern(const char* pPattern);
	static vector<DWORD> FindPatternList(const char* pPattern,string segment);
	static pair<DWORD, DWORD> PatternScanFast::SegmentDetails(string segment);
	//static const void* Search(const uint8_t* data, const uint32_t size, const uint8_t* pattern, const char* mask);
private:

};
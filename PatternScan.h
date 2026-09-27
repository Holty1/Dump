#pragma once
class PatternScan
{
public:

	
	static  DWORD FindPattern(const char* pPattern);
	static  DWORD FindPattern2(const char* pPattern);
	static   DWORD Search(DWORD base, DWORD size, unsigned char* pattern, unsigned int &instances);
	
};


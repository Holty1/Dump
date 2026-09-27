#pragma once
class ProtectExtension
{
public:
	static string GetMacAdress();
	static DWORD GetVolumeId(string volumeLetter);
	static string GetCpuId();
	static string GetMachineName();
	static string GetHWID();
};


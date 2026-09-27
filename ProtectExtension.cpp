#include "stdafx.h"
#include "ProtectExtension.h"



string ProtectExtension::GetMacAdress()
{
	IP_ADAPTER_INFO		AdapterInfo[32];
	PIP_ADAPTER_INFO	pAdapterInfo;

	DWORD dwSize = sizeof(AdapterInfo);
	DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwSize);
	string address = "";

	for (pAdapterInfo = AdapterInfo; pAdapterInfo; pAdapterInfo = pAdapterInfo->Next)
	{
		for (size_t i = 0; i < 6; i++)
		{
			char Out[10] = { 0 };
			int32_t k = pAdapterInfo->Address[i];
			sprintf_s(Out, "%s%02X", i ? "" : "", k);
			address += Out;
		}
	}
	return address;
}

DWORD ProtectExtension::GetVolumeId(string volumeLetter)
{
	DWORD serialNum = 0;

	string volumePath = volumeLetter + ":\\";
	GetVolumeInformation(StringExtension::GetWCharFromString(volumePath), NULL, 0, &serialNum, NULL, NULL, NULL, 0);
	

	return serialNum;
}


string ProtectExtension::GetCpuId()
{
	int cpuinfo[4] = { 0, 0, 0, 0 };
	__cpuid(cpuinfo, 0);
	string id;
	for (int i = 0; i < 4; i++)
	{
		id += to_string(cpuinfo[i])+"|";
	}

	return id;
}

string ProtectExtension::GetMachineName()
{
	TCHAR computerName[1024];
	DWORD size = 1024;
	GetComputerName(computerName, &size);
	return StringExtension::StringFromWChar(computerName);
}

string ProtectExtension::GetHWID()
{
	HW_PROFILE_INFO hwProfileInfo;
	GetCurrentHwProfile(&hwProfileInfo);
	wstring hwidWString = hwProfileInfo.szHwProfileGuid;
	return StringExtension::StringFromWString(hwidWString);
}
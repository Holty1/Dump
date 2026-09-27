#include "stdafx.h"
#include "AsmOperations.h"


DWORD CheckModuleFunctionNotJMP(DWORD address)
{

	//###################################################################################
	unsigned int decodedInstructionsCount = 0, i, next;
	_DecodeResult res;
	// Decoded instruction information.
	_DecodedInst decodedInstructions[MAX_INSTRUCTIONS];
	_DecodeType dt = Decode32Bits;
	_OffsetType offset = 0;
	res = distorm_decode(address, (const unsigned char*)address, 5, dt, decodedInstructions, 5, &decodedInstructionsCount);
	if (res == DECRES_INPUTERR) {

	}
	if (StringExtension::Equals((char*)decodedInstructions[0].mnemonic.p, "JMP"))
	{
		string s = "";
		s += (char*)decodedInstructions[0].operands.p;
		s = StringExtension::ReplaceString(s, "0x", "");
		char* p;
		DWORD n = strtol(s.c_str(), &p, 16);
		return n;
	}


	return address;
}
vector< std::pair<DWORD, string>>  AsmOperations::offsetList;
//#################################################################################
DWORD AsmOperations::GetFirstDworCallInstance(vector< _DecodedInst> funcInstructions)
{
	DWORD pointer = 0;
	for (vector< _DecodedInst>::iterator it = funcInstructions.begin(); it != funcInstructions.end(); ++it)
	{
		if (StringExtension::Equals((char*)it->mnemonic.p, "MOV") && StringExtension::Contains((char*)it->operands.p, "EAX, [0x"))
		{

			string strAddress = "";
			strAddress += (char*)it->operands.p;
			strAddress = StringExtension::ReplaceString(strAddress, "EAX, [", "");
			strAddress = StringExtension::ReplaceString(strAddress, "]", "");
			char * p;
			DWORD address = strtol(strAddress.c_str(), &p, 16);
			return address;
		}
	}
	/*MessageBox(NULL, L"GetFirstDworCallInstance", L"ERROR 1", NULL);*/
	return 0;
}
//#################################################################################
DWORD AsmOperations::GetInstanceCallDwordAddress(const char* functionName, vector< _DecodedInst> funcInstructions, DWORD callNumber)
{
	DWORD pointer = 0;
	for (vector< _DecodedInst>::iterator it = funcInstructions.begin(); it != funcInstructions.end(); ++it)
	{
		if (StringExtension::Equals((char*)it->mnemonic.p, "CALL"))
		{
			pointer++;
		}
		if (pointer == callNumber+1 && StringExtension::Equals((char*)it->mnemonic.p, "CALL") && !StringExtension::Contains((char*)it->operands.p, "-0x") && !StringExtension::Contains((char*)it->operands.p, "+0x"))
		{
			DWORD callAddress = GetCallStaticAddress(functionName,funcInstructions, callNumber + 1);
			vector< _DecodedInst> callInside = GetModuleFunctionsOpInstructions(CheckModuleFunctionNotJMP(callAddress), 100, false);
			DWORD address = GetFirstDworCallInstance(callInside);
			if (address == 0)
			{
				/*MessageBox(NULL, L"GetInstanceCallAddress", L"Error 1", NULL);*/
			}
			return address;

		}
		if (pointer > callNumber+1)
		{
			/*MessageBox(NULL, L"GetInstanceCallAddress", L"Error 2", NULL);*/
			return 0;
		}
	}
	/*MessageBox(NULL, L"GetInstanceCallAddress", L"Error 3", NULL);*/
	return 0;
}
//#################################################################################
DWORD AsmOperations::GetInstanceDwordAddress(const char* functionName,vector< _DecodedInst> funcInstructions, DWORD callNumber)
{
	DWORD pointer = 0;
	for (vector< _DecodedInst>::iterator it = funcInstructions.begin(); it != funcInstructions.end(); ++it)
	{
		if (StringExtension::Equals((char*)it->mnemonic.p, "CALL"))
		{
			pointer++;
		}
		if (pointer == callNumber )
		{
			if (StringExtension::Equals((char*)it->mnemonic.p, "MOV") && StringExtension::Contains((char*)it->operands.p, "ECX, [0x"))
			{
				string strAddress = "";
				strAddress += (char*)it->operands.p;
				strAddress = StringExtension::ReplaceString(strAddress, "ECX, [0x", "");
				strAddress = StringExtension::ReplaceString(strAddress, "]", "");
				char * p;
				DWORD address = strtol(strAddress.c_str(), &p, 16);
				return address;
			}
			if (StringExtension::Equals((char*)it->mnemonic.p, "MOV") && StringExtension::Contains((char*)it->operands.p, "EAX, [0x"))
			{
				string strAddress = "";
				strAddress += (char*)it->operands.p;
				strAddress = StringExtension::ReplaceString(strAddress, "EAX, [0x", "");
				strAddress = StringExtension::ReplaceString(strAddress, "]", "");
				char* p;
				DWORD address = strtol(strAddress.c_str(), &p, 16);
				return address;
			}
			if (StringExtension::Equals((char*)it->mnemonic.p, "MOV") && StringExtension::Contains((char*)it->operands.p, "EDX, [0x"))
			{
				string strAddress = "";
				strAddress += (char*)it->operands.p;
				strAddress = StringExtension::ReplaceString(strAddress, "EDX, [0x", "");
				strAddress = StringExtension::ReplaceString(strAddress, "]", "");
				char* p;
				DWORD address = strtol(strAddress.c_str(), &p, 16);
				return address;
			}
		}
		if (pointer > callNumber )
		{
			/*MessageBox(NULL, L"GetInstanceDwordAddress", L"ERROR 1", NULL);*/
			return 0;
		}
	}
	/*MessageBox(NULL, L"GetInstanceDwordAddress", L"ERROR 2", NULL);*/
	return 0;
}
//#################################################################################
DWORD AsmOperations::GetCallStaticAddress(const char* functionName,vector< _DecodedInst> funcInstructions, DWORD callNumber)
{
	DWORD pointer = 0;
	for (vector< _DecodedInst>::iterator it = funcInstructions.begin(); it != funcInstructions.end(); ++it)
	{

		if (StringExtension::Equals((char*)it->mnemonic.p, "CALL"))
		{
			pointer++;
		}
		if (pointer == callNumber && StringExtension::Equals((char*)it->mnemonic.p, "CALL") && !StringExtension::Contains((char*)it->operands.p, "-0x") && !StringExtension::Contains((char*)it->operands.p, "+0x"))
		{
			string strAddress = "";
			strAddress += (char*)it->operands.p;
			strAddress = StringExtension::ReplaceString(strAddress, "0x", "");
			char * p;
			DWORD address = strtol(strAddress.c_str(), &p, 16);
			return address;
		}
		if (pointer > callNumber)
		{
			/*MessageBox(NULL, L"GetCallStaticAddress", L"ERROR 1", NULL);*/
			return 0;
		}
	}
	/*MessageBox(NULL, L"GetCallStaticAddress", L"ERROR 2", NULL);*/
	return 0;
}
//#################################################################################
int AsmOperations::GetCallVirtualFunctionOffset(const char* functionName, vector< _DecodedInst> funcInstructions, DWORD callNumber,bool isDown)
{
	DWORD pointer = 0;
	for (vector< _DecodedInst>::iterator it = funcInstructions.begin(); it != funcInstructions.end(); ++it)
	{

		if (StringExtension::Equals((char*)it->mnemonic.p, "CALL"))
		{
			pointer++;
		}
		if (pointer == callNumber && StringExtension::Equals((char*)it->mnemonic.p, "CALL") && StringExtension::Equals((char*)it->operands.p, "EAX"))
		{
			

			vector< _DecodedInst>::iterator itLine = it;
			for (int i = 0; i < 4; i++)
			{
				 
					
				 
				if (StringExtension::Equals((char*)itLine->mnemonic.p, "MOV") && StringExtension::Contains((char*)itLine->operands.p, "EAX, [EDX+0x") )
				{
					string strAddress = "";
					strAddress += (char*)itLine->operands.p;
					strAddress = StringExtension::ReplaceString(strAddress, "EAX, [EDX+0x", "");
					strAddress = StringExtension::ReplaceString(strAddress, "]", "");
					char * p;
					DWORD address = strtol(strAddress.c_str(), &p, 16);
					return address;
				}

				if (StringExtension::Equals((char*)itLine->mnemonic.p, "INT3"))
				{
					return -1;
				}
				if (isDown)
				{
					itLine--;
				}
				else
				{
					itLine++;
				}
				
			}
			
			


			 
			return -1;
		}
		if (pointer == callNumber && StringExtension::Equals((char*)it->mnemonic.p, "CALL") && StringExtension::Contains((char*)it->operands.p, "EDX"))
		{
			 

			vector< _DecodedInst>::iterator itLine = it;
			for(int i = 0; i< 4;i++)
			{
				 
					
				 
				if (StringExtension::Equals((char*)itLine->mnemonic.p, "MOV") && StringExtension::Contains((char*)itLine->operands.p, "EDX, [EAX+0x") )
				{
					string strAddress = "";
					strAddress += (char*)itLine->operands.p;
					strAddress = StringExtension::ReplaceString(strAddress, "EDX, [EAX+0x", "");
					strAddress = StringExtension::ReplaceString(strAddress, "]", "");
					char * p;
					DWORD address = strtol(strAddress.c_str(), &p, 16);
					return address;
				}

				if (StringExtension::Equals((char*)itLine->mnemonic.p, "INT3"))
				{
					return -1;
				}
				if (isDown)
				{
					itLine--;
				}
				else
				{
					itLine++;
				}
			}
			
			


			 
			return -1;
		}
		if (pointer == callNumber && StringExtension::Equals((char*)it->mnemonic.p, "CALL") && StringExtension::Contains((char*)it->operands.p, "ESI"))
		{


			vector< _DecodedInst>::iterator itLine = it;
			for (int i = 0; i < 12; i++)
			{

				if (isDown)
				{
					itLine--;
				}
				else
				{
					itLine++;
				}
				if (StringExtension::Equals((char*)itLine->mnemonic.p, "CALL"))
				{
					return -1;
				}
				if (StringExtension::Equals((char*)itLine->mnemonic.p, "MOV") && StringExtension::Contains((char*)itLine->operands.p, "ESI, [EAX+0x"))
				{
					string strAddress = "";
					strAddress += (char*)itLine->operands.p;
					strAddress = StringExtension::ReplaceString(strAddress, "ESI, [EAX+0x", "");
					strAddress = StringExtension::ReplaceString(strAddress, "]", "");
					char* p;
					DWORD address = strtol(strAddress.c_str(), &p, 16);
					return address;
				}

				if (StringExtension::Equals((char*)itLine->mnemonic.p, "INT3"))
				{
					return -1;
				}
				
			}





			return -1;
		}

		if (pointer == callNumber && StringExtension::Equals((char*)it->mnemonic.p, "CALL") && StringExtension::Contains((char*)it->operands.p, "DWORD [EAX+0x"))
		{
			string strAddress = "";
			strAddress += (char*)it->operands.p;
			strAddress = StringExtension::ReplaceString(strAddress, "DWORD [EAX+0x", "");
			strAddress = StringExtension::ReplaceString(strAddress, "]", "");
			char * p;
			DWORD address = strtol(strAddress.c_str(), &p, 16);
			return address;
		}
		if (pointer > callNumber)
		{
		
			return -1;
		}
	}
	/*MessageBox(NULL, L"GetCallVirtualAddress", L"ERROR 2", NULL);*/
	return -1;
}
//#################################################################################
DWORD AsmOperations::GetModuleFunctionsCallsCount(vector< _DecodedInst> funcInstructions)
{
	DWORD counter = 0;
	for (vector< _DecodedInst>::iterator it = funcInstructions.begin(); it != funcInstructions.end(); ++it)
	{

		if (StringExtension::Equals((char*)it->mnemonic.p, "CALL"))
		{
			counter++;
		}
	}
	return counter;
}
//#################################################################################
vector< _DecodedInst> AsmOperations::GetModuleFunctionsOpInstructions(DWORD offset, DWORD sizeOp, bool reverseToEnd)
{
	vector< _DecodedInst> ret;
	unsigned int decodedInstructionsCount = 0;
	_DecodeResult res;

	_DecodedInst decodedInstructions[MAX_INSTRUCTIONS];
	_DecodeType dt = Decode32Bits;

	res = distorm_decode(offset, (const unsigned char*)offset, sizeOp, dt, decodedInstructions, MAX_INSTRUCTIONS, &decodedInstructionsCount);
	if (res == DECRES_INPUTERR) {

	}
	for (int i = 0; i < decodedInstructionsCount; i++)
	{
		ret.push_back(decodedInstructions[i]);
	}
	if (reverseToEnd)
	{
		reverse(ret.begin(), ret.end());
	}
	return ret;
}
//#################################################################################
DWORD AsmOperations::GetModuleFunctionSize(const char * funcName,map< DWORD, string> moduleFunctions )
{
	map<DWORD, string>::iterator itor = moduleFunctions.begin();

	for (; itor != moduleFunctions.end(); itor++)
	{
		if (StringExtension::Equals(itor->second.c_str(), funcName))
		{

			map<DWORD, string>::iterator itorNext = itor;
			itorNext++;
			if (itorNext != moduleFunctions.end())
			{
				DWORD sizeFunc = itorNext->first - itor->first;
				return sizeFunc;
			}
			else
			{
				DWORD sizeFunc = 0;
				for (int i = 0;; i++)
				{
					BYTE value = *reinterpret_cast<BYTE*>(itor->first + i);
					if (value == 0xCC)
					{
						break;
					}
					sizeFunc++;
				}
				return sizeFunc;
			}

		}
	}
	return 0;
}
//#################################################################################
DWORD AsmOperations::GetNativeFunctionStart(DWORD address)
{

		for (int i = 0;; i++)
		{
			
			if (*reinterpret_cast<BYTE*>(address - i) == 0xCC)
			{
				if (*reinterpret_cast<BYTE*>((address - i) - 1) == 0xCC)
				{
					return address-i+1;
				}
				
			}
			if (*reinterpret_cast<BYTE*>(address - i)  == 0x55)
			{
				if (*reinterpret_cast<BYTE*>((address - i )- 1) == 0xCC)
				{
					return address - i;
				}
			}
			if (*reinterpret_cast<BYTE*>(address - i) == 0xEC)
			{
				if (*reinterpret_cast<BYTE*>((address - i) - 1) == 0x8B)
				{
					if (*reinterpret_cast<BYTE*>((address - i) - 2) == 0x55)
					{
						return  ((address - i) - 2);
					}
				}
			}
		}

	
	return 0;
}
//#################################################################################
DWORD AsmOperations::GetNativeFunctionSize(DWORD address)
{
	


		 
		for (DWORD i = 0;; i++)
		{
			if (*reinterpret_cast<BYTE*>(address + i + 1) == 0xCC)
			{
				if (*reinterpret_cast<BYTE*>(address + i + 2) == 0xCC)
				{
					return i ;
				}

			}
			if (*reinterpret_cast<BYTE*>(address + i + 1) == 0x55)
			{
				if (*reinterpret_cast<BYTE*>(address + i + 2) == 0x8B)
				{
					if (*reinterpret_cast<BYTE*>(address + i + 3) == 0xEC)
					{
						return i;
					}
				}
			}
			 
		}
		 
	
	return 0;
}
//#################################################################################
DWORD AsmOperations::GetAddressFromVectorOffsetList(const char* offsetName)
{
	for (vector< std::pair<DWORD, string >>::iterator it = AsmOperations::offsetList.begin(); it != AsmOperations::offsetList.end(); ++it)
	{

		if (StringExtension::Equals(it->second.c_str(), offsetName))
		{
			return it->first;
		}
	}
	return 0;
}

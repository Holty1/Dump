#pragma once
class AsmOperations
{
public:
	static DWORD GetFirstDworCallInstance(vector< _DecodedInst> funcInstructions);
	static	DWORD GetInstanceCallDwordAddress(const char* functionName, vector< _DecodedInst> funcInstructions, DWORD callNumber);
	static	DWORD GetInstanceDwordAddress(const char* functionName,vector< _DecodedInst> funcInstructions, DWORD callNumber);
	static	DWORD GetCallStaticAddress(const char* functionName,vector< _DecodedInst> funcInstructions, DWORD callNumber);
	static	DWORD GetModuleFunctionsCallsCount(vector< _DecodedInst> funcInstructions);
	static vector< _DecodedInst> GetModuleFunctionsOpInstructions(DWORD offset, DWORD sizeOp, bool reverseToEnd);
	static DWORD GetModuleFunctionSize(const char * funcName,map< DWORD, string> moduleFunctions );
	
	static int GetCallVirtualFunctionOffset(const char* functionName, vector< _DecodedInst> funcInstructions, DWORD callNumber, bool isDown);
	static vector< std::pair<DWORD, string >>  offsetList;
	static DWORD GetNativeFunctionSize(DWORD address);
	static DWORD GetNativeFunctionStart(DWORD address);
	static DWORD GetAddressFromVectorOffsetList(const char* offsetName);
};


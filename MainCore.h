#pragma once
class MainCore
{
public:
	MainCore();
	~MainCore();
	static void Initialize();
	
	static void RunUi();
	static  map< DWORD, string> CreateModuleFunctionMap();
	
	static  void SetBaseAddress(bool isGlobal);
	struct FuncStruct
	{

		FuncStruct(string functionName, DWORD functionAddress, string  searchLine)
		{
			this->searchLine = searchLine;
			this->functionName = functionName;
			this->functionAddress = functionAddress;

		}
		string searchLine;
		string functionName;
		DWORD functionAddress;
		bool operator < (const FuncStruct& str) const
		{
			return (functionName < str.functionName);
		}
	};
	
	static LogWindow  * logWindow;
	static map<string, PyMethodDef *> initModulesMap;
	static vector<MainCore::FuncStruct> searchOutput;
	static HMODULE		hModule;
	static map<string, string> pythonPatternFunctionsList;
	static DWORD hEntryBaseAddress;
};

map<string, string> MainCore::pythonPatternFunctionsList = {
	{ "55 8B EC 51 8D 45 FC 50 FF 75 0C FF 75 08 E8 ? ? ? ? 8B 55 10 83 C4 0C 8A 4D FC 88 0A 8B E5 5D C3", "PyTuple_GetInteger"},
	{ "55 8B EC FF 75 08 FF 15 ? ? ? ? 8B 4D 0C 83 C4 04 3B C8 7C 04 32 C0 5D C3 51 FF 75 08 FF 15 ? ? ? ? 83 C4 08 85 C0 74 EB 50 FF 15 ? ? ? ? 8B 4D 10", "PyTuple_GetInteger"},
	{ "55 8B EC 81 EC ? ? ? ? A1 ? ? ? ? 33 C5 89 45 FC 8B 45 08 85 C0", "Py_BuildException"},
	{ "FF 05 ? ? ? ? B8 ? ? ? ? C3", "Py_BuildNone"},
	{ "55 8B EC FF 75 08 E8 ? ? ? ? 8B 4D 0C 83 C4 04 3B C8 7C 04 32 C0 5D C3 51 FF 75 08 E8 ? ? ? ? 83 C4 08 85 C0 74 EC 50 E8 ? ? ? ? 83 C4 04", "PyTuple_GetBoolean"},
	{ "55 8B EC FF 75 08 E8 ? ? ? ? 8B 4D 0C 83 C4 04 3B C8 7C 04 32 C0 5D C3 51 FF 75 08 E8 ? ? ? ? 83 C4 08 85 C0 74 EC 50 E8 ? ? ? ? 8B 4D 10 83 C4 04 89 01 B0 01 5D C3", "PyTuple_GetLong"},
	{ "E8 ? ? ? ? 33 C0 C3", "Py_BadArgument"},
	{ "55 8B EC 83 EC 08 8D 45 0C 89 45 FC 6A 00","Py_BuildValue"},
	{ "55 8B EC FF 75 08 E8 ? ? ? ? 8B 4D 0C 83 C4 04 3B C8 7C 04 32 C0 5D C3 51 FF 75 08 E8 ? ? ? ? 8B C8 83 C4 08 85 C9 74 EA 8B 41 04", "PyTuple_GetString"},
	{ "55 8B EC FF 75 08 FF 15 ? ? ? ? 8B 4D 0C 83 C4 04 3B C8 7C 04 32 C0 5D C3 51 FF 75 08 FF 15 ? ? ? ? 8B C8 83 C4 08 85 C9 74 E9 8B 41 04", "PyTuple_GetString"},
	{ "55 8B EC FF 75 08 E8 ? ? ? ? 8B 4D 0C 83 C4 04 3B C8 7C 04 32 C0 5D C3 51 FF 75 08 E8 ? ? ? ? 83 C4 08 85 C0 74 EC 50 E8 ? ? ? ? 8B 4D 10 83 C4 04 89 01 B0 01 5D C3", "PyTuple_GetFloat"},
	{ "55 8B EC FF 75 08 FF 15 ? ? ? ? 8B 4D 0C 83 C4 04 3B C8 7C 04 32 C0 5D C3 51 FF 75 08 FF 15 ? ? ? ? 83 C4 08 85 C0 74 EB 50 FF 15 ? ? ? ? 8B 4D 10", "PyTuple_GetFloat"},

	{"56 8B 74 24 08 56 FF 15 ? ? ? ? 8B 4C 24 10 83 C4 04 3B C8 7C 04 32 C0 5E C3 51 56 FF 15 ? ? ? ? 83 C4 08 85 C0 74 ED 50 FF 15 ? ? ? ? 8B 4C 24 14 83 C4 04 89 01 B0 01 5E C3 CC CC 56 8B 74 24 08 56 FF 15 ? ? ? ? 8B 4C 24 10 83 C4 04 3B C8 7C 04 32 C0 5E C3 51 56 FF 15 ? ? ? ? 83 C4 08 85 C0 74 ED 50","PyTuple_GetInterger"},
	{"81 EC 08 02 00 00 A1 ? ? ? ? 33 C4 89 84 24 04 02 00 00 8B 84 24 0C 02 00 00 85 C0 75 08 FF 15 ? ? ? ? EB 2F 8D 8C 24 10 02 00 00 51 50 8D 54 24 08 68 01 02 00 00 52 E8 ? ? ? ? 8B 0D ? ? ? ? 8B 11 8D 44 24 10 50 52 FF 15 ? ? ? ? 83 C4 18 E8 ? ? ? ? 8B 8C 24 04 02 00 00 33 CC E8 ? ? ? ? 81 C4 08 02 00 00 C3","Py_BuildException"},
	{"A1 ? ? ? ? FF 00 A1 ? ? ? ? C3 CC CC CC 56","Py_BuildNone"},
	{"56 8B 74 24 08 56 FF 15 ? ? ? ? 8B 4C 24 10 83 C4 04 3B C8 7C 04 32 C0 5E C3 51 56 FF 15 ? ? ? ? 83 C4 08 85 C0 74 ED 8B 48 04 F7 41 54 00 00 00 08 74 E1 50 FF 15 ? ? ? ? 8B 54 24 14 83 C4 04 89 02 B0 01 5E C3","PyTuple_GetString"},
	{"56 8B 74 24 08 56 FF 15 ? ? ? ? 8B 4C 24 10 83 C4 04 3B C8 7C 04 32 C0 5E C3 51 56 FF 15 ? ? ? ? 83 C4 08 85 C0 74 ED 50 FF 15 ? ? ? ? 8B 44 24 14 83 C4 04 D9 18 B0 01 5E C3","PyTuple_GetFloat"}

};
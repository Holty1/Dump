#include "stdafx.h"
#include "MainCore.h"
#include "tlhelp32.h"
#include "boost/filesystem.hpp"

#include <exception>
//#include <boost/crc.hpp>
//#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#pragma pack(pop)
#pragma pack(push, 4)
typedef struct SEterPackIndex
{
	long			id;
	char			filename[160 + 1];
	DWORD			filename_crc;
	long			real_data_size;
	long			data_size;
#ifdef CHECKSUM_CHECK_MD5
	BYTE			MD5Digest[16];
#else
	DWORD			data_crc;
#endif
	long			data_position;
	char			compressed_type;
} TEterPackIndex;
#pragma pack(pop)





typedef void(__thiscall* tCEterFileDictInsertItem)(void* This, DWORD* pkPack, TEterPackIndex* pkInfo);
//typedef bool(__thiscall* tCEterPackManagerGet)(void* This, void* rMappedFile, const char* c_szFileName, LPCVOID* pData);/////
typedef bool(__thiscall* tCEterPackManagerGet)(void* This, void* rMappedFile, const char* c_szFileName, LPCVOID* pData);/////



typedef DWORD(__thiscall* tCMappedFileSize)(void* This);
typedef DWORD* (__thiscall* tCMappedFile)(void* This);


tCEterFileDictInsertItem nCEterFileDictInsertItem = NULL;
tCEterPackManagerGet nCEterPackManagerGet = NULL;


tCMappedFile CMappedFile = NULL;
tCMappedFileSize CMappedFileSize = NULL;

tCEterPackManagerGet CEterPackManagerGet = NULL;

vector<string> CEterFileDict;
vector<TEterPackIndex*> CEterFileDict2;
__declspec(dllexport) void __cdecl Init(void)
{
	
}


void _fastcall NewCEterFileDictInsertItem(void* This, void* EDX, DWORD* pkPack, TEterPackIndex* pkInfo)
{
		/*cout << "insert" << endl;	*/
	
	/*MessageBox(NULL, L"BP-Insert", L"BPInsert", NULL);*/
	/*if (StringExtension::Contains(pkInfo->filename, "d:/ymir work/pc/assassin/61250.dds"))
	{
	DWORD k =*reinterpret_cast<DWORD *>(pCPythonNetworkStreamInstance);
	
	}*/
CEterFileDict.push_back(pkInfo->filename);
	/*DWORD v =*reinterpret_cast<DWORD*>(pkInfo);
	TEterPackIndex* ddd = (TEterPackIndex*)v;
	const char* f = (const char*)((DWORD)EDX-160);
	const char* ss = (const char*)(pkPack-160);*/
	
	/*cout<<"[" << pkInfo->filename << "]"<< endl;*/
	return nCEterFileDictInsertItem(This, pkPack, pkInfo);
}

typedef bool(__thiscall* tCEterPackManagerGet4)(void* This,LPCVOID* pData, int a1, int a2, int a3, int a4, int a5,int a6, const char* c_szFileName,  void* rMappedFile);/////
tCEterPackManagerGet4 nCEterPackManagerGet4 = NULL;

//##################################################################################################################################################
bool  _fastcall  HookCEterPackManagerGet4(void* This, void* _EDX, LPCVOID* pData, int a1, int a2, int a3, int a4, int a5, int a6, const char* c_szFileName, void* rMappedFile)
{
	
		/*ret = nCEterPackManagerGet4(This, pData, a1, a2, a3, a4, a5,a6, c_szFileName, rMappedFile);*/
		if (CEterFileDict2.size() > 0)
		{
			cout << "##### SIZE" << CEterFileDict2.size() << "  ######" << endl;
				for (std::vector<TEterPackIndex*>::iterator it = CEterFileDict2.begin(); it != CEterFileDict2.end(); ++it)
				{
					TEterPackIndex* j = *it;

				

				bool ret = false;
				try
				{
					ret = nCEterPackManagerGet4(This, pData, a1, a2, a3, a4, a5, a6, j->filename, rMappedFile);
				}
				catch (const std::exception& e)
				{
					cout << "tu by wypierdoli這 " << j->filename << " zero plik" << endl;
					ret = false;
				}
				catch (...)
				{
					cout << "tu by wypierdoli這 " << j->filename << " zero plik" << endl;
					ret = false;
				}
				if (ret)
				{
					DWORD size = j->data_size;
					if (size)
					{
						string path = string(j->filename);
						string path2 = "./Dump/" + path;
						string path3 = path;
						path2 = StringExtension::ReplaceString(path2, "d:/", "");
						path2 = StringExtension::ReplaceString(path2, "d:\\", "");
						path2 = StringExtension::ReplaceString(path2, "D:/", "");
						path2 = StringExtension::ReplaceString(path2, "D:\\", "");
						path2 = StringExtension::ReplaceString(path2, "E:\\", "");
						path2 = StringExtension::ReplaceString(path2, "\\", "/");
						boost::filesystem::path rootPath(path2);
						boost::system::error_code returnedError;
						bool dir = boost::filesystem::create_directories(rootPath.parent_path(), returnedError);
						if (dir)
						{
							/*cout << c_szFileName << " zero folder" << endl;*/
						}
						boost::filesystem::ofstream  out(rootPath, std::ios::out | std::ios::binary);
						DWORD o = *reinterpret_cast<DWORD*>(pData);
						const char* u = (const char*)o;
						out.write(u, size);
					}
					else
					{
						cout << j->filename << " zero plik" << endl;
					}

				}
				else
				{
					cout << j->filename << " brak" << endl;

				}
			}
			if (CEterFileDict.size() > 0)
			{
				MessageBox(NULL, L"Wypakowanie Skonczone", L"Wypakowanie Skonczone", NULL);
				ExitProcess(0);

			}
		}
	
		bool ret = false;
		try
		{
			ret = nCEterPackManagerGet4(This, pData, a1, a2, a3, a4, a5, a6, c_szFileName, rMappedFile);
		}
		catch (...)
		{
			ret = false;
		}


		return ret;
		//return ret;
}



typedef bool(__thiscall* tCEterPackManagerGet2)(void* This, const char* c_szFileName, int a1, int a2, int a3, int a4, int a5, LPCVOID* pData, void* rMappedFile);/////
tCEterPackManagerGet2 nCEterPackManagerGet2 = NULL;

//##################################################################################################################################################
bool  _fastcall  HookCEterPackManagerGet2(void* This, void* _EDX, const char* c_szFileName, int a1, int a2, int a3, int a4, int a5, LPCVOID* pData, void* rMappedFile)
{


	if (CEterFileDict.size() > 0)
	{
		int counter = 0;
		cout << "##### SIZE" << CEterFileDict.size() << "  ######" << endl;
		reverse(CEterFileDict.begin(), CEterFileDict.end());
		for (std::vector<string>::iterator it = CEterFileDict.begin(); it != CEterFileDict.end(); ++it)
		{
			counter++;
			/*	cout << "(" << it->c_str() << ")" << endl;*/

			bool ret = true;
			try
			{
				ret = nCEterPackManagerGet2(This, it->c_str(), a1, a2, a3, a4, a5, pData, rMappedFile);
			}
			catch (...)
			{

			}


			if (ret)
			{
				DWORD size = CMappedFileSize(rMappedFile);
				if (size)
				{
					string path = string(it->c_str());
					string path2 = "./Dump/" + path;
					string path3 = path;
					path2 = StringExtension::ReplaceString(path2, "d:/", "");
					path2 = StringExtension::ReplaceString(path2, "d:\\", "");
					path2 = StringExtension::ReplaceString(path2, "D:/", "");
					path2 = StringExtension::ReplaceString(path2, "D:\\", "");
					path2 = StringExtension::ReplaceString(path2, "E:\\", "");
					path2 = StringExtension::ReplaceString(path2, "\\", "/");
					boost::filesystem::path rootPath(path2);
					boost::system::error_code returnedError;
					bool dir = boost::filesystem::create_directories(rootPath.parent_path(), returnedError);
					if (dir)
					{
						/*cout << c_szFileName << " zero folder" << endl;*/
					}
					boost::filesystem::ofstream  out(rootPath, std::ios::out | std::ios::binary);
					DWORD o = *reinterpret_cast<DWORD*>(pData);
					const char* u = (const char*)o;
					out.write(u, size);
				}
				else
				{
					cout << it->c_str() << " zero plik" << endl;
				}

			}
			else
			{
				cout << it->c_str() << " brak" << endl;

			}
		}
		if (CEterFileDict.size() > 0)
		{
			MessageBox(NULL, L"Wypakowanie Skonczone", L"Wypakowanie Skonczone", NULL);
			ExitProcess(0);

		}
	}









	//cout << c_szFileName << endl;


	/*if (StringExtension::Contains(c_szFileName, "12t_12statue_01.gr2"))
	{

		MessageBox(NULL, L"Dfghfghone", L"Dhfgfgone", NULL);
	}*/

	bool ret = true;
	try
	{
		ret = nCEterPackManagerGet2(This, c_szFileName, a1, a2, a3, a4, a5, pData, rMappedFile);
	}
	catch (...)
	{

	}	if (ret)
	{
		DWORD size = CMappedFileSize(rMappedFile);
		if (size)
		{
			string path = string(c_szFileName);
			string path2 = "./Dump/" + path;
			string path3 = path;
			path2 = StringExtension::ReplaceString(path2, "d:/", "");
			path2 = StringExtension::ReplaceString(path2, "d:\\", "");
			path2 = StringExtension::ReplaceString(path2, "D:/", "");
			path2 = StringExtension::ReplaceString(path2, "D:\\", "");
			path2 = StringExtension::ReplaceString(path2, "E:\\", "");
			path2 = StringExtension::ReplaceString(path2, "\\", "/");
			boost::filesystem::path rootPath(path2);
			boost::system::error_code returnedError;
			bool dir = boost::filesystem::create_directories(rootPath.parent_path(), returnedError);
			if (dir)
			{
				cout << c_szFileName << " zero folder" << endl;
			}
			boost::filesystem::ofstream  out(rootPath, std::ios::out | std::ios::binary);
			DWORD o = *reinterpret_cast<DWORD*>(pData);
			const char* u = (const char*)o;
			out.write(u, size);
		}
		else
		{
			cout << c_szFileName << " zero plik" << endl;
		}

	}
	else
	{
		cout << c_szFileName << " brak" << endl;

	}

	/*ExitProcess(0);*/
	/*bool ret = nCEterPackManagerGet(This2, rMappedFile, c_szFileName, pData);*/

	return ret;
	//return ret;
}

//##################################################################################################################################################
bool  _fastcall  HookCEterPackManagerGet(void* This2, void* _EDX, void* rMappedFile, const char* c_szFileName, LPCVOID* pData)
{
	/*MessageBox(NULL, L"Dfghfghone", L"Dhfgfgone", NULL);*/
	if (CEterFileDict.size() > 0)
	{
		cout << "##### SIZE" << CEterFileDict.size() << "  ######" << endl;
		for (std::vector<string>::iterator it = CEterFileDict.begin(); it != CEterFileDict.end(); ++it)
		{

			if (StringExtension::Contains(it->c_str(), ""))
			{


			}

			bool ret = false;
			try
			{
				 ret = nCEterPackManagerGet(This2, rMappedFile, it->c_str(), pData);
			}
			catch (const std::exception& e)
			{ 
				cout <<"tu by wypierdoli這 "<< it->c_str() << " zero plik" << endl;
				ret = false;
			}
			catch (...)
			{
				cout << "tu by wypierdoli這 " << it->c_str() << " zero plik" << endl;
				ret = false;
			}
			if (ret)
			{
				DWORD size = CMappedFileSize(rMappedFile);
				if (size)
				{
					string path = string(it->c_str());
					string path2 = "./Dump/" + path;
					string path3 = path;
					path2 = StringExtension::ReplaceString(path2, "d:/", "");
					path2 = StringExtension::ReplaceString(path2, "d:\\", "");
					path2 = StringExtension::ReplaceString(path2, "D:/", "");
					path2 = StringExtension::ReplaceString(path2, "D:\\", "");
					path2 = StringExtension::ReplaceString(path2, "E:\\", "");
					path2 = StringExtension::ReplaceString(path2, "\\", "/");
					boost::filesystem::path rootPath(path2);
					boost::system::error_code returnedError;
					bool dir = boost::filesystem::create_directories(rootPath.parent_path(), returnedError);
					if (dir)
					{
						/*cout << c_szFileName << " zero folder" << endl;*/
					}
					boost::filesystem::ofstream  out(rootPath, std::ios::out | std::ios::binary);
					DWORD o = *reinterpret_cast<DWORD*>(pData);
					const char* u = (const char*)o;
					out.write(u, size);
				}
				else
				{
					cout << it->c_str() << " zero plik" << endl;
				}

			}
			else
			{
				cout << it->c_str() << " brak" << endl;

			}
		}
		if (CEterFileDict.size() > 0)
		{
			/*MessageBox(NULL, L"Wypakowanie Skonczone", L"Wypakowanie Skonczone", NULL);*/
			ExitProcess(0);

		}
	}
	/*else
	{
		MessageBox(NULL, L"Pusto", L"Pusto", NULL);
	}*/

	
	//if (CEterFileDict2.size() > 0)
	//{
	//	cout << "##### SIZE" << CEterFileDict2.size() << "  ######" << endl;
	//	for (std::vector<TEterPackIndex*>::iterator it = CEterFileDict2.begin(); it != CEterFileDict2.end(); ++it)
	//	{
	//		TEterPackIndex* j = *it;
	//		
	//		bool ret = false;
	//		try
	//		{
	//			ret = nCEterPackManagerGet(This2, rMappedFile, j->filename, pData);
	//		}
	//		catch (const std::exception& e)
	//		{
	//			cout << "tu by wypierdoli這 " << j->filename << " zero plik" << endl;
	//			ret = false;
	//		}
	//		catch (...)
	//		{
	//			cout << "tu by wypierdoli這 " << j->filename << " zero plik" << endl;
	//			ret = false;
	//		}
	//		if (ret)
	//		{
	//			DWORD size = j->data_size;
	//			if (size)
	//			{
	//				string path = string(j->filename);
	//				string path2 = "./Dump/" + path;
	//				string path3 = path;
	//				path2 = StringExtension::ReplaceString(path2, "d:/", "");
	//				path2 = StringExtension::ReplaceString(path2, "d:\\", "");
	//				path2 = StringExtension::ReplaceString(path2, "D:/", "");
	//				path2 = StringExtension::ReplaceString(path2, "D:\\", "");
	//				path2 = StringExtension::ReplaceString(path2, "E:\\", "");
	//				path2 = StringExtension::ReplaceString(path2, "\\", "/");
	//				boost::filesystem::path rootPath(path2);
	//				boost::system::error_code returnedError;
	//				bool dir = boost::filesystem::create_directories(rootPath.parent_path(), returnedError);
	//				if (dir)
	//				{
	//					/*cout << c_szFileName << " zero folder" << endl;*/
	//				}
	//				boost::filesystem::ofstream  out(rootPath, std::ios::out | std::ios::binary);
	//				/*DWORD o = *reinterpret_cast<DWORD*>(pData);
	//				const char* u = (const char*)o;
	//				out.write(u, size);*/
	//			}
	//			else
	//			{
	//				cout << j->filename << " zero plik" << endl;
	//			}

	//		}
	//		else
	//		{
	//			cout << j->filename << " brak" << endl;

	//		}
	//	}
	//	if (CEterFileDict.size() > 0)
	//	{
	//		MessageBox(NULL, L"Wypakowanie Skonczone", L"Wypakowanie Skonczone", NULL);
	//		ExitProcess(0);

	//	}
	//}

	//bool ret3 = nCEterPackManagerGet(This2, rMappedFile, c_szFileName, pData);
	//


	////cout << "##### " << c_szFileName << "  ######  " << h << endl;
	//return ret3;




	/*cout << c_szFileName  << endl;*/

	
	/*cout << c_szFileName << " [FILE]" << endl;*/
	bool ret = false;
	try
	{
		 ret = nCEterPackManagerGet(This2, rMappedFile, c_szFileName, pData);
	}
	catch (...)
	{
		ret = false;
	}
	
	if (ret)
	{
		DWORD size = CMappedFileSize(rMappedFile);
		if (size)
		{
			string path = string(c_szFileName);
			string path2 = "./Dump/" + path;
			/*string path2 = "c:/Dump/" + path;*/
			string path3 = path;
			path2 = StringExtension::ReplaceString(path2, "d:/", "");
			path2 = StringExtension::ReplaceString(path2, "d:\\", "");
			path2 = StringExtension::ReplaceString(path2, "D:/", "");
			path2 = StringExtension::ReplaceString(path2, "D:\\", "");
			path2 = StringExtension::ReplaceString(path2, "E:\\", "");
			path2 = StringExtension::ReplaceString(path2, "\\", "/");
			boost::filesystem::path rootPath(path2);
			boost::system::error_code returnedError;
			bool dir = boost::filesystem::create_directories(rootPath.parent_path(), returnedError);
			if (dir)
			{
				/*cout << c_szFileName << " zero folder" << endl;*/
			}
			boost::filesystem::ofstream  out(rootPath, std::ios::out | std::ios::binary);
			DWORD o = *reinterpret_cast<DWORD*>(pData);
			const char* u = (const char*)o;
			out.write(u, size);
		}
		else
		{
			/*cout << c_szFileName << " zero plik" << endl;*/
		}

	}
	else
	{
		/*cout << c_szFileName << " brak" << endl;*/

	}
	
	/*ExitProcess(0);*/
	/*bool ret = nCEterPackManagerGet(This2, rMappedFile, c_szFileName, pData);*/
	return ret;
	//return ret;



}


typedef bool(__thiscall* tCEterPackManagerGet3)(void* This, void* rMappedFile, const char* c_szFileName, LPCVOID* pDataconst, const char* unk1, int unk2);/////







tCEterPackManagerGet3 nCEterPackManagerGet3 = NULL;

bool  _fastcall  HookCEterPackManagerGet3(void* This2, void* _EDX, void* rMappedFile, const char* c_szFileName, LPCVOID* pData,const char* unk1,int unk2 )
{


	if (CEterFileDict.size() > 0)
	{
		cout << "##### SIZE" << CEterFileDict.size() << "  ######" << endl;
		for (std::vector<string>::iterator it = CEterFileDict.begin(); it != CEterFileDict.end(); ++it)
		{

			if (StringExtension::Contains(it->c_str(), ""))
			{


			}

			bool ret = false;
			try
			{
				ret = nCEterPackManagerGet3(This2, rMappedFile, it->c_str(), pData,unk1,unk2);
			}
			catch (const std::exception& e)
			{
				cout << "tu by wypierdoli這 " << it->c_str() << " zero plik" << endl;
				ret = false;
			}
			catch (...)
			{
				cout << "tu by wypierdoli這 " << it->c_str() << " zero plik" << endl;
				ret = false;
			}
			if (ret)
			{
				DWORD size = CMappedFileSize(rMappedFile);
				if (size)
				{
					string path = string(it->c_str());
					string path2 = "./Dump/" + path;
					string path3 = path;
					path2 = StringExtension::ReplaceString(path2, "d:/", "");
					path2 = StringExtension::ReplaceString(path2, "d:\\", "");
					path2 = StringExtension::ReplaceString(path2, "D:/", "");
					path2 = StringExtension::ReplaceString(path2, "D:\\", "");
					path2 = StringExtension::ReplaceString(path2, "E:\\", "");
					path2 = StringExtension::ReplaceString(path2, "\\", "/");
					boost::filesystem::path rootPath(path2);
					boost::system::error_code returnedError;
					bool dir = boost::filesystem::create_directories(rootPath.parent_path(), returnedError);
					if (dir)
					{
						/*cout << c_szFileName << " zero folder" << endl;*/
					}
					boost::filesystem::ofstream  out(rootPath, std::ios::out | std::ios::binary);
					DWORD o = *reinterpret_cast<DWORD*>(pData);
					const char* u = (const char*)o;
					out.write(u, size);
				}
				else
				{
					cout << it->c_str() << " zero plik" << endl;
				}

			}
			else
			{
				cout << it->c_str() << " brak" << endl;

			}
		}
		if (CEterFileDict.size() > 0)
		{
			MessageBox(NULL, L"Wypakowanie Skonczone", L"Wypakowanie Skonczone", NULL);
			ExitProcess(0);

		}
	}
	/*else
	{
		MessageBox(NULL, L"Pusto", L"Pusto", NULL);
	}*/









	/*cout << c_szFileName  << endl;*/


	cout << c_szFileName << " [FILE]" << endl;
	bool ret = false;
	try
	{
		ret = nCEterPackManagerGet3(This2, rMappedFile, c_szFileName, pData,unk1, unk2);
		cout << c_szFileName << " true" << endl;
	}
	catch (...)
	{
		ret = false;
	}

	//if (ret)
	//{
	//	DWORD size = CMappedFileSize(rMappedFile);
	//	if (size)
	//	{
	//		string path = string(c_szFileName);
	//		string path2 = "./Dump/" + path;
	//		/*string path2 = "c:/Dump/" + path;*/
	//		string path3 = path;
	//		path2 = StringExtension::ReplaceString(path2, "d:/", "");
	//		path2 = StringExtension::ReplaceString(path2, "d:\\", "");
	//		path2 = StringExtension::ReplaceString(path2, "D:/", "");
	//		path2 = StringExtension::ReplaceString(path2, "D:\\", "");
	//		path2 = StringExtension::ReplaceString(path2, "E:\\", "");
	//		path2 = StringExtension::ReplaceString(path2, "\\", "/");
	//		boost::filesystem::path rootPath(path2);
	//		boost::system::error_code returnedError;
	//		bool dir = boost::filesystem::create_directories(rootPath.parent_path(), returnedError);
	//		if (dir)
	//		{
	//			/*cout << c_szFileName << " zero folder" << endl;*/
	//		}
	//		boost::filesystem::ofstream  out(rootPath, std::ios::out | std::ios::binary);
	//		DWORD o = *reinterpret_cast<DWORD*>(pData);
	//		const char* u = (const char*)o;
	//		out.write(u, size);
	//	}
	//	else
	//	{
	//		/*cout << c_szFileName << " zero plik" << endl;*/
	//	}

	//}
	//else
	//{
	//	/*cout << c_szFileName << " brak" << endl;*/

	//}

	/*ExitProcess(0);*/
	/*bool ret = nCEterPackManagerGet(This2, rMappedFile, c_szFileName, pData);*/
	return ret;
	//return ret;



}


//##################################################################################################################################################

//##################################################################################################################################################


void __stdcall NewPostQuitMessage(UINT exitCode)
{

}
void __stdcall NewExitProcess(UINT exitCode)
{

}
typedef void(__stdcall* tExitProcess)(UINT exitCode);
tExitProcess nExitProcess;
typedef void(__stdcall* tPostQuitMessage)(UINT exitCode);
tPostQuitMessage nPostQuitMessage;
void DumpHook()//77A140
{
	//rubin s
	//CMappedFileSize = (tCMappedFileSize)(MainCore::hEntryBaseAddress + 0x335DC0);//1879160   122640

	// 
	//nCEterPackManagerGet = (tCEterPackManagerGet)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x379B90, (PBYTE)HookCEterPackManagerGet);

	//nCEterPackManagerGet2 = (tCEterPackManagerGet2)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x379B70, (PBYTE)HookCEterPackManagerGet2);




	//Aeldra
	//CMappedFileSize = (tCMappedFileSize)(MainCore::hEntryBaseAddress + 0x306100);//1879160   122640


	//nCEterPackManagerGet3 = (tCEterPackManagerGet3)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x34AA90, (PBYTE)HookCEterPackManagerGet3);

	//nCEterFileDictInsertItem = (tCEterFileDictInsertItem)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x3B35B0, (PBYTE)NewCEterFileDictInsertItem);


	//xales
	//CMappedFileSize = (tCMappedFileSize)(MainCore::hEntryBaseAddress + 0x20C9E0);//1879160   122640


	//nCEterPackManagerGet = (tCEterPackManagerGet)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0xF82C0, (PBYTE)HookCEterPackManagerGet);

	//nCEterFileDictInsertItem = (tCEterFileDictInsertItem)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x13293F0, (PBYTE)NewCEterFileDictInsertItem);

	//oriig
	//CMappedFileSize = (tCMappedFileSize)(MainCore::hEntryBaseAddress + 0x11B49);//sub_41DCAF(&v17);


	//nCEterPackManagerGet2 = (tCEterPackManagerGet2)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x3D91A0, (PBYTE)HookCEterPackManagerGet2);

	//nCEterFileDictInsertItem = (tCEterFileDictInsertItem)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0xE511, (PBYTE)NewCEterFileDictInsertItem);



	////Rub
	//CMappedFileSize = (tCMappedFileSize)(MainCore::hEntryBaseAddress + 0x1270F0);//sub_41DCAF(&v17);

	//nCEterPackManagerGet = (tCEterPackManagerGet)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x156570, (PBYTE)HookCEterPackManagerGet);//AtlasInfo.txt

	//
	//nCEterFileDictInsertItem = (tCEterFileDictInsertItem)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x1599B0, (PBYTE)NewCEterFileDictInsertItem);

	

	//SAm
	//CMappedFileSize = (tCMappedFileSize)(MainCore::hEntryBaseAddress + 0x3645F0);//sub_41DCAF(&v17);
	//
	//while(*reinterpret_cast<BYTE*>(MainCore::hEntryBaseAddress + 0x3A8420) != 0x55)
	//{
	//	
	//}
	//
	//nCEterPackManagerGet = (tCEterPackManagerGet)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x3A8420, (PBYTE)HookCEterPackManagerGet);//AtlasInfo.txt

	//nCEterFileDictInsertItem = (tCEterFileDictInsertItem)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x3ABC80, (PBYTE)NewCEterFileDictInsertItem);



	//CMappedFileSize = (tCMappedFileSize)(MainCore::hEntryBaseAddress + 0x3C9B30);
	//nCEterPackManagerGet3 = (tCEterPackManagerGet3)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x19A9F0, (PBYTE)HookCEterPackManagerGet3);//1744B0.txt
	//nCEterFileDictInsertItem = (tCEterFileDictInsertItem)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x419480, (PBYTE)NewCEterFileDictInsertItem);

	
	//nCEterPackManagerGet4 = (tCEterPackManagerGet4)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x1CE6D0, (PBYTE)HookCEterPackManagerGet4);//1744B0.txt
	//CMappedFileSize = (tCMappedFileSize)(MainCore::hEntryBaseAddress + 0x1C1510);
	////nCEterPackManagerGet3 = (tCEterPackManagerGet3)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x40DF70, (PBYTE)HookCEterPackManagerGet3);//1744B0.txt
	////nCEterFileDictInsertItem = (tCEterFileDictInsertItem)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x419480, (PBYTE)NewCEterFileDictInsertItem);
	//nCEterPackManagerGet2 = (tCEterPackManagerGet2)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x213100, (PBYTE)HookCEterPackManagerGet2);
	
	

	//CMappedFileSize = (tCMappedFileSize)(MainCore::hEntryBaseAddress + 0x1F29F0);
	//nCEterPackManagerGet = (tCEterPackManagerGet)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x1EE060, (PBYTE)HookCEterPackManagerGet);//AtlasInfo.txt


	//nCEterFileDictInsertItem = (tCEterFileDictInsertItem)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x1A2FF0, (PBYTE)NewCEterFileDictInsertItem);//Pack index file size error! %s, indexCount %d

	//
																																						  
	CMappedFileSize = (tCMappedFileSize)(MainCore::hEntryBaseAddress + 0x1DD780);
	nCEterPackManagerGet = (tCEterPackManagerGet)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x21FBE0, (PBYTE)HookCEterPackManagerGet);//AtlasInfo.txt
	nCEterFileDictInsertItem = (tCEterFileDictInsertItem)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x22B3C0, (PBYTE)NewCEterFileDictInsertItem);//Pack index file size error! %s, indexCount %d																																					  
																																						  
		
	//CMappedFileSize = (tCMappedFileSize)(MainCore::hEntryBaseAddress + 0x268980);
	//nCEterPackManagerGet = (tCEterPackManagerGet)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x2D0140, (PBYTE)HookCEterPackManagerGet);//AtlasInfo.txt
	//nCEterFileDictInsertItem = (tCEterFileDictInsertItem)DetourFunction((PBYTE)MainCore::hEntryBaseAddress + 0x2DC510, (PBYTE)NewCEterFileDictInsertItem);//Pack index file size error! %s, indexCount %d																		


																																						  //Globals::CMappedFileSize = (Globals::tCMappedFileSize)(Globals::hEntryBaseAddress + 0x136340);
	//Globals::CMappedFile = (Globals::tCMappedFile)(Globals::hEntryBaseAddress + 0x135EA0);
	//Globals::CEterPackManagerGet = (Globals::tCEterPackManagerGet)(Globals::hEntryBaseAddress + 0x4F6750);
	//nCEterPackManagerGet = (Globals::tCEterPackManagerGet)DetourFunction((PBYTE)Globals::CEterPackManagerGet, (PBYTE)HookCEterPackManagerGet); //CItemManager::LoadItemList(%s) - StrangeLine in %d\n
	//Globals::CEterFileDictInsertItem = (Globals::tCEterFileDictInsertItem)(Globals::hEntryBaseAddress + 0x2C2120);
	//nCEterFileDictInsertItem = (Globals::tCEterFileDictInsertItem)DetourFunction((PBYTE)Globals::CEterFileDictInsertItem, (PBYTE)NewCEterFileDictInsertItem);//Pack index file size error! %s, indexCount %d
	//Globals::pCEterPackManagerGet = Globals::hEntryBaseAddress + 0x166DD0;
	//Globals::pCMappedFileSize = Globals::hEntryBaseAddress + 0x134EB0;
	//Globals::pCMappedFile = Globals::hEntryBaseAddress + 0x134970;
	// Globals::pCMappedFileSize = Globals::hEntryBaseAddress + 0x175890;
	//Globals::CEterFileDictInsertItem = (Globals::tCEterFileDictInsertItem)(Globals::hEntryBaseAddress + 0x16A550);
	//nCEterFileDictInsertItem = (Globals::tCEterFileDictInsertItem)DetourFunction((PBYTE)Globals::CEterFileDictInsertItem, (PBYTE)NewCEterFileDictInsertItem);//Pack index file size error! %s, indexCount %d

}

typedef int(__cdecl* tstrcmp)(const char* a1, const char* a2);
tstrcmp nstrcmp;
int _cdecl Newstrcmp(const char* a1, const char* a2)
{
	cout << a2 <<  "     "   << a1 << endl;
	return nstrcmp(a1, a2);
}


void SetHook(BYTE head, DWORD offset, ...)
{
	DWORD OldProtect;
	VirtualProtect((LPVOID)offset, 4, PAGE_EXECUTE_READWRITE, &OldProtect);
	if (head != 0xFF)
	{
		*(BYTE*)(offset) = head;
	}

	DWORD* function = &offset + 1;

	*(DWORD*)(offset + 1) = (*function) - (offset + 5);
};
DWORD d = 0;
DWORD c = 0;
const char* v = "";
const char* r = "";

TEterPackIndex* pkInfo;

void huj(TEterPackIndex* pkInf)
{
	CEterFileDict2.push_back(pkInf);
}
void __declspec(naked) SomeHook()
{
	
	_asm
	{
		MOV d, ESI
		
		/*MOV EDX, c*/
		
	}
	pkInfo =(TEterPackIndex*)d;
	/*cout << pkInfo->filename << "    "<< pkInfo->data_size <<endl;*/
	huj(pkInfo);
	_asm
	{
		

		JMP c
	}
}
void __declspec(naked) Test()
{
	MessageBox(NULL, L"Test", L"Test", 0);
}
typedef HMODULE(__stdcall* tLoadLibraryA)(LPCSTR lpLibFileName);
tLoadLibraryA nLoadLibraryA;
HMODULE __stdcall NewLoadLibraryA(LPCSTR lpLibFileName)
{
	cout << lpLibFileName << endl;
	string d = lpLibFileName;
	if (d == "htrap11/HackTrap.dll")
	{
		DWORD d = (DWORD)_ReturnAddress();
		cout << (d - (DWORD)GetModuleHandle(NULL)) << "    " << endl;
		MessageBox(NULL, L"Test", L"Test", 0);
		/*	MessageBox(NULL, to_string(d).c_str(), "Error", 0);*/
		return (HMODULE)1;
		/*return NULL;*/
	}
	if (d == "htrap2/HackTrap.dll")
	{
		DWORD d = (DWORD)_ReturnAddress();
		cout << (d - (DWORD)GetModuleHandle(NULL)) << "    " << endl;
	/*	MessageBox(NULL, to_string(d).c_str(), "Error", 0);*/
		return (HMODULE)1;
		/*return NULL;*/
	}
	if (d == "htrap/HackTrap.dll")
	{
		DWORD d = (DWORD)_ReturnAddress();
		cout << (d - (DWORD)GetModuleHandle(NULL)) << "    " << endl;
		return (HMODULE)1;
		/*return NULL;*/
	}
	if (d == "HackTrap/HackTrap.dll")
	{
		DWORD d = (DWORD)_ReturnAddress();
		cout << (d - (DWORD)GetModuleHandle(NULL) )<< "    " << endl;
	/*	MessageBox(NULL, to_string(d).c_str(), "Error2", 0);*/
		return (HMODULE)1;
		/*return NULL;*/
	}
	if (d == "htrap3/HackTrap.dll")
	{
		DWORD d = (DWORD)_ReturnAddress();
		cout << (d - (DWORD)GetModuleHandle(NULL)) << "    " << endl;
		MessageBox(NULL, L"Test", L"Test", 0);
		/*MessageBox(NULL, lpLibFileName, lpLibFileName, 0);*/
		return (HMODULE)1;
		/*return NULL;*/
	}
	if (d == "ilu15.dll")
	{
		return (HMODULE)1;
	}
	MessageBox(NULL, L"Test", L"Test", 0);
	return nLoadLibraryA(lpLibFileName);
}
static void JmpHook(DWORD FuncOffset, DWORD JmpOffset)
{
	DWORD OldProtect;
	VirtualProtect((LPVOID)JmpOffset, 4, PAGE_EXECUTE_READWRITE, &OldProtect);
	*(DWORD*)(JmpOffset) = 0xE9;
	*(DWORD*)(JmpOffset + 1) = FuncOffset - (JmpOffset + 5);
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{


	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		std::cout << "This works" << std::endl;
		FARPROC f1 = NULL;
		HMODULE user32Module = GetModuleHandle(L"USER32.dll");
		FARPROC f2 = NULL;
		HMODULE kernel32Module = GetModuleHandle(L"KERNEL32.dll");
		f1 = GetProcAddress(user32Module, "PostQuitMessage");
		f2 = GetProcAddress(kernel32Module, "ExitProcess");
		MessageBox(NULL, L"Test", L"Test", 0);
	/*	nLoadLibraryA = (tLoadLibraryA)DetourFunction((PBYTE)GetProcAddress(GetModuleHandle(L"KERNEL32.dll"), "LoadLibraryA"), (PBYTE)NewLoadLibraryA);*/
		/*nstrcmp = (tstrcmp)DetourFunction((PBYTE)strcmp, (PBYTE)Newstrcmp);*/
		/*c = (DWORD)GetModuleHandle(NULL) + 0x1D3688;*/
		/*JmpHook((DWORD)GetModuleHandle(NULL)+ 0x105F7D, (DWORD)GetModuleHandle(NULL) + 0x1D3679);*/
			/*SetHook(0xE9, (DWORD)GetModuleHandle(NULL) + 0x1D3679, SomeHook);*/
		/*nExitProcess = (tExitProcess)DetourFunction((PBYTE)f2, (PBYTE)NewExitProcess);*/


		//MemoryExtension::MemSet(((DWORD)GetModuleHandle(NULL) + 0x106840), 0x90, 200); //83 C4 ? E8 ? ? ? ? 6A ? 6A


		/*nPostQuitMessage = (tPostQuitMessage)DetourFunction((PBYTE)f1, (PBYTE)NewPostQuitMessage);*/
//#ifdef DEVELOPER_MODE
			
//#endif
		 //



		/*MemoryExtension::MemSet(((DWORD)GetModuleHandle(NULL) + 0x21F8603), 0x90, 10);*/ //E8 ? ? ? ? A3 F8 54
		/*MemoryExtension::MemSet(((DWORD)GetModuleHandle(NULL) + 0x1A0A6D), 0x90, 13);

		MemoryExtension::MemSet(((DWORD)GetModuleHandle(NULL) + 0x1A1A82), 0x90, 75);*/
		

		/*CreateThread(0, NULL, (LPTHREAD_START_ROUTINE)DumpHook, NULL, NULL, NULL);*/
			MainCore::hModule = hModule;;
			/*MemoryExtension::MemSet((MainCore::hEntryBaseAddress + 0x20DB313), 0x90, 5);*/ //83 C4 ? E8 ? ? ? ? 6A ? 6A

			/*DumpHook();*/
			/*MessageBox(NULL, L"Test", L"Test", 0);*/
		//	//
	/*	CreateThread(0, NULL, (LPTHREAD_START_ROUTINE)MainCore::Initialize, NULL, NULL, NULL);*/
		   MainCore::Initialize();
		 
		   /*for (;;) 
		   {

		   }*/
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	{
		
	}
	case DLL_PROCESS_DETACH:
		
		break;
	}
	return TRUE;
}




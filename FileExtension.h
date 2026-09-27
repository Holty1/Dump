#pragma once
class FileExtension
{
public:
	static string GetDirectoryPathFromFilePatch(string filePath);
	static string GetCurrentExeDirectory();
	static vector<char> ReadAllBytes(char const* filename);
	static int ReadByteFileSize(const char * filename, int * read);
	static char * ReadAllBytes(const char * filename, int * read);
	static bool CreateDirectoryPath(const char* path);
	static void Write(const std::string& file_name, void* data,int size);
	static void Read(const std::string& file_name, void* data, int size);
	
};


#include "stdafx.h"
#include "FileExtension.h"


string FileExtension::GetDirectoryPathFromFilePatch(string filePath)
{
	string directory;
	const size_t last_slash_idx = filePath.rfind('\\');
	if (std::string::npos != last_slash_idx)
	{
		directory = filePath.substr(0, last_slash_idx);
	}
	return directory;
}

string FileExtension::GetCurrentExeDirectory()
{
	const unsigned long maxDir = 260;
	char currentDir[maxDir];
	GetCurrentDirectory(maxDir, (LPWSTR)currentDir);
	return string(currentDir);
}
int FileExtension::ReadByteFileSize(const char * filename, int * read)
{
	ifstream file(filename, ios::binary | ios::ate);
	return file.tellg();
}

char * FileExtension::ReadAllBytes(const char * filename, int * read)
{
	ifstream ifs(filename, ios::binary | ios::ate);
	ifstream::pos_type pos = ifs.tellg();
	int length = pos;
	char *pChars = new char[length];
	ifs.seekg(0, ios::beg);
	ifs.read(pChars, length);
	ifs.close();
	*read = length;
	return pChars;
}
vector<char> FileExtension::ReadAllBytes(char const* filename)
{
	ifstream ifs(filename, ios::binary | ios::ate);
	ifstream::pos_type pos = ifs.tellg();

	std::vector<char>  result(pos);

	ifs.seekg(0, ios::beg);
	ifs.read(&result[0], pos);

	return result;
}

bool FileExtension::CreateDirectoryPath(const char* path)
{
	if (CreateDirectory(StringExtension::GetWideChar(path), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void FileExtension::Write(const std::string& file_name, void* data,int size)
{
	std::ofstream out(file_name.c_str());
	out.write(reinterpret_cast<char*>(data), size);
	out.close();
}

void FileExtension::Read(const std::string& file_name, void* data,int size)
{
	std::ifstream in(file_name.c_str());
	in.read(reinterpret_cast<char*>(data), size);
	in.close();
}
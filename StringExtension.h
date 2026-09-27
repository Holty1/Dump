#pragma once
class StringExtension
{
public:
	static const char * ConstCharJoin(const char * chr1, const char * chr2);
	//static const char * ConstCharJoin(const char * chr1, const char * chr2, const char * chr3);
	static string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
	static bool Contains(const std::string& word, const std::string& sentence);
	static bool ContainsW(const std::wstring& sentence, const std::wstring& word);
	static bool Equals(const char* word1, const char*  word2);
	static unsigned char *    BinToStrhex(const unsigned char *bin, unsigned int binsz, unsigned char **result);
	static string MakeHexString(BYTE *data, int len, bool use_uppercase, bool insert_spaces);

	static string ByteToHex(BYTE byte);
	static string StringFormat(const string fmt_str, ...);
	static const char* StringFormatChar(const string fmt_str, ...);
	static string ByteToAsciiString(void *data, int len);
	static const wchar_t  * GetWideChar(const char *c);
	static LPWSTR  GetLPWSTR(const char *c);
	static const wchar_t * GetWCharFromString(string c);
	static const char* ConstCharFromWChar(TCHAR *tch);
	static string StringFromWChar(TCHAR *tch);
	static string StringFromWString(wstring ws);
	static vector<string> Split(const string& str, const string& delim);
	static bool EndsWith(std::string const& value, std::string const& ending);
};


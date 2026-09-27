#include "stdafx.h"
#include "StringExtension.h"
vector<string> StringExtension::Split(const string& str, const string& delim)
{
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

const char * StringExtension::ConstCharJoin(const char * chr1, const char * chr2)
{

	char result[sizeof(chr1)+sizeof(chr2)];
	strncpy(result, chr1, sizeof(result));
	strncat(result, chr2, sizeof(result));
	return result;
}
string StringExtension::ReplaceString(std::string subject, const std::string& search, const std::string& replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

 bool StringExtension::EndsWith(std::string const& value, std::string const& ending)
{
	if (ending.size() > value.size()) return false;
	return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

bool StringExtension::Contains( const std::string& sentence,const std::string& word)
{
	return sentence.find(word)   
	
		!= std::string::npos;  
}
bool StringExtension::ContainsW(const std::wstring& sentence, const std::wstring& word)
{
	return sentence.find(word)

		!= std::string::npos;
}
bool StringExtension::Equals(const char* word1, const char*  word2)
{
	if (strcmp(word1, word2) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

unsigned char *    StringExtension::BinToStrhex(const unsigned char *bin, unsigned int binsz,unsigned char **result)
{
	unsigned char     hex_str[] = "0123456789ABCDEF";
	unsigned int      i;

	if (!(*result = (unsigned char *)malloc(binsz * 2 + 1)))
		return (NULL);

	(*result)[binsz * 2] = 0;

	if (!binsz)
		return (NULL);

	for (i = 0; i < binsz; i++)
	{
		(*result)[i * 2 + 0] = hex_str[(bin[i] >> 4) & 0x0F];
		(*result)[i * 2 + 1] = hex_str[(bin[i]) & 0x0F];
	}
	return (*result);
}

string StringExtension::MakeHexString(BYTE *data, int len, bool use_uppercase = true, bool insert_spaces = false)
{
	std::ostringstream ss;
	ss << std::hex << setfill('0');
	if (use_uppercase)
		ss << std::uppercase;
	for (int i = 0; i < len; ++i)
	{
		ss << setw(2) << static_cast<int>(data[i]);
		if (insert_spaces)
			ss << " ";
	}
	string butt = ss.str();
	butt.erase(butt.size() - 1);
	return butt;
	
}
string StringExtension::ByteToHex(BYTE byte)
{
	ostringstream ss;
	ss << std::hex << setfill('0');
	ss << std::uppercase;
	
	ss << setw(2) << static_cast<int>(byte);
	return ss.str();
}
string StringExtension::StringFormat(const string fmt_str, ...)
{
	int final_n, n = ((int)fmt_str.size()) * 2;
	unique_ptr<char[]> formatted;
	va_list ap;
	while (1) {
		formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
		strcpy(&formatted[0], fmt_str.c_str());
		va_start(ap, fmt_str);
		final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
		va_end(ap);
		if (final_n < 0 || final_n >= n)
			n += abs(final_n - n + 1);
		else
			break;
	}
	return string(formatted.get());
}
const char* StringExtension::StringFormatChar(const string fmt_str, ...)
{
	int final_n, n = ((int)fmt_str.size()) * 2;
	unique_ptr<char[]> formatted;
	va_list ap;
	while (1) {
		formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
		strcpy(&formatted[0], fmt_str.c_str());
		va_start(ap, fmt_str);
		final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
		va_end(ap);
		if (final_n < 0 || final_n >= n)
			n += abs(final_n - n + 1);
		else
			break;
	}
	return string(formatted.get()).c_str();
}
string StringExtension::ByteToAsciiString(void *data, int len )
{

	string ret = "";
	BYTE *dataBuff = new BYTE[len];
	memcpy(dataBuff, data, len);
	for (int j = 0; j < len;j++)
	{

		if (dataBuff[j] == 0x00)
		{
			ret += ".";
		}
		else
		{
			ret += (char)dataBuff[j];
		}

	}


	return ret;

	//return string(reinterpret_cast<char const*>(data), len);
}

const wchar_t * StringExtension::GetWideChar(const char *c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

LPWSTR  StringExtension::GetLPWSTR(const char *c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}
const wchar_t * StringExtension::GetWCharFromString(string c)
{
	std::wstring stemp = std::wstring(c.begin(), c.end());
	return  stemp.c_str();
}
const char* StringExtension::ConstCharFromWChar(TCHAR *tch)
{
	wstring ws = wstring(tch);
	string s(ws.begin(), ws.end());
	return s.c_str();
}
string StringExtension::StringFromWChar(TCHAR *tch)
{
	wstring ws = wstring(tch);
	string s(ws.begin(), ws.end());
	return s;
}
string StringExtension::StringFromWString(wstring ws)
{
	string s(ws.begin(), ws.end());
	return s;
}


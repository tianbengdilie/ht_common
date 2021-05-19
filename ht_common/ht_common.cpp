#define _CRT_SECURE_NO_WARNINGS

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus > 201402L) == 1
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#endif

#include "ht_common.h"

#include <fstream>
using namespace std;

// file
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus > 201402L) == 0
long long ht::getFileSize(const std::string& filepath) {
	ifstream ifs(filepath, ios::in);
	if (!ifs.is_open()) {
		return -1;
	}

	ifs.seekg(0, ios::end);
	return ifs.tellg();
}

bool ht::isFileExist(const std::string & filepath)
{
	ifstream file(filepath, ios::in);
	return file.good();
}

#else
// c++17 µÄº¯Êý
#include <filesystem>

using namespace std;

long long ht::getFileSize(const std::string_view & filepath)
{
	filesystem::path p(filepath);
	if (!filesystem::exists(p)) {
		return -1;
	}

	return (long long)filesystem::file_size(p);
}

bool ht::isFileExist(const std::string_view & filepath)
{
	return filesystem::exists(filesystem::path(filepath));
}

std::string ht::getFileExtend(const std::string_view & filepath)
{
	return filesystem::path(filepath).extension().string();
}

std::string ht::getFileFromPath(const std::string_view & filepath)
{
	return filesystem::path(filepath).filename().string();
}

#endif

// encoding 

#include <locale>
#include <codecvt>

using namespace std;

std::string ht::UnicodeToUTF8(const std::wstring & wstr)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wstr);
}

std::wstring ht::UTF8ToUnicode(const std::string & str)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(str);
}

std::string ht::UnicodeToANSI(const std::wstring & wstr)
{
	std::string ret;
	std::mbstate_t state = {};
	const wchar_t *src = wstr.data();
	size_t len = std::wcsrtombs(nullptr, &src, 0, &state);
	if (static_cast<size_t>(-1) != len) {
		std::unique_ptr< char[] > buff(new char[len + 1]);
		len = std::wcsrtombs(buff.get(), &src, len, &state);
		if (static_cast<size_t>(-1) != len) {
			ret.assign(buff.get(), len);
		}
	}
	return ret;
}

std::wstring ht::ANSIToUnicode(const std::string & str)
{
	std::wstring ret;
	std::mbstate_t state = {};
	const char *src = str.data();
	size_t len = std::mbsrtowcs(nullptr, &src, 0, &state);
	if (static_cast<size_t>(-1) != len) {
		std::unique_ptr< wchar_t[] > buff(new wchar_t[len + 1]);
		len = std::mbsrtowcs(buff.get(), &src, len, &state);
		if (static_cast<size_t>(-1) != len) {
			ret.assign(buff.get(), len);
		}
	}
	return ret;
}

std::string ht::UTF8ToANSI(const std::string & str)
{
	return ht::UnicodeToANSI(ht::UTF8ToUnicode(str));
}

std::string ht::ANSIToUTF8(const std::string & str)
{
	return ht::UnicodeToUTF8(ht::ANSIToUnicode(str));
}

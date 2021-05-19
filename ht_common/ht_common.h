#pragma once
#include <string>

#if (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus > 201402L
#include <string_view>
#endif

namespace ht {
	// file
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus > 201402L) == 0
	long long getFileSize(const std::string& filepath);
	bool isFileExist(const std::string& filepath);
#else
	long long getFileSize(const std::string_view& filepath);
	bool isFileExist(const std::string_view& filepath);
	std::string getFileExtend(const std::string_view& filepath);
	std::string getFileFromPath(const std::string_view& filepath);
#endif

	// encoding
	std::string UnicodeToUTF8(const std::wstring & wstr);
	std::wstring UTF8ToUnicode(const std::string & str);
	std::string UnicodeToANSI(const std::wstring & wstr);
	std::wstring ANSIToUnicode(const std::string & str);
	std::string UTF8ToANSI(const std::string & str);
	std::string ANSIToUTF8(const std::string & str);
}
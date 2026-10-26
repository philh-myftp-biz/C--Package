#pragma once

#include <string>
#include <vector>
#include <iterator>
#include <cwctype>
#include <format>
#include <algorithm>

#include "ww898/utf_converters.hpp"

namespace stru {
    
    using str = std::string;
    using wstr = std::wstring;

    template <typename T>
    concept IsString = std::same_as<T, str> || std::same_as<T, wstr>;

    //===============================================================================

    wstr to_wstr(const str& _str) {
        if (_str.empty()) return wstr();
        return ww898::utf::conv<wchar_t>(_str);
    }

    str to_str(const wstr& _wstr) {
        if (_wstr.empty()) return str();
        return ww898::utf::conv<char>(_wstr);
    }

    //===============================================================================

    str lower(str _str) {
        std::transform(_str.begin(), _str.end(), _str.begin(), [](unsigned char c) {
            return std::tolower(c);
        });
        return _str;
    }

    wstr lower(wstr _str) {
        std::transform(_str.begin(), _str.end(), _str.begin(), [](wchar_t c) {
            return std::towlower(c);
        });
        return _str;
    }

    //===============================================================================

    template <IsString T>
    bool has_str(T mainstr, T substr) {
        return mainstr.find(substr) != T::npos;
    }

    template <IsString T>
    bool has_str_nc(T mainstr, T substr) {
        return has_str(lower(mainstr), lower(substr));
    }

    //===============================================================================

    template <IsString T>
    bool match_str(T a, T b) {
        return has_str(a, b) || has_str(b, a);
    }

    template <IsString T>
    bool match_str_nc(T a, T b) {
        return has_str_nc(a, b) || has_str_nc(b, a);
    }

    //===============================================================================

    str strip(const str& _str) {
        size_t first = _str.find_first_not_of(' ');
        if (str::npos == first) return "";
        size_t last = _str.find_last_not_of(' ');
        return _str.substr(first, (last - first + 1));
    }

    //===============================================================================
    
    str zfill(int n, str _str) {
        return std::format("{:0>{}}", _str, n);
    }

    str zfill(int n, int _int) {
        return std::format("{:0{}}", _int, n);
    }

    //===============================================================================

}

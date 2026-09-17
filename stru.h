#pragma once

#include <string>
#include <vector>
#include <iterator>
#include <cwctype>
#include <format>

#include "ww898/utf_converters.hpp"

using str = str;
using wstr = std::wstring;

namespace stru {

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

    bool has_str(str mainstr, str substr) {
        return mainstr.find(substr) != str::npos;
    }

    bool has_str(wstr mainstr, wstr substr) {
        return mainstr.find(substr) != wstr::npos;
    }

    bool has_str_nc(str mainstr, str substr) {
        return has_str(lower(mainstr), lower(substr));
    }

    bool has_str_nc(wstr mainstr, wstr substr) {
        return has_str(lower(mainstr), lower(substr));
    }

    //===============================================================================

    bool match_str(str a, str b) {
        return has_str(a, b) || has_str(b, a);
    }

    bool match_str(wstr a, wstr b) {
        return has_str(a, b) || has_str(b, a);
    }

    bool match_str_nc(str a, str b) {
        return has_str_nc(a, b) || has_str_nc(b, a);
    }

    bool match_str_nc(wstr a, wstr b) {
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

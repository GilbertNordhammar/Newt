#include "jerboa-pch.h"
#include "String.h"

namespace Jerboa::String {
    std::string TrimLeft(const std::string& s, const std::string& characters)
    {
        size_t start = s.find_first_not_of(characters);
        return (start == std::string::npos) ? "" : s.substr(start);
    }

    std::string TrimRight(const std::string& s, const std::string& characters)
    {
        size_t end = s.find_last_not_of(characters);
        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
    }

    std::string Trim(const std::string& s, const std::string& characters)
    {
        return TrimRight(TrimLeft(s, characters), characters);
    }
}
#pragma once

#include <string>

namespace Jerboa::String {
    std::string TrimLeft(const std::string& s, const std::string& characters);
    std::string TrimRight(const std::string& s, const std::string& characters);
    std::string Trim(const std::string& s, const std::string& characters);
}
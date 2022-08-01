#pragma once

#include <string_view>

namespace Jerboa
{
    enum class FileNameMode
	{
		WithExtension,
		WithoutExtension
	};

    std::string GetFileName(std::string_view path, FileNameMode type);
}
#include "jerboa-pch.h"
#include "File.h"

namespace Jerboa
{
	std::string GetFileName(std::string_view path, FileNameMode type)
	{
		auto nameStart = path.find_last_of("/\\") + 1;
		auto nameEnd = type == FileNameMode::WithoutExtension ? path.find_last_of(".") : path.size();
		if (nameEnd == std::string::npos)
			nameEnd = path.size();

		int nameLength = nameEnd - nameStart;
		return std::string(path.substr(nameStart, nameLength));
	}
}
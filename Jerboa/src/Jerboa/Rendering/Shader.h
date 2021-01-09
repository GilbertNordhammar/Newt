#pragma once

#include <memory>

namespace Jerboa {
	class Shader
	{
	public:
		static std::shared_ptr<Shader> Create(
			const std::string& vertexPath,
			const std::string& fragmentPath
		);

		virtual void Use() const = 0;
	};
}
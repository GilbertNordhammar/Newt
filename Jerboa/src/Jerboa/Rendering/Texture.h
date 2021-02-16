#pragma once

#include <string>
#include <memory>

namespace Jerboa {
	class Texture
	{
	public:
		virtual int_fast32_t GetWidth() const = 0;
		virtual int_fast32_t GetHeight() const = 0;
		virtual const std::string& GetPath() const = 0;
		virtual void Bind(int slot) = 0;
	};

	enum class TextureType {
		Albedo, Normal, Metallic, Roughness, AmbientOcclusion
	};

	class Texture2D : public Texture {
	public:
		static std::shared_ptr<Texture2D> Create(const std::string& path, TextureType type);

		virtual TextureType GetType() const = 0;
	};
}



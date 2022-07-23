#pragma once

#include "Jerboa/Rendering/Texture.h"
#include "Objects/GL_TextureObject.h"

namespace Jerboa
{
	class GL_Texture2D : public Texture2D
	{
	public:
		GL_Texture2D(const std::string &path, TextureType type);

		virtual int_fast32_t GetWidth() const override { return mWidth; };
		virtual int_fast32_t GetHeight() const override { return mHeight; };
		virtual const std::string &GetPath() const override { return mPath; };
		virtual TextureType GetType() const override { return mType; };
		virtual void Bind(int slot) override;

	private:
		GL_TextureObject mTexture;
		TextureType mType;

		int_fast32_t mWidth;
		int_fast32_t mHeight;
		std::string mPath;
	};
} // namespace Jerboa

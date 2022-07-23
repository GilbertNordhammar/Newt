#include "jerboa-pch.h"
#include "GL_Texture2D.h"

#include "Jerboa/Debug.h"

#include "stb_image.h"
#include "glad/glad.h"

namespace Jerboa
{
	GL_Texture2D::GL_Texture2D(const std::string &path, TextureType type)
		: mPath(path), mType(type)
	{
		stbi_set_flip_vertically_on_load(true);

		int nrComponents;
		float *dataHDR{};
		unsigned char *data{};

		if (stbi_is_hdr(path.c_str()))
		{
			JERBOA_LOG_INFO("Loading HDR texture \"{0}\"", path);
			dataHDR = stbi_loadf(path.c_str(), &mWidth, &mHeight, &nrComponents, 0);
		}
		else
		{
			JERBOA_LOG_INFO("Loading texture \"{0}\"", path);
			data = stbi_load(path.c_str(), &mWidth, &mHeight, &nrComponents, 0);
		}

		if (data || dataHDR)
		{
			GLenum format;
			if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;
			else // nrComponents == 1
				format = GL_RED;

			GLenum internalFormat = format;
			if (type == TextureType::Albedo)
				internalFormat = format == GL_RGBA ? GL_SRGB_ALPHA : GL_SRGB;

			glBindTexture(GL_TEXTURE_2D, mTexture);
			if (dataHDR)
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, dataHDR);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else
		{
			JERBOA_LOG_WARN("Couldn't load texture {0}", path);
		}

		stbi_image_free(data);
		stbi_image_free(dataHDR);
	}

	void GL_Texture2D::Bind(int slot)
	{
		JERBOA_ASSERT(slot >= 0, "Must not be negative");
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, mTexture);
	}
} // namespace Jerboa
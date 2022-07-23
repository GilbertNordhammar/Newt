#pragma once

#pragma once

#include "GL_Object.h"

namespace Jerboa
{
	class GL_TextureObject : public GL_Object
	{
	public:
		GL_TextureObject()
			: GL_Object(
				  [](GLuint *object) {
					  glGenTextures(1, object);
				  },
				  [](GLuint *object) {
					  glDeleteTextures(1, object);
				  })
		{
		}
	};
} // namespace Jerboa
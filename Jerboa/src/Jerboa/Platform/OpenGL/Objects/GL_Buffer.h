#pragma once

#include "GL_Object.h"

namespace Jerboa
{
	class GL_Buffer : public GL_Object
	{
	public:
		GL_Buffer()
			: GL_Object(
				  [](GLuint *object) {
					  glGenBuffers(1, object);
				  },
				  [](GLuint *object) {
					  glDeleteBuffers(1, object);
				  })
		{
		}
	};
} // namespace Jerboa

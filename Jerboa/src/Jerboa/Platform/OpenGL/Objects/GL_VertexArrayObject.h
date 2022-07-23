#pragma once

#include "GL_Buffer.h"

namespace Jerboa
{
	class GL_VertexArray : public GL_Object
	{
	public:
		GL_VertexArray()
			: GL_Object(
				  [](GLuint *object) {
					  glGenVertexArrays(1, object);
				  },
				  [](GLuint *object) {
					  glDeleteVertexArrays(1, object);
				  })
		{
		}
	};
} // namespace Jerboa

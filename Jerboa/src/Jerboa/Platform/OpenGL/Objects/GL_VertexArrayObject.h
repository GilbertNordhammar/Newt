#pragma once

#include "GL_Buffer.h"

namespace Jerboa
{
	class GL_VertexArrayObject : public GL_Object
	{
	public:
		GL_VertexArrayObject()
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

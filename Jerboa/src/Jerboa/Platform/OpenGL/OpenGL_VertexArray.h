#pragma once

#include "OpenGL_Buffer.h"

namespace Jerboa {
	class OpenGL_VertexArray : public OpenGL_Object {
	public:
		OpenGL_VertexArray()
			: OpenGL_Object
			(
				[](GLuint* object) {
					glGenVertexArrays(1, object);
				},
				[](GLuint* object) {
					glDeleteVertexArrays(1, object);
				}
			)
		{}
	};
}

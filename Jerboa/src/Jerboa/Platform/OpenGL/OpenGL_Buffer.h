#pragma once

#include "OpenGL_Object.h"

namespace Jerboa {
	class OpenGL_Buffer : public OpenGL_Object {
	public:
		OpenGL_Buffer()
			: OpenGL_Object
			(
				[](GLuint* object) {
					glGenBuffers(1, object);
				},
				[](GLuint* object) {
					glDeleteBuffers(1, object);
				}
			)
		{}
	};
}


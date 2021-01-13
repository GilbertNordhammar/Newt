#pragma once

#pragma once

#include "OpenGL_Object.h"

namespace Jerboa {
	class OpenGL_TextureObject : public OpenGL_Object {
	public:
		OpenGL_TextureObject()
			: OpenGL_Object
			(
				[](GLuint* object) {
					glGenTextures(1, object);
				},
				[](GLuint* object) {
					glDeleteTextures(1, object);
				}
			)
		{}
	};
}
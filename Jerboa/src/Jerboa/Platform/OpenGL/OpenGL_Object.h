#pragma once

#include <glad/glad.h>
#include <vector>
#include <functional>

namespace Jerboa {
	using GenerateObjectFunc = std::function<void(GLuint*)>;
	using DeleteObjectFunc = std::function<void(GLuint*)>;

	class OpenGL_Object {
	public:
		OpenGL_Object(
			GenerateObjectFunc	genObjFunc,
			DeleteObjectFunc	delObjFunc);
		OpenGL_Object(const OpenGL_Object& other) = delete;
		OpenGL_Object(OpenGL_Object&& other);
		~OpenGL_Object();

		OpenGL_Object& operator=(OpenGL_Object& other) = delete;
		OpenGL_Object& operator=(OpenGL_Object&& other) noexcept;
		
		operator GLuint() const { return mObject; }

	protected:
		void CleanUp();
		void Move(OpenGL_Object& other);
		
		GLuint mObject = 0;
		DeleteObjectFunc DeleteObjects;
	};
}





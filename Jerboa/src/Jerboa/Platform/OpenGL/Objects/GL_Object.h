#pragma once

#include <glad/glad.h>
#include <vector>
#include <functional>

namespace Jerboa
{
	using GenerateObjectFunc = std::function<void(GLuint *)>;
	using DeleteObjectFunc = std::function<void(GLuint *)>;

	class GL_Object
	{
	public:
		GL_Object(
			GenerateObjectFunc genObjFunc,
			DeleteObjectFunc delObjFunc);
		GL_Object(const GL_Object &other) = delete;
		GL_Object(GL_Object &&other);
		~GL_Object();

		GL_Object &operator=(GL_Object &other) = delete;
		GL_Object &operator=(GL_Object &&other) noexcept;

		operator GLuint() const { return mObject; }

	protected:
		void CleanUp();
		void Move(GL_Object &other);

		GLuint mObject = 0;
		DeleteObjectFunc DeleteObjects;
	};
} // namespace Jerboa
